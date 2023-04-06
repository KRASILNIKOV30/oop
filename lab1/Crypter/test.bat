@echo off

set CRYPT="%~1"
set DECRYPT="%~2"

rem проверяем кодирование пустого файла

%CRYPT% empty.txt %TEMP%\empty.txt 1
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt empty.txt
if ERRORLEVEL 1 goto err

%DECRYPT% empty.txt %TEMP%\empty.txt 1
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt empty.txt
if ERRORLEVEL 1 goto err


rem проверяем корректность кодирования/декодирования с помощью данных, найденных вручную

%CRYPT% manual-test.txt %TEMP%\manual-test-result.txt 199
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\manual-test-result.txt manual-test-expectation.txt 
if ERRORLEVEL 1 goto err

%DECRYPT% manual-test-expectation.txt %TEMP%\manual-test-result.txt 199
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\manual-test-result.txt manual-test.txt 
if ERRORLEVEL 1 goto err


rem проверяем корректность кодирования/декодирования

%CRYPT% decryption.txt cryption.txt 0
if ERRORLEVEL 1 goto err
%DECRYPT% cryption.txt %TEMP%\decryption.txt 0
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\decryption.txt decryption.txt 
if ERRORLEVEL 1 goto err

%CRYPT% decryption.txt cryption.txt 255
if ERRORLEVEL 1 goto err
%DECRYPT% cryption.txt %TEMP%\decryption.txt 255
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\decryption.txt decryption.txt 
if ERRORLEVEL 1 goto err


rem Ожидаем ненулевой код ошибки при:

rem попытка зашифровать несуществующий файл

%CRYPT% non-existing-file-name.txt %TEMP%\non-existing-file-name.txt 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

%DECRYPT% non-existing-file-name.txt %TEMP%\non-existing-file-name.txt 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err


rem невозможность записи в выходной файл (в исполняемый файл программы)

%CRYPT% manual-test.txt %CRYPT% 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

%DECRYPT% manual-test.txt %DECRYPT% 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err


rem неверное кол-во аргументов

%CRYPT% in.txt out.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

%DECRYPT% in.txt out.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem неверный формат ключа

%CRYPT% in.txt out.txt -1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
%CRYPT% in.txt out.txt 256 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
%CRYPT% in.txt out.txt A > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

%DECRYPT% in.txt out.txt -1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
%DECRYPT% in.txt out.txt 256 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
%DECRYPT% in.txt out.txt A > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1