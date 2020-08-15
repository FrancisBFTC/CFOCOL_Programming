echo off
cls
color 6
echo ***** EXECUTE COMO ADMINISTRADOR *****
echo.
set /p var=digite aqui o caminho do interpretador: 
echo.
echo Salvando na variavel de ambiente ...
echo.
setx PATH "%PATH%;%var%;" /M
echo.
pause