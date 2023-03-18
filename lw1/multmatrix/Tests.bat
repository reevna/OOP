REM Путь к тестируемой программе передается через 1й аргумент командной строки
set MyProgram="%~1"
set OUT="%TEMP%\out.txt"


REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM empty file with first matrix fc Empty.txt 
%MyProgram% Empty.txt matrix2.txt > %OUT% || goto err
fc EmptyOut.txt %OUT% >nul || goto err
echo Test 1 passed


REM Correct files
%MyProgram% matrix1.txt matrix2.txt > %OUT%|| goto err
fc %OUT% matrixRes.txt > nul|| goto err
echo Test 2 passed


REM  missing file should fail
%MyProgram% Missing.txt matrix2.txt && goto err
echo Test 3 passed

REM If first matrix file is not specified, progam should fail
%MyProgram% Missing.txt && goto err
echo Test 4 passed

REM If first and second files are not specified, progam should fail
%MyProgram% && goto err
echo Test 5 passed


REM Тесты прошли успешно
echo All tests passed succesfully :)
exit /B 0


REM В случае ошибки
:err
echo Test failed
exit /B 1

