@echo off

set PROGRAM="%~1"

rem ��������� ������������ ��������� ���������� ���������
%PROGRAM% first-generation.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt second-generation.txt
if ERRORLEVEL 1 goto err

rem ��������� ������ ���� �� �����
%PROGRAM% empty.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt empty.txt
if ERRORLEVEL 1 goto err

rem ��������� ������ � ����� ������������� �������
%PROGRAM% max-size-in.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt max-size-out.txt
if ERRORLEVEL 1 goto err

rem ��������� ������ � ����� �������� ������ �������������
%PROGRAM% more-than-max-size-in.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt more-than-max-size-out.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� ������� ��������� �������������� ������� ����
%PROGRAM% %TEMP%\non-existing-file-name.txt %TEMP%\output.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� ������� ��������� ��� ����������
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ������������� ������ � �������� ����
%PROGRAM% first-generation.txt %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1