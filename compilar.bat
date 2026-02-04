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

if not exist "/bin" (
	mkdir bin
)

gcc -c src/cliente.c -o bin/cliente.o
call :Verifica cliente.c

gcc -c src/produtos.c -o bin/produtos.o
call :Verifica produtos.c

gcc -c src/compras.c -o bin/compras.o
call:Verifica compras.c

gcc -c src/main.c -o bin/main.o
call :Verifica main.c

gcc bin/cliente.o bin/produtos.o bin/compras.o bin/main.o -o sistema_loja.exe

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