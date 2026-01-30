@echo off

chcp 65001
title Gerente de Compilação

rem https://superuser.com/questions/80485/exit-batch-file-from-subroutine
REM SETLOCAL
REM IF "%selfWrapped%"=="" (
  REM SET selfWrapped=true
  REM %ComSpec% /s /c ""%~0" %*"
  REM GOTO :EOF
REM )

setlocal EnableDelayedExpansion

rem if not exist %~dp0bin mkdir %~dp0bin
rem cd %~dp0src

call :CompilarH cliente.h
call :CompilarC main.c

GOTO Rodar

:CompilarH
	rem javac %~1.java -d %~dp0bin -Xdiags:verbose
	gcc %~1
	if %ERRORLEVEL% EQU 0 (
		echo %~1 compilou
		exit /b 0
		)
	if %ERRORLEVEL% NEQ 0 (
		pause 
		exit
		)
		
:CompilarC
	rem javac %~1.java -d %~dp0bin -Xdiags:verbose
	gcc %~1 -o programa.exe
	if %ERRORLEVEL% EQU 0 (
		echo %~1 compilou
		exit /b 0
		)
	if %ERRORLEVEL% NEQ 0 (
		pause 
		exit
		)

:Rodar
	START programa
	rem system(pause) incluso no final do programa
	exit