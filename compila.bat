gcc cliente.h
gcc main.c -o programa.exe
if %ERRORLEVEL% equ 0 (
	cls
	start programa.exe
)
if %ERRORLEVEL% neq 0 (
	pause
	exit
)