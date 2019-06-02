@echo off

:: copy to C:/
mkdir C:\tetri_game\bin
mkdir C:\tetri_game\Sound\assets
xcopy /e/y/i/f .\bin C:\tetri_game\bin
copy .\Sound\assets\8bit.wav C:\tetri_game\Sound\assets
copy .\tetri.ico C:\tetri_game
cd C:\tetri_game


:: shortcut
::设置程序或文件的完整路径（必选）
set Program=C:\tetri_game\bin\splash_screen.exe
 
::设置快捷方式名称（必选）
set LnkName=Tetris
 
::设置程序的工作路径，一般为程序主目录，此项若留空，脚本将自行分析路径
set WorkDir=
 
::设置快捷方式显示的说明（可选）
::set Desc=测试
 
if not defined WorkDir call:GetWorkDir "%Program%"
(echo Set WshShell=CreateObject("WScript.Shell"^)
echo strDesKtop=WshShell.SpecialFolders("DesKtop"^)
echo Set oShellLink=WshShell.CreateShortcut(strDesKtop^&"\%LnkName%.lnk"^)
echo oShellLink.TargetPath="%Program%"
echo oShellLink.WorkingDirectory="%WorkDir%"
echo oShellLink.WindowStyle=1
echo oShellLink.Description="%Desc%"
echo oShellLink.IconLocation="C:\tetri_game\tetri.ico"
echo oShellLink.Save)>makelnk.vbs
:: echo 桌面快捷方式创建成功！
makelnk.vbs
del /f /q makelnk.vbs
exit
goto :eof
:GetWorkDir
set WorkDir=%~dp1
set WorkDir=%WorkDir:~,-1%
goto :eof