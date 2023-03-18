REM ���� � ����������� ��������� ���������� ����� 1� �������� ��������� ������
SET MyProgram="%~1"


REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Check empty file
%MyProgram% Empty.txt "�����" || goto err
fc Empty.txt "output.txt" > nul || goto err
echo Test 1 passed

REM Check Notempty file with one search word
%MyProgram% onegin2.txt "�����" || goto err
fc onegin2_output.txt "output.txt" > nul|| goto err
echo Test 2 passed


REM Check Notempty file with a phrase to search
%MyProgram% phrase.txt "���������� ����������" || goto err
fc phrase_output.txt "output.txt" > nul|| goto err
echo Test 3 passed


REM Missing file should fail
%MyProgram% Missing.txt "�����" && goto err
echo Test 4 passed

REM If phrase to search is not specified, progam should fail
%MyProgram% onegin2.txt && goto err
echo Test 5 passed

REM If input file is not specified, progam should fail
%MyProgram% && goto err
echo Test 6 passed


REM ����� ������ �������
echo All tests passed succesfully :)
exit /B 0


REM � ������ ������
:err
echo Test failed
exit /B 1

