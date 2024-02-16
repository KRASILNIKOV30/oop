@echo off

rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem проверяем нахождение обратной матрицы с положительным определителем
%PROGRAM% positive_det.txt > %TEMP%\positive_det.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\positive_det.txt positive_det_inverted.txt
if ERRORLEVEL 1 goto err

rem проверяем нахождение обратной матрицы с отрицательным определителем
%PROGRAM% negative_det.txt > %TEMP%\negative_det.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\negative_det.txt negative_det_inverted.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при инвертировании матрицы с нулевым определителем
%PROGRAM% zero_det.txt > %TEMP%\zero_det.txt
if NOT ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при открытии несуществующего файла
%PROGRAM% non-existing-file-name.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

%PROGRAM% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1