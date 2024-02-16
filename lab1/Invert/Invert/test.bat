@echo off

rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��������� ���������� �������� ������� � ������������� �������������
%PROGRAM% positive_det.txt > %TEMP%\positive_det.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\positive_det.txt positive_det_inverted.txt
if ERRORLEVEL 1 goto err

rem ��������� ���������� �������� ������� � ������������� �������������
%PROGRAM% negative_det.txt > %TEMP%\negative_det.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\negative_det.txt negative_det_inverted.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� �������������� ������� � ������� �������������
%PROGRAM% zero_det.txt > %TEMP%\zero_det.txt
if NOT ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� �������� ��������������� �����
%PROGRAM% non-existing-file-name.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

%PROGRAM% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1