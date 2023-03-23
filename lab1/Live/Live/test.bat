@echo off

set PROGRAM="%~1"

rem провер€ем правильность генерации следующего поколени€
%PROGRAM% first-generation.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt second-generation.txt
if ERRORLEVEL 1 goto err

rem провер€ем пустой файл на входе
%PROGRAM% empty.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt empty.txt
if ERRORLEVEL 1 goto err

rem провер€ем работу с полем максимального размера
%PROGRAM% max-size-in.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt max-size-out.txt
if ERRORLEVEL 1 goto err

rem провер€ем работу с полем размером больше максимального
%PROGRAM% more-than-max-size-in.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt more-than-max-size-out.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при попытке прочитать несуществующий входной файл
%PROGRAM% %TEMP%\non-existing-file-name.txt %TEMP%\output.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при запуске программы без аргументов
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки невозможности записи в выходной файл
%PROGRAM% first-generation.txt %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1