Skip to content
Search or jump to�
Pull requests
Issues
Marketplace
Explore
 
@KRASILNIKOV30 
alexey-malov
/
oop
Public
Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights
oop/labs/lab1/CopyFile/test.bat
@alexey-malov
alexey-malov ��������� ����������� � ������ ��������� CopyFile
Latest commit e29f385 on 7 Feb 2018
 History
 1 contributor
40 lines (32 sloc)  1.42 KB
   
rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��������� ����������� ������� ����� (�������� ��� �� ��������� ����� �������� ������������)
%PROGRAM% empty.txt %TEMP%\empty.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt empty.txt
if ERRORLEVEL 1 goto err

rem ��������� ����������� ����� �� ����� ������
%PROGRAM% one-line.txt %TEMP%\one-line.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\one-line.txt one-line.txt
if ERRORLEVEL 1 goto err

rem ��������� ����������� ����� �� ���������� �����
%PROGRAM% multiline.txt %TEMP%\multiline.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\multiline.txt multiline.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� ����������� ��������������� �����
%PROGRAM% non-existing-file-name.txt %TEMP%\non-existing-file-name.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-when-input-file-is-missing.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� ������������� ������ � �������� ���� (� ����������� ���� ���������)
%PROGRAM% multiline.txt %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1