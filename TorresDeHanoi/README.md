# 🗼 Torres de Hanoi - Documentación Completa

## 📋 Índice
1. [Descripción del Proyecto](#descripción-del-proyecto)
2. [El Problema de las Torres de Hanoi](#el-problema-de-las-torres-de-hanoi)
3. [Tecnologías Utilizadas](#tecnologías-utilizadas)
4. [Estructura del Proyecto](#estructura-del-proyecto)
5. [Arquitectura y Flujo del Programa](#arquitectura-y-flujo-del-programa)
6. [Análisis Detallado de Cada Archivo](#análisis-detallado-de-cada-archivo)
7. [Máquina de Estados](#máquina-de-estados)
8. [Algoritmo de Auto-Resolución](#algoritmo-de-auto-resolución)
9. [Compilación y Ejecución](#compilación-y-ejecución)
10. [Diagrama de Clases](#diagrama-de-clases)

---

## 📖 Descripción del Proyecto

Este proyecto implementa una **versión gráfica interactiva** del clásico rompecabezas matemático "Torres de Hanoi" utilizando **C++** y la biblioteca **SFML** (Simple and Fast Multimedia Library) para los gráficos.

### Características principales:
- ✅ Interfaz gráfica intuitiva con botones redondeados
- ✅ Selección de dificultad (3 a 8 discos)
- ✅ Animaciones suaves de movimiento de discos
- ✅ Sistema de Auto-Resolución que muestra la solución óptima
- ✅ Contador de movimientos
- ✅ Detección automática de victoria

---

## 🧩 El Problema de las Torres de Hanoi

### Historia
El problema fue inventado por el matemático francés **Édouard Lucas** en 1883. Consiste en mover una pila de discos de una torre a otra, siguiendo reglas específicas.

### Reglas del juego:
1. Solo se puede mover **un disco a la vez**
2. Un disco solo puede colocarse sobre otro **más grande** (nunca sobre uno más pequeño)
3. Solo se puede mover el disco que está en la **cima** de una torre

### Complejidad matemática:
- **Número mínimo de movimientos**: $2^n - 1$ donde $n$ es el número de discos
- Ejemplo: Para 3 discos → $2^3 - 1 = 7$ movimientos
- Para 8 discos → $2^8 - 1 = 255$ movimientos

---

## 🛠️ Tecnologías Utilizadas

| Tecnología | Propósito |
|------------|-----------|
| **C++** | Lenguaje de programación principal |
| **SFML 2.x** | Biblioteca para gráficos, ventanas y eventos |
| **MinGW-w64** | Compilador g++ para Windows |

### ¿Por qué SFML?
- API simple y orientada a objetos
- Soporte multiplataforma (Windows, Linux, macOS)
- Manejo eficiente de gráficos 2D, eventos y texto

---

## 📁 Estructura del Proyecto

```
TorresDeHanoi/
│
├── main.cpp           # Punto de entrada del programa
├── Game.hpp           # Declaración de la clase Game (cabecera)
├── Game.cpp           # Implementación de la lógica del juego
├── Config.hpp         # Configuración global (constantes)
├── RoundedButton.hpp  # Declaración de botones redondeados
├── RoundedButton.cpp  # Implementación de botones
├── build.bat          # Script de compilación para Windows
├── Hanoi.exe          # Ejecutable compilado
└── arial.ttf          # Fuente (opcional, usa la del sistema)
```

### Diagrama de dependencias:
```
                    ┌─────────────┐
                    │   main.cpp  │
                    └──────┬──────┘
                           │ incluye
                           ▼
                    ┌─────────────┐
                    │  Game.hpp   │
                    └──────┬──────┘
                           │ incluye
              ┌────────────┼────────────┐
              ▼            ▼            ▼
       ┌───────────┐ ┌───────────┐ ┌──────────────────┐
       │Config.hpp │ │ SFML Libs │ │RoundedButton.hpp │
       └───────────┘ └───────────┘ └──────────────────┘
```

---

## 🔄 Arquitectura y Flujo del Programa

### Flujo General de Ejecución

```
┌─────────────────────────────────────────────────────────────────┐
│                         main.cpp                                 │
│  1. Crea instancia de Game                                       │
│  2. Llama a game.run() → Inicia el bucle principal              │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                    Game::run() - BUCLE PRINCIPAL                │
│                                                                  │
│  while (ventana abierta) {                                       │
│      1. Preparar frame (resetear banderas)                      │
│      2. Procesar eventos (según estado actual)                  │
│      3. Actualizar lógica (animaciones, win condition)          │
│      4. Aplicar cambio de estado                                │
│      5. Renderizar (dibujar según estado)                       │
│  }                                                               │
└─────────────────────────────────────────────────────────────────┘
```

### El Game Loop Detallado

```cpp
void Game::run() {
    while (mWindow.isOpen()) {
        // 1. PREPARAR FRAME
        mNextState = mCurrentState;      // Asume que no cambia
        mButtonClickedThisFrame = false; // Reset bandera
        
        // 2. PROCESAR EVENTOS
        while (mWindow.pollEvent(event)) {
            switch (mCurrentState) {
                case SETUP:    processSetupEvents(event);    break;
                case PLAYING:  processPlayingEvents(event);  break;
                case ANIMATING: /* No procesa input */       break;
                case JUEGO_TERMINADO: processTerminadoEvents(event); break;
            }
        }
        
        // 3. ACTUALIZAR LÓGICA
        if (mCurrentState == ANIMATING)  updateAnimation();
        if (mCurrentState == PLAYING)    updatePlaying();
        checkWinCondition();
        
        // 4. APLICAR CAMBIO DE ESTADO
        mCurrentState = mNextState;  // ¡Importante! Cambio retrasado
        
        // 5. RENDERIZAR
        mWindow.clear(Config::BG_COLOR);
        switch (mCurrentState) {
            case SETUP:          renderSetup();   break;
            case PLAYING/ANIMATING: renderPlaying(); break;
            case JUEGO_TERMINADO:   renderPlaying(); renderAlerta(); break;
        }
        mWindow.display();
    }
}
```

---

## 📄 Análisis Detallado de Cada Archivo

### 1. `main.cpp` - Punto de Entrada

```cpp
#include "Game.hpp"

int main() {
    Game hanoiGame;    // Crea el juego (inicializa todo)
    hanoiGame.run();   // Ejecuta el bucle principal
    return 0;
}
```

**Responsabilidad**: Única responsabilidad de iniciar la aplicación. Sigue el principio **KISS** (Keep It Simple, Stupid).

---

### 2. `Config.hpp` - Configuración Global

Este archivo define todas las **constantes** del juego en un namespace `Config`:

```cpp
namespace Config {
    // Dimensiones de ventana
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 600;
    
    // Límites de dificultad
    const int MIN_DISKS = 3;
    const int MAX_DISKS = 8;
    
    // Dimensiones de elementos
    const float TOWER_WIDTH = 20.f;
    const float DISK_HEIGHT = 25.f;
    const float DISK_WIDTH_BASE = 50.f;   // Ancho mínimo del disco más pequeño
    const float DISK_WIDTH_STEP = 30.f;   // Incremento por cada tamaño
    
    // Animación
    const float ANIMATION_HEIGHT = 150.f;  // Altura a la que "vuelan" los discos
    const float ANIMATION_SPEED = 0.15f;   // Factor de interpolación (0-1)
    
    // Colores (usando sf::Color de SFML)
    const sf::Color BG_COLOR(24, 28, 31);         // Fondo oscuro
    const sf::Color TOWER_COLOR(200, 200, 200);   // Torres grises
    const sf::Color TEXT_COLOR(230, 230, 230);    // Texto claro
    
    // Paleta de colores para discos (8 colores)
    const std::vector<sf::Color> DISK_COLORS = {
        sf::Color(230, 57, 70),   // Rojo
        sf::Color(241, 150, 52),  // Naranja
        sf::Color(249, 199, 79),  // Amarillo
        // ... más colores
    };
}
```

**¿Por qué usar un namespace?**
- Evita conflictos de nombres con otras partes del código
- Agrupa todas las configuraciones en un solo lugar
- Facilita modificar el aspecto del juego sin tocar la lógica

---

### 3. `Game.hpp` - Declaración de la Clase Principal

Define la **interfaz** de la clase `Game`:

#### Estados del Juego (enum class)
```cpp
enum class GameState {
    SETUP,           // Pantalla de selección de dificultad
    PLAYING,         // Jugando (esperando input del usuario)
    ANIMATING,       // Animando movimiento de disco
    JUEGO_TERMINADO  // Pantalla de victoria
};
```

#### Estructura de la Clase
```cpp
class Game {
public:
    Game();           // Constructor
    void run();       // Bucle principal
    
private:
    // --- MÉTODOS POR ESTADO ---
    void setupSetupUI();        void processSetupEvents();      void renderSetup();
    void setupGameUI();         void processPlayingEvents();    void renderPlaying();
    void setupAlertaUI();       void processTerminadoEvents();  void renderAlerta();
    
    // --- LÓGICA DE JUEGO ---
    void handleClick(int mouseX);      // Maneja clics en torres
    bool tryMove(int targetTower);     // Valida movimiento
    void checkWinCondition();          // ¿Ganó el jugador?
    
    // --- ANIMACIÓN ---
    void updateAnimation();            // Interpola posición del disco
    
    // --- AUTO-RESOLVER ---
    void buildSolutionMoves(int n, int from, int to, int aux);
    void startAutoMove(int from, int to);
    
    // --- VARIABLES DE ESTADO ---
    sf::RenderWindow mWindow;
    GameState mCurrentState, mNextState;
    std::vector<std::vector<int>> mTowers;  // Las 3 torres con sus discos
    int mNumDisks, mMoveCount;
    // ... más variables
};
```

---

### 4. `Game.cpp` - Implementación Principal

#### Constructor
```cpp
Game::Game() 
    : mWindow(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Torres de Hanoi"),
      mCurrentState(GameState::SETUP),
      mNumDisks(Config::MIN_DISKS),
      // ... inicializaciones
{
    mTowers.resize(3);  // Crea 3 vectores (uno por torre)
    mWindow.setVerticalSyncEnabled(true);  // Evita tearing
    
    // Carga fuente
    mFont.loadFromFile("arial.ttf");
    
    // Configura todas las UIs
    setupTowerShapes();
    setupSetupUI();
    setupGameUI();
    setupAlertaUI();
}
```

#### Estructura de Datos: Las Torres
```cpp
std::vector<std::vector<int>> mTowers;
// mTowers[0] = Torre izquierda
// mTowers[1] = Torre central
// mTowers[2] = Torre derecha

// Cada vector contiene enteros representando el TAMAÑO del disco
// Ejemplo con 3 discos en torre 0: mTowers[0] = {3, 2, 1}
//   - 3 está en la BASE (índice 0)
//   - 1 está en la CIMA (último índice)
```

#### Manejo de Clics
```cpp
void Game::handleClick(int mouseX) {
    int clickedTower = getTowerAt(mouseX);  // ¿En qué torre hizo clic?
    
    if (mIsHoldingDisk) {
        // INTENTANDO SOLTAR
        if (tryMove(clickedTower)) {
            // Movimiento válido → Inicia animación
            mNextState = GameState::ANIMATING;
            mAnimStage = 1;  // Etapa: cruzando horizontalmente
        } else {
            // Movimiento inválido → Devuelve disco a su torre
            mTowers[mSourceTower].push_back(mHeldDiskSize);
            mIsHoldingDisk = false;
        }
    } else {
        // INTENTANDO LEVANTAR
        if (!mTowers[clickedTower].empty()) {
            mHeldDiskSize = mTowers[clickedTower].back();  // Toma el de arriba
            mTowers[clickedTower].pop_back();              // Lo quita de la torre
            mIsHoldingDisk = true;
            mSourceTower = clickedTower;
        }
    }
}
```

#### Validación de Movimiento
```cpp
bool Game::tryMove(int targetTower) {
    // Regla 1: No puede soltarse en la misma torre
    if (targetTower == mSourceTower) return false;
    
    // Regla 2: Siempre puede soltarse en torre vacía
    if (mTowers[targetTower].empty()) return true;
    
    // Regla 3: Solo si el disco es más pequeño que el de arriba
    int topDisk = mTowers[targetTower].back();
    return mHeldDiskSize < topDisk;
}
```

#### Sistema de Animación (Interpolación)
```cpp
void Game::updateAnimation() {
    sf::Vector2f pos = mAnimatingDisk.getPosition();
    sf::Vector2f target = mAnimTargetPos;
    
    // Interpolación suavizada: mueve 15% de la distancia restante cada frame
    sf::Vector2f delta = (target - pos) * Config::ANIMATION_SPEED;
    mAnimatingDisk.setPosition(pos + delta);
    
    // Cuando llega al destino...
    if (llegóAlDestino) {
        if (mAnimStage == 1) {
            // Etapa 1 completada: ahora baja
            mAnimStage = 2;
            mAnimTargetPos.y = calcularAlturaEnTorre();
        } else if (mAnimStage == 2) {
            // Etapa 2 completada: coloca el disco
            mTowers[mAnimTargetTower].push_back(mHeldDiskSize);
            mMoveCount++;
            mNextState = GameState::PLAYING;
        }
    }
}
```

**Fases de la animación:**
```
       Etapa 1: Cruzar horizontalmente
    ┌────────────────────────────────────┐
    │  ████                        ████  │  ← ANIMATION_HEIGHT
    │   │                            │   │
    │   │                            │   │
    └───┴────────────────────────────┴───┘
       FROM                         TO
       
       Etapa 2: Bajar verticalmente
    ┌────────────────────────────────────┐
    │                              ████  │
    │                                │   │
    │                              ████  │  ← Posición final
    └────────────────────────────────────┘
```

---

### 5. `RoundedButton.hpp` y `RoundedButton.cpp`

Implementa botones con **esquinas redondeadas** usando composición de formas SFML:

```cpp
class RoundedButton {
private:
    sf::CircleShape mLeftCap;     // Semicírculo izquierdo
    sf::CircleShape mRightCap;    // Semicírculo derecho
    sf::RectangleShape mMiddle;   // Rectángulo central
    sf::Text mText;               // Texto del botón
};
```

**Visualización:**
```
    ┌────────────────────────────┐
    │ ◯│      TEXTO      │◯ │
    └────────────────────────────┘
     Cap    Middle       Cap
```

#### Métodos principales:
```cpp
void init(label, width, height, font, x, y);  // Inicializa el botón
void setFillColor(color);                      // Cambia color (hover)
void draw(window);                             // Dibuja las 3 partes + texto
sf::FloatRect getGlobalBounds();               // Para detectar clics
```

---

### 6. `build.bat` - Script de Compilación

```batch
@echo off
set SFML_PATH=C:\SFML
set COMPILER_PATH=C:\mingw64\bin\g++.exe

set SOURCE_FILES=main.cpp Game.cpp RoundedButton.cpp
set OUTPUT_EXE=Hanoi.exe

"%COMPILER_PATH%" -g %SOURCE_FILES% -o %OUTPUT_EXE% ^
    -I"%SFML_PATH%\include" ^
    -L"%SFML_PATH%\lib" ^
    -lsfml-graphics-d -lsfml-window-d -lsfml-system-d ^
    -mwindows

start %OUTPUT_EXE%
```

**Flags importantes:**
| Flag | Significado |
|------|-------------|
| `-g` | Incluir info de debug |
| `-I` | Ruta de headers de SFML |
| `-L` | Ruta de librerías de SFML |
| `-l` | Enlazar librerías específicas |
| `-mwindows` | Ocultar consola (solo ventana gráfica) |

---

## 🔀 Máquina de Estados

El juego utiliza una **máquina de estados finitos** para controlar el flujo:

```
                    ┌─────────────────────────────┐
                    │                             │
                    ▼                             │
              ┌──────────┐                        │
     START───►│  SETUP   │◄───────────────┐      │
              └────┬─────┘                │      │
                   │ Click "JUGAR"        │      │
                   ▼                      │      │
              ┌──────────┐         Click  │      │
              │ PLAYING  │◄────┐   "Fin"  │      │
              └────┬─────┘     │          │      │
                   │           │          │      │
        Levanta    │           │          │      │
        y suelta   │           │          │      │
        disco      │           │          │      │
                   ▼           │          │      │
              ┌───────────┐    │          │      │
              │ ANIMATING │────┘          │      │
              └─────┬─────┘               │      │
                    │ Todos los discos    │      │
                    │ en torre 2 o 3      │      │
                    ▼                     │      │
              ┌────────────────┐          │      │
              │JUEGO_TERMINADO │──────────┘      │
              └───────┬────────┘                 │
                      │ Click "Salir"            │
                      └──────────────────────────┘
```

### ¿Por qué usar `mNextState` en lugar de cambiar directamente?

```cpp
// ❌ PROBLEMA: Cambio inmediato puede causar bugs
mCurrentState = GameState::PLAYING;  // Si se hace dentro de processSetupEvents
// ... el resto del frame aún usa SETUP para algunas cosas

// ✅ SOLUCIÓN: Cambio retrasado
mNextState = GameState::PLAYING;     // Marca el cambio
// ... al final del frame:
mCurrentState = mNextState;          // Aplica el cambio
```

---

## 🤖 Algoritmo de Auto-Resolución

El algoritmo utiliza **recursión** para generar la secuencia óptima de movimientos:

### Algoritmo Recursivo
```cpp
void Game::buildSolutionMoves(int n, int from, int to, int aux) {
    if (n <= 0) return;  // Caso base
    
    // 1. Mover n-1 discos de 'from' a 'aux' (usando 'to' como auxiliar)
    buildSolutionMoves(n - 1, from, aux, to);
    
    // 2. Mover el disco más grande de 'from' a 'to'
    mAutoMoves.emplace_back(from, to);
    
    // 3. Mover n-1 discos de 'aux' a 'to' (usando 'from' como auxiliar)
    buildSolutionMoves(n - 1, aux, to, from);
}
```

### Ejemplo con 3 discos:
```
Llamada inicial: buildSolutionMoves(3, 0, 2, 1)
                 (Mover 3 discos de torre 0 a torre 2)

Movimientos generados:
1. Disco 1: Torre 0 → Torre 2
2. Disco 2: Torre 0 → Torre 1
3. Disco 1: Torre 2 → Torre 1
4. Disco 3: Torre 0 → Torre 2  ← El disco más grande
5. Disco 1: Torre 1 → Torre 0
6. Disco 2: Torre 1 → Torre 2
7. Disco 1: Torre 0 → Torre 2

Total: 2³ - 1 = 7 movimientos
```

### Visualización del Árbol de Recursión (n=3):
```
buildSolution(3, 0→2, aux=1)
├── buildSolution(2, 0→1, aux=2)
│   ├── buildSolution(1, 0→2, aux=1) → move(0,2)
│   ├── move(0,1)
│   └── buildSolution(1, 2→1, aux=0) → move(2,1)
├── move(0,2)  ← DISCO GRANDE
└── buildSolution(2, 1→2, aux=0)
    ├── buildSolution(1, 1→0, aux=2) → move(1,0)
    ├── move(1,2)
    └── buildSolution(1, 0→2, aux=1) → move(0,2)
```

---

## ⚙️ Compilación y Ejecución

### Requisitos:
1. **MinGW-w64** instalado (g++ compiler)
2. **SFML 2.x** instalado y configurado
3. Archivos DLL de SFML en el mismo directorio o en PATH

### Opción 1: Usar build.bat
```batch
cd TorresDeHanoi
build.bat
```

### Opción 2: Compilar manualmente
```powershell
g++ -g main.cpp Game.cpp RoundedButton.cpp -o Hanoi.exe `
    -IC:\SFML\include -LC:\SFML\lib `
    -lsfml-graphics -lsfml-window -lsfml-system -mwindows
```

### Opción 3: Ejecutar el archivo ya compilado
```powershell
cd TorresDeHanoi
.\Hanoi.exe
```

---

## 📊 Diagrama de Clases UML

```
┌─────────────────────────────────────────────────────────────┐
│                          Game                                │
├─────────────────────────────────────────────────────────────┤
│ - mWindow: sf::RenderWindow                                  │
│ - mFont: sf::Font                                           │
│ - mCurrentState: GameState                                   │
│ - mNextState: GameState                                      │
│ - mTowers: vector<vector<int>>    ← Estructura de datos     │
│ - mNumDisks: int                                             │
│ - mMoveCount: int                                            │
│ - mIsHoldingDisk: bool                                       │
│ - mAutoMoves: vector<pair<int,int>>                         │
├─────────────────────────────────────────────────────────────┤
│ + Game()                                                     │
│ + run(): void                                                │
│ - processSetupEvents(): void                                 │
│ - processPlayingEvents(): void                               │
│ - processTerminadoEvents(): void                             │
│ - handleClick(mouseX: int): void                            │
│ - tryMove(targetTower: int): bool                           │
│ - checkWinCondition(): void                                  │
│ - updateAnimation(): void                                    │
│ - buildSolutionMoves(n,from,to,aux): void                   │
│ - startAutoMove(from,to): void                              │
└─────────────────────────────────────────────────────────────┘
                              │
                              │ usa
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                      RoundedButton                           │
├─────────────────────────────────────────────────────────────┤
│ - mLeftCap: sf::CircleShape                                 │
│ - mRightCap: sf::CircleShape                                │
│ - mMiddle: sf::RectangleShape                               │
│ - mText: sf::Text                                           │
│ - mPosition: sf::Vector2f                                   │
│ - mWidth, mHeight: float                                    │
├─────────────────────────────────────────────────────────────┤
│ + init(label, width, height, font, x, y): void              │
│ + setFillColor(color): void                                 │
│ + setPosition(x, y): void                                   │
│ + move(dx, dy): void                                        │
│ + getGlobalBounds(): sf::FloatRect                          │
│ + draw(window): void                                        │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────┐
│      «enumeration»          │
│        GameState            │
├─────────────────────────────┤
│ SETUP                       │
│ PLAYING                     │
│ ANIMATING                   │
│ JUEGO_TERMINADO             │
└─────────────────────────────┘

┌─────────────────────────────┐
│      «namespace»            │
│        Config               │
├─────────────────────────────┤
│ WINDOW_WIDTH: int           │
│ WINDOW_HEIGHT: int          │
│ MIN_DISKS: int              │
│ MAX_DISKS: int              │
│ TOWER_WIDTH: float          │
│ DISK_HEIGHT: float          │
│ ANIMATION_SPEED: float      │
│ BG_COLOR: sf::Color         │
│ DISK_COLORS: vector<Color>  │
└─────────────────────────────┘
```

---

## 🎯 Puntos Clave para la Exposición

### 1. **Estructura de Datos Principal**
- `vector<vector<int>>` representa las 3 torres como pilas (LIFO)
- Uso de `push_back()` y `pop_back()` para mover discos

### 2. **Patrón de Diseño: Máquina de Estados**
- Separación clara de responsabilidades por estado
- Cambio de estado retrasado (`mNextState`) para evitar bugs

### 3. **Algoritmo Recursivo**
- Complejidad $O(2^n)$ para generar los movimientos
- Demuestra el principio de "divide y vencerás"

### 4. **Separación de Intereses**
- `Config.hpp`: Configuración
- `Game.*`: Lógica del juego
- `RoundedButton.*`: Componente UI reutilizable

### 5. **Game Loop Clásico**
- Procesar eventos → Actualizar lógica → Renderizar
- VSync para sincronización con el monitor

---

## 📝 Preguntas Frecuentes de Defensa

**P: ¿Por qué usas `vector<vector<int>>` y no una estructura Stack?**
R: `std::vector` ya proporciona operaciones de pila (`push_back`, `pop_back`, `back`) y es más flexible para iterar y renderizar.

**P: ¿Qué pasa si el jugador intenta hacer un movimiento inválido?**
R: La función `tryMove()` retorna `false` y el disco regresa a su torre original.

**P: ¿Por qué la animación tiene 2 etapas?**
R: Etapa 1 mueve horizontalmente, etapa 2 mueve verticalmente. Esto crea un efecto visual de "arco" más natural.

**P: ¿Cómo detectas la victoria?**
R: `checkWinCondition()` verifica si `mTowers[1].size() == mNumDisks` o `mTowers[2].size() == mNumDisks`.

---

## 👨‍💻 Autor

Proyecto desarrollado para la materia de **Estructura de Datos**.

---

*Última actualización: Diciembre 2024*
