REM Путь к тестируемой программе передается через 1й аргумент командной строки
SET MyProgram="%~1"


REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Copy empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" || goto err
fc Empty.txt "%TEMP%\output.txt" >nul || goto err
echo Test 1 passed

REM Copy Notempty file
%MyProgram% NotEmpty.txt "%TEMP%\output.txt" || goto err
fc NotEmpty.txt "%TEMP%\output.txt" > nul|| goto err
echo Test 2 passed



REM Copy missing file should fail
%MyProgram% Missing.txt "%TEMP%\output.txt" && goto err
echo Test 3 passed

REM If output file is not specified, progam should fail
%MyProgram% Missing.txt && goto err
echo Test 4 passed

REM If input and output files are not specified, progam should fail
%MyProgram% && goto err
echo Test 5 passed


REM Тесты прошли успешно
echo All tests passed succesfully :)
exit /B 0


REM В случае ошибки
:err
echo Test failed
exit /B 1

