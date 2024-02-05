@echo off

rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��������� ��������� ������� ����� (�������� ��� �� ��������� ����� �������� ������������)
%PROGRAM% empty.txt %TEMP%\empty.txt 1 1
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt empty.txt
if ERRORLEVEL 1 goto err

rem ��������� ��������� �����, ������� �������� ������ ��������� ������
%PROGRAM% searchStr.txt %TEMP%\output.txt searchStr replaceStr
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt replaceStr.txt
if ERRORLEVEL 1 goto err

rem ��������� ��������� �����, ������� �������� ��������� ��������� �����
%PROGRAM% searchMult.txt %TEMP%\output.txt searchStr replaceStr
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt replaceMult.txt
if ERRORLEVEL 1 goto err

rem ��������� �������� � ��������� ��� ��������� ������
%PROGRAM% test-from-task.txt %TEMP%\output.txt 1231234 000
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt test-from-task-out.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� ��������� ��������������� �����
%PROGRAM% non-existing-file-name.txt %TEMP%\non-existing-file-name.txt 1 1 > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� ������������� ������ � �������� ���� (� ����������� ���� ���������)
%PROGRAM% searchStr.txt %PROGRAM% 1 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

%PROGRAM% searchStr.txt %TEMP%\output.txt 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1