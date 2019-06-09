#ifndef _SERIAL_UTIL_H
#define _SERIAL_UTIL_H

#include <Windows.h>

extern HANDLE serial_open(const char *fn, DCB *dcb_saved);
extern void serial_close(HANDLE handle, const DCB *dcb_saved);

void InitSerial();

void Serial_Background ();

#endif	/* _SERIAL_UTIL_H */
