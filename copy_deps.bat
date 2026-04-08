@echo off
:: ===========================================
:: copy_dependencies.bat
:: Copies SFML DLLs and data folder next to binary
:: Does NOT overwrite existing files
:: Usage: copy_dependencies.bat <TargetDir> <Configuration>
:: ===========================================

:: Use %~1 and %~2 to strip any surrounding quotes
set "TARGETDIR=%~1"
set "CONFIG=%~2"

if "%TARGETDIR%"=="" (
    echo ERROR: No target directory specified
    exit /b 1
)

:: Ensure TARGETDIR ends with a backslash
if not "%TARGETDIR:~-1%"=="\" set "TARGETDIR=%TARGETDIR%\"

:: Determine SFML DLL suffix
if /I "%CONFIG%"=="Debug" (
    set "SUFFIX=-d-3.dll"
) else (
    set "SUFFIX=-3.dll"
)

echo Copying SFML DLLs for %CONFIG% to "%TARGETDIR%"...

:: List of SFML modules
set MODULES=graphics window system audio network
for %%M in (%MODULES%) do (
    if not exist "%TARGETDIR%sfml-%%M%SUFFIX%" (
        copy /Y "%~dp0SFML-3.0.2\bin\sfml-%%M%SUFFIX%" "%TARGETDIR%"
    )
)

:: Copy data folder
if exist "%~dp0data" (
    echo Copying data folder...
    xcopy "%~dp0data" "%TARGETDIR%data" /E /I /Y /Q
)

echo Dependencies copied successfully.