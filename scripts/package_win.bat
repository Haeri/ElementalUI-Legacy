@echo off

:: Store caller path
set old_path=%cd%
set err=0 
cd "%~dp0"
::-----------------------



cd ..
if "%1" == "-static" (
	xcopy ".\build\Release\elem.lib" ".\lib\elem-static.lib*"

	:: Hello World
	xcopy ".\build\examples\calculator\res" ".\samples\calculator\res" /I/E
	xcopy ".\build\examples\calculator\Release\calculator.exe" ".\samples\calculator\"

	:: Overview
	xcopy ".\build\examples\slack\res" ".\samples\slack\res" /I/E
	xcopy ".\build\examples\slack\Release\slack.exe" ".\samples\slack\"
) else (
	xcopy ".\build\Release\elem.dll" ".\bin\"
	xcopy ".\build\Release\elem.lib" ".\lib\"
)
set /a "err=%err%+%errorlevel%"




::-----------------------
:: Restore to caller path
cd "%old_path%"
if not "%1" == "-s" if not "%2" == "-s" pause
exit /b %err%