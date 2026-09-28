# Visualizador de Árbol Rojo-Negro

Una aplicación gráfica interactiva para visualizar la estructura y operaciones de un Árbol Rojo-Negro.

## 📸 Características

- **Visualización en tiempo real** del árbol rojo-negro
- **Inserción interactiva** de nodos
- **Eliminación de nodos** con rebalanceo automático
- **Colores distintivos** para nodos rojos y negros
- **Interfaz intuitiva** con instrucciones en pantalla

## 🎮 Controles

| Tecla | Acción |
|-------|--------|
| `1-9` | Insertar el número correspondiente |
| `Shift + 1-9` | Eliminar el número correspondiente |
| `I` | Modo insertar (para números grandes) |
| `D` | Modo eliminar (para números grandes) |
| `R` | Insertar número aleatorio (1-100) |
| `+` | Insertar valor incremental (10, 20, 30...) |
| `C` | Limpiar el árbol |
| `ESC` | Salir |

### Modo Número Grande
Cuando presionas `I` o `D`, puedes escribir un número de varios dígitos y luego presionar `Enter` para confirmar.

## 🔧 Requisitos

- **Compilador**: MinGW g++ con soporte C++17
- **Biblioteca gráfica**: SFML 2.5+ ([Descargar](https://www.sfml-dev.org/download.php))

## 📦 Instalación de SFML

1. Descarga SFML de [sfml-dev.org](https://www.sfml-dev.org/download.php)
2. Extrae en `C:\SFML` (o modifica `build.bat` con tu ruta)
3. Copia los archivos DLL de `C:\SFML\bin` al directorio del proyecto

## 🔨 Compilación

### Usando build.bat
```batch
build.bat
```

### Manual
```batch
g++ -std=c++17 -I"C:\SFML\include" main.cpp -o ArbolRojoNegro.exe -L"C:\SFML\lib" -lsfml-graphics -lsfml-window -lsfml-system
```

## 📚 Sobre Árboles Rojo-Negro

Un árbol rojo-negro es un árbol binario de búsqueda auto-balanceado con las siguientes propiedades:

1. **Cada nodo es rojo o negro**
2. **La raíz siempre es negra**
3. **Las hojas (NIL) son negras**
4. **Si un nodo es rojo, sus hijos son negros**
5. **Todo camino desde la raíz a las hojas tiene el mismo número de nodos negros**

### Complejidad
- **Búsqueda**: O(log n)
- **Inserción**: O(log n)
- **Eliminación**: O(log n)

## 📁 Estructura del Proyecto

```
ArbolRojoNegro/
├── main.cpp           # Punto de entrada y lógica principal
├── RedBlackTree.hpp   # Implementación del árbol rojo-negro
├── Visualizador.hpp   # Clase para renderizado gráfico
├── build.bat          # Script de compilación
└── README.md          # Este archivo
```

## 🎨 Leyenda de Colores

- 🔴 **Rojo**: Nodo recién insertado o nodo rojo
- ⚫ **Negro**: Nodo negro (incluye la raíz)

## 👨‍💻 Autor

Creado para el curso de Estructura de Datos.
