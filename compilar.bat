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

gcc cliente.h
call :Verifica cliente.h
gcc -c produtos.c -o produtos.o
call :Verifica produtos.c
gcc -c compras.c -o compras.o
call:Verifica compras.c
gcc -c main.c -o main.o
call :Verifica main.c
gcc produtos.o main.o compras.o -o sistema_loja.exe
if %ERRORLEVEL% EQU 0 (
		echo Executavel gerado com sucesso!
		START sistema_loja
		exit
	)
	if %ERRORLEVEL% NEQ 0 (
		pause 
		exit
	)

:Verifica
	if %ERRORLEVEL% EQU 0 (
		echo %~1 compilou
		exit /b 0
	)
	if %ERRORLEVEL% NEQ 0 (
		pause 
		exit
	)