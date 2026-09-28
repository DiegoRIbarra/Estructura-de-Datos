@echo off
echo Compilando Visualizador de Arbol Rojo-Negro...

REM Verificar si SFML esta instalado
if not exist "C:\SFML\include\SFML\Graphics.hpp" (
    echo.
    echo ADVERTENCIA: SFML no encontrado en C:\SFML
    echo Por favor, asegurate de tener SFML instalado.
    echo.
    echo Puedes descargarlo de: https://www.sfml-dev.org/download.php
    echo.
    echo Si SFML esta en otra ubicacion, modifica este archivo.
    echo.
)

REM Compilar con g++
g++ -std=c++17 ^
    -I"C:\SFML\include" ^
    main.cpp ^
    -o ArbolRojoNegro.exe ^
    -L"C:\SFML\lib" ^
    -lsfml-graphics -lsfml-window -lsfml-system ^
    -mwindows

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Compilacion exitosa!
    echo Ejecuta ArbolRojoNegro.exe para iniciar el programa.
) else (
    echo.
    echo Error en la compilacion.
    echo Verifica que SFML este instalado correctamente.
)

pause
