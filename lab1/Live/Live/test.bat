@echo off

set PROGRAM="%~1"

rem проверяем правильность генерации следующего поколения
%PROGRAM% first-generation.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt second-generation.txt
if ERRORLEVEL 1 goto err

rem проверяем пустой файл на входе
%PROGRAM% empty.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt empty.txt
if ERRORLEVEL 1 goto err

rem проверяем работу с полем максимального размера
%PROGRAM% max-size-in.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt max-size-out.txt
if ERRORLEVEL 1 goto err

rem проверяем работу с полем размером больше максимального
%PROGRAM% more-than-max-size-in.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt more-than-max-size-out.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при подаче несуществующего файла
%PROGRAM% non-existing-file-name.txt %TEMP%\non-existing-file-name.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1