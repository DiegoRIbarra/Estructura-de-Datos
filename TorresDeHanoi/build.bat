@echo off
REM --- CONFIGURACION ---
set SFML_PATH=C:\SFML
set COMPILER_PATH=C:\mingw64\bin\g++.exe

REM --- Archivos fuente ---
set SOURCE_FILES=main.cpp Game.cpp RoundedButton.cpp
set OUTPUT_EXE=Hanoi.exe

REM --- FIN DE CONFIGURACION ---

echo [COMPILANDO %SOURCE_FILES% en modo DEBUG...]
echo.

if exist %OUTPUT_EXE% (
    del %OUTPUT_EXE%
)

REM --- Comando de Compilación ---
"%COMPILER_PATH%" -g %SOURCE_FILES% -o %OUTPUT_EXE% -I"%SFML_PATH%\include" -L"%SFML_PATH%\lib" -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -mwindows

if errorlevel 1 (
    echo.
    echo [!!! ERROR: Hubo un problema al compilar. !!!]
) else (
    echo.
    echo [=== EXITO: Se creo %OUTPUT_EXE% ===]
    echo.
    echo [Ejecutando el juego...]
    start %OUTPUT_EXE%
)

:end
echo.
pause