@echo off

rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамл€ющих кавычек (если они были)

rem ѕеременна€ PROGRAM будет хранить первый аргумент командной строки заключЄнный в кавычки
set PROGRAM="%~1"

rem провер€ем обработку пустого файла (копируем его во временную папку текущего пользовател€)
%PROGRAM% empty.txt %TEMP%\empty.txt 1 1
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt empty.txt
if ERRORLEVEL 1 goto err

rem провер€ем обработку файла, который содержит только поисковую строку
%PROGRAM% searchStr.txt %TEMP%\output.txt searchStr replaceStr
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt replaceStr.txt
if ERRORLEVEL 1 goto err

rem провер€ем обработку файла, который содержит несколько поисковых строк
%PROGRAM% searchMult.txt %TEMP%\output.txt searchStr replaceStr
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt replaceMult.txt
if ERRORLEVEL 1 goto err

rem провер€ем ситуацию с возвратом при неудачном поиске
%PROGRAM% test-from-task.txt %TEMP%\output.txt 1231234 000
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test-from-task-out.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при обработке несуществующего файла
%PROGRAM% non-existing-file-name.txt %TEMP%\non-existing-file-name.txt 1 1 > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при невозможности записи в выходной файл (в исполн€емый файл программы)
%PROGRAM% searchStr.txt %PROGRAM% 1 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

%PROGRAM% searchStr.txt %TEMP%\output.txt 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1