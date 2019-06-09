#include <stdio.h>

#include <Windows.h>
#include "serial_util.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

static void _pwinerror(const char *msg, DWORD error_code)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
	              FORMAT_MESSAGE_FROM_SYSTEM,
		      NULL, error_code,
		      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		      (LPTSTR)&lpMsgBuf, 0, NULL);
	printf("%s: %s", msg, lpMsgBuf);

	LocalFree(lpMsgBuf);
}

static void pwinerror(const char *msg)
{
	_pwinerror(msg, GetLastError());
}

static int is_key_down_event(HANDLE stdin_hdl, unsigned char *c)
{
	INPUT_RECORD rec;
	DWORD len;

	if (!ReadConsoleInput(stdin_hdl, &rec, 1, &len)) {
		pwinerror("ReadConsoleInput");
		return 0;
	}
	if (rec.EventType != KEY_EVENT)
		return 0;
	if (!rec.Event.KeyEvent.bKeyDown)
		return 0;

	*c = rec.Event.KeyEvent.uChar.AsciiChar;
	return 1;
}

static int write(HANDLE serial_hdl, const void *buf, int bytes)
{
	int ret = 0;
	OVERLAPPED ov = {0};
	DWORD err_code;
	const DWORD TIMEOUT_MSEC = 200;	/* arbitrary */

	ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (WriteFile(serial_hdl, buf, bytes, NULL, &ov))
		goto out;	/* write completed */

	err_code = GetLastError();
	if (err_code != ERROR_IO_PENDING) {
		_pwinerror("WriteFile", err_code);
		ret = 1;
		goto out;
	}

	/* Wait until write completed. */
	if (WaitForSingleObject(ov.hEvent, TIMEOUT_MSEC) != WAIT_OBJECT_0) {
		pwinerror("WaitForSingleObject");
		ret = 1;
	}
out:
	CloseHandle(ov.hEvent);
	return ret;
}

static int try_read(HANDLE serial_hdl, void *buf, int bytes, OVERLAPPED *ov)
{
	if (!ReadFile(serial_hdl, buf, bytes, NULL, ov)) {
		DWORD e = GetLastError();
		if (e != ERROR_IO_PENDING) {
			_pwinerror("ReadFile", e);
			return 1;
		}
	}
	return 0;
}

static void main_loop(HANDLE serial_hdl)
{
	HANDLE stdin_hdl;
	HANDLE hdls[2];
	OVERLAPPED ov = {0};
	unsigned char ser_in;
	unsigned char std_in;
	DWORD rlen;

	stdin_hdl = GetStdHandle(STD_INPUT_HANDLE);
	if (stdin_hdl == INVALID_HANDLE_VALUE) {
		pwinerror("GetStdHandle");
		return;
	}

	FlushConsoleInputBuffer(stdin_hdl);
	PurgeComm(serial_hdl,
		  PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	/* Make incoming packet turn ov.hEvent signaled. */
	if (try_read(serial_hdl, &ser_in, sizeof(ser_in), &ov))
		//goto out;
		;

	/* Smaller index has the priority when events occur at the same time. */
	hdls[0] = stdin_hdl;
	hdls[1] = ov.hEvent;

	for (;;) {
		int event = WaitForMultipleObjects(ARRAY_SIZE(hdls), hdls,
						   FALSE, INFINITE);
		switch (event) {
		case WAIT_OBJECT_0:
			if (!is_key_down_event(stdin_hdl, &std_in))
				continue;
			printf("got data on stdin: %c\n", std_in);
			if (std_in == 'q')
				goto out;
			if (write(serial_hdl, &std_in, sizeof(std_in)))
				goto out;
			break;
		case WAIT_OBJECT_0 + 1:
			GetOverlappedResult(serial_hdl, &ov, &rlen, FALSE);
			if (rlen > 0)
				printf("\t\t\t\tgot data on serial: %c\n",
				       ser_in);
			else
				printf("serial read timeout\n");

			/* Next try */
			ResetEvent(ov.hEvent);
			if (try_read(serial_hdl, &ser_in, sizeof(ser_in), &ov))
				goto out;
			break;
		default:
			pwinerror("WaitForMultipleObjects");
			goto out;
		}
	}
out:
	CancelIo(serial_hdl);
	CloseHandle(ov.hEvent);
	CloseHandle(stdin_hdl);
}

int main(int argc, char **argv)
{
	HANDLE handle;
	DCB olddcb;
	char *devname;

	if (argc == 2) {
		devname = argv[1];
	} else {
		devname = "com4";
		// printf("usage: %s <serial device>\n", argv[0]);
		// return 1;
	}

	if ((handle = serial_open(devname, &olddcb)) < 0) {
		pwinerror(devname);
		return 1;
	}

	main_loop(handle);

	serial_close(handle, &olddcb);

	return 0;
}
