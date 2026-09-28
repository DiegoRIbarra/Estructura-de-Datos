#include <SFML/Graphics.hpp>
#include "RedBlackTree.hpp"
#include "Visualizador.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

int main() {
    // Semilla para números aleatorios
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    // Crear ventana
    sf::RenderWindow ventana(sf::VideoMode(1200, 750), "Arbol Rojo-Negro - Visualizador", sf::Style::Close);
    ventana.setFramerateLimit(60);
    
    // Crear árbol rojo-negro
    ArbolRojoNegro<int> arbol;
    
    // Crear visualizador
    Visualizador visualizador(ventana, arbol);
    
    // Cargar fuente
    sf::Font fuente;
    bool fuenteCargada = false;
    
    std::vector<std::string> rutasFuentes = {
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/segoeui.ttf",
        "C:/Windows/Fonts/calibri.ttf",
        "arial.ttf"
    };
    
    for (const auto& ruta : rutasFuentes) {
        if (fuente.loadFromFile(ruta)) {
            fuenteCargada = true;
            visualizador.setFuente(fuente);
            break;
        }
    }
    
    if (!fuenteCargada) {
        std::cerr << "Error: No se pudo cargar ninguna fuente." << std::endl;
        return -1;
    }
    
    // NO insertar valores iniciales - árbol vacío
    std::string mensajeInfo = "Escribe un numero y presiona Enter para insertar";
    
    // Input de texto
    std::string inputNumero = "";
    bool modoEliminar = false;
    bool cursorVisible = true;
    sf::Clock cursorClock;
    
    sf::Color colorFondo(240, 240, 245);
    
    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
            
            if (evento.type == sf::Event::KeyPressed) {
                // ESC para salir
                if (evento.key.code == sf::Keyboard::Escape) {
                    ventana.close();
                }
                
                // R para insertar aleatorio
                if (evento.key.code == sf::Keyboard::R && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    int valorAleatorio = std::rand() % 100 + 1;
                    arbol.insertar(valorAleatorio);
                    mensajeInfo = "Insertado aleatorio: " + std::to_string(valorAleatorio);
                }
                
                // C para limpiar el árbol
                if (evento.key.code == sf::Keyboard::C && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    arbol.~ArbolRojoNegro();
                    new (&arbol) ArbolRojoNegro<int>();
                    mensajeInfo = "Arbol limpiado";
                    inputNumero = "";
                }
                
                // Tab para cambiar entre modo insertar/eliminar
                if (evento.key.code == sf::Keyboard::Tab) {
                    modoEliminar = !modoEliminar;
                    mensajeInfo = modoEliminar ? "Modo: ELIMINAR" : "Modo: INSERTAR";
                }
                
                // Enter para confirmar
                if (evento.key.code == sf::Keyboard::Enter) {
                    if (!inputNumero.empty()) {
                        try {
                            int valor = std::stoi(inputNumero);
                            if (modoEliminar) {
                                arbol.eliminar(valor);
                                mensajeInfo = "Eliminado: " + std::to_string(valor);
                            } else {
                                arbol.insertar(valor);
                                mensajeInfo = "Insertado: " + std::to_string(valor);
                            }
                        } catch (...) {
                            mensajeInfo = "Numero invalido";
                        }
                        inputNumero = "";
                    }
                }
                
                // Backspace para borrar
                if (evento.key.code == sf::Keyboard::BackSpace) {
                    if (!inputNumero.empty()) {
                        inputNumero.pop_back();
                    }
                }
                
                // Delete para limpiar input
                if (evento.key.code == sf::Keyboard::Delete) {
                    inputNumero = "";
                }
            }
            
            // Entrada de texto
            if (evento.type == sf::Event::TextEntered) {
                char c = static_cast<char>(evento.text.unicode);
                // Solo números y signo negativo al inicio
                if (c >= '0' && c <= '9') {
                    if (inputNumero.length() < 6) { // Máximo 6 dígitos
                        inputNumero += c;
                    }
                } else if (c == '-' && inputNumero.empty()) {
                    inputNumero += c;
                }
            }
        }
        
        // Cursor parpadeante
        if (cursorClock.getElapsedTime().asMilliseconds() > 500) {
            cursorVisible = !cursorVisible;
            cursorClock.restart();
        }
        
        // Dibujar
        ventana.clear(colorFondo);
        
        // Título
        sf::Text titulo;
        titulo.setFont(fuente);
        titulo.setString("Visualizador de Arbol Rojo-Negro");
        titulo.setCharacterSize(28);
        titulo.setFillColor(sf::Color(50, 50, 50));
        titulo.setStyle(sf::Text::Bold);
        sf::FloatRect titleBounds = titulo.getLocalBounds();
        titulo.setOrigin(titleBounds.width / 2.0f, 0);
        titulo.setPosition(ventana.getSize().x / 2.0f, 15.f);
        ventana.draw(titulo);
        
        // === CAMPO DE ENTRADA DE TEXTO ===
        float inputX = ventana.getSize().x / 2.0f - 150.f;
        float inputY = 55.f;
        
        // Fondo del campo de entrada
        sf::RectangleShape inputBox(sf::Vector2f(200.f, 35.f));
        inputBox.setPosition(inputX, inputY);
        inputBox.setFillColor(sf::Color::White);
        inputBox.setOutlineThickness(2.f);
        inputBox.setOutlineColor(modoEliminar ? sf::Color(220, 50, 50) : sf::Color(70, 130, 180));
        ventana.draw(inputBox);
        
        // Texto dentro del campo
        sf::Text inputText;
        inputText.setFont(fuente);
        std::string displayText = inputNumero;
        if (cursorVisible) displayText += "|";
        inputText.setString(displayText.empty() && !cursorVisible ? "Escribe aqui..." : displayText);
        inputText.setCharacterSize(18);
        inputText.setFillColor(inputNumero.empty() ? sf::Color(150, 150, 150) : sf::Color::Black);
        inputText.setPosition(inputX + 10.f, inputY + 5.f);
        ventana.draw(inputText);
        
        // Botón Insertar/Eliminar (indicador de modo)
        sf::RectangleShape modeButton(sf::Vector2f(100.f, 35.f));
        modeButton.setPosition(inputX + 210.f, inputY);
        modeButton.setFillColor(modoEliminar ? sf::Color(220, 50, 50) : sf::Color(50, 150, 50));
        ventana.draw(modeButton);
        
        sf::Text modeText;
        modeText.setFont(fuente);
        modeText.setString(modoEliminar ? "ELIMINAR" : "INSERTAR");
        modeText.setCharacterSize(14);
        modeText.setFillColor(sf::Color::White);
        sf::FloatRect modeBounds = modeText.getLocalBounds();
        modeText.setOrigin(modeBounds.width / 2.0f, modeBounds.height / 2.0f);
        modeText.setPosition(inputX + 260.f, inputY + 15.f);
        ventana.draw(modeText);
        
        // Mensaje de información
        sf::Text info;
        info.setFont(fuente);
        info.setString(mensajeInfo);
        info.setCharacterSize(14);
        info.setFillColor(sf::Color(100, 100, 100));
        sf::FloatRect infoBounds = info.getLocalBounds();
        info.setOrigin(infoBounds.width / 2.0f, 0);
        info.setPosition(ventana.getSize().x / 2.0f, inputY + 40.f);
        ventana.draw(info);
        
        // Dibujar el árbol
        visualizador.dibujar();
        
        // === PANEL DE CONTROLES ===
        float panelX = 20.f;
        float panelY = ventana.getSize().y - 160.f;
        
        sf::RectangleShape panelFondo(sf::Vector2f(280.f, 150.f));
        panelFondo.setPosition(panelX - 10.f, panelY - 10.f);
        panelFondo.setFillColor(sf::Color(255, 255, 255, 240));
        panelFondo.setOutlineThickness(2.f);
        panelFondo.setOutlineColor(sf::Color(150, 150, 150));
        ventana.draw(panelFondo);
        
        sf::Text controles;
        controles.setFont(fuente);
        controles.setCharacterSize(13);
        controles.setFillColor(sf::Color::Black);
        
        std::vector<std::string> lineas = {
            "CONTROLES:",
            "Escribe numeros + Enter: Insertar/Eliminar",
            "Tab: Cambiar modo (Insertar/Eliminar)",
            "R: Insertar numero aleatorio",
            "C: Limpiar arbol",
            "Backspace: Borrar digito",
            "Delete: Limpiar campo",
            "ESC: Salir"
        };
        
        for (size_t i = 0; i < lineas.size(); i++) {
            controles.setString(lineas[i]);
            controles.setPosition(panelX, panelY + i * 17.f);
            if (i == 0) controles.setStyle(sf::Text::Bold);
            else controles.setStyle(sf::Text::Regular);
            ventana.draw(controles);
        }
        
        // === LEYENDA ===
        float leyendaX = ventana.getSize().x - 180.f;
        float leyendaY = ventana.getSize().y - 100.f;
        
        sf::RectangleShape leyendaFondo(sf::Vector2f(170.f, 90.f));
        leyendaFondo.setPosition(leyendaX - 10.f, leyendaY - 10.f);
        leyendaFondo.setFillColor(sf::Color(255, 255, 255, 240));
        leyendaFondo.setOutlineThickness(2.f);
        leyendaFondo.setOutlineColor(sf::Color(150, 150, 150));
        ventana.draw(leyendaFondo);
        
        sf::Text leyendaTitulo;
        leyendaTitulo.setFont(fuente);
        leyendaTitulo.setString("LEYENDA:");
        leyendaTitulo.setCharacterSize(13);
        leyendaTitulo.setFillColor(sf::Color::Black);
        leyendaTitulo.setStyle(sf::Text::Bold);
        leyendaTitulo.setPosition(leyendaX, leyendaY);
        ventana.draw(leyendaTitulo);
        
        // Nodo rojo
        sf::CircleShape circuloRojo(10.f);
        circuloRojo.setFillColor(sf::Color(220, 50, 50));
        circuloRojo.setPosition(leyendaX, leyendaY + 25.f);
        ventana.draw(circuloRojo);
        
        sf::Text textoRojo;
        textoRojo.setFont(fuente);
        textoRojo.setString("= Nodo Rojo");
        textoRojo.setCharacterSize(12);
        textoRojo.setFillColor(sf::Color::Black);
        textoRojo.setPosition(leyendaX + 25.f, leyendaY + 27.f);
        ventana.draw(textoRojo);
        
        // Nodo negro
        sf::CircleShape circuloNegro(10.f);
        circuloNegro.setFillColor(sf::Color(40, 40, 40));
        circuloNegro.setPosition(leyendaX, leyendaY + 50.f);
        ventana.draw(circuloNegro);
        
        sf::Text textoNegro;
        textoNegro.setFont(fuente);
        textoNegro.setString("= Nodo Negro");
        textoNegro.setCharacterSize(12);
        textoNegro.setFillColor(sf::Color::Black);
        textoNegro.setPosition(leyendaX + 25.f, leyendaY + 52.f);
        ventana.draw(textoNegro);
        
        ventana.display();
    }
    
    return 0;
}
