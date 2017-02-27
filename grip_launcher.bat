@if "%DEBUG%" == "" @echo off

rem this is only an if statement and prompt... :/
rem only made it to save the time of having to cd into the right dir on winshit

echo I had to make this to run the command for me...
echo Starting GRIP...

choice /c:ync /n /m "Run offline? (y/N/cancel)"

if errorlevel 3 exit

if errorlevel == 1 (
	echo running using previous build...
	gradlew.bat :ui:run --offline
) else (
	echo downloading and then running...
	gradlew.bat :ui:run
)

echo "Job completed, Have a good day :)"
