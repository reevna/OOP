REM ���� � ����������� ��������� ���������� ����� 1� �������� ��������� ������
SET MyProgram="%~1"
SET OUT="%TEMP%\out.txt"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)


REM Check correct input of number
%MyProgram% "253" > %OUT% || goto err
fc %OUT% 253output.txt|| goto err
echo Test 1 passed

REM Non a number on input
%MyProgram% "abc" > %OUT% || goto err
fc %OUT% abc.txt|| goto err
echo Test 2 passed


REM Number greater than MAXINT in input
%MyProgram% "2147483648" > %OUT% || goto err
fc %OUT% maxOutput.txt|| goto err
echo Test 3 passed


REM MAXINT in input
%MyProgram% "2147483647" > %OUT% || goto err
fc %OUT% maxint.txt|| goto err
echo Test 4 passed



REM Check missing number
%MyProgram% ""> %OUT% || goto err
fc %OUT% missing.txt|| goto err
echo Test 5 passed



REM ����� ������ �������
echo All tests passed succesfully :)
exit /B 0


REM � ������ ������
:err
echo Test failed
exit /B 1

