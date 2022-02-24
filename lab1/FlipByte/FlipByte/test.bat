@echo off

set PROGRAM="%~1"

%PROGRAM% 6 > out.txt
if ERRORLEVEL 1 goto err
fc.exe out.txt in6.txt
if ERRORLEVEL 1 goto err
echo Test 1 succeeded

%PROGRAM% 255 > out.txt
if ERRORLEVEL 1 goto err
fc.exe out.txt in255.txt
if ERRORLEVEL 1 goto err
echo Test 2 succeeded

%PROGRAM% 256 > out.txt
if NOT ERRORLEVEL 1 goto err
echo Test 3 succeeded

%PROGRAM% > out.txt
if NOT ERRORLEVEL 1 goto err
echo Test 4 succeeded

%PROGRAM% a6 > out.txt
if NOT ERRORLEVEL 1 goto err
echo Test 5 succeeded

%PROGRAM% out.txt > out.txt
if NOT ERRORLEVEL 1 goto err
echo Test 6 succeeded

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1