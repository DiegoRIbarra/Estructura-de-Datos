#ifndef VISUALIZADOR_HPP
#define VISUALIZADOR_HPP

#include <SFML/Graphics.hpp>
#include "RedBlackTree.hpp"
#include <sstream>
#include <cmath>
#include <string>

class Visualizador {
private:
    sf::RenderWindow& ventana;
    sf::Font fuente;
    ArbolRojoNegro<int>& arbol;
    
    float radioNodo = 25.f;
    float separacionVertical = 80.f;
    float offsetY = 100.f;
    
    // Colores
    sf::Color colorRojo = sf::Color(220, 50, 50);
    sf::Color colorNegro = sf::Color(40, 40, 40);
    sf::Color colorFondo = sf::Color(245, 245, 245);
    sf::Color colorLinea = sf::Color(100, 100, 100);
    sf::Color colorTexto = sf::Color::White;
    
    void calcularPosiciones(Nodo<int>* nodo, float x, float y, float offset, int nivel) {
        if (nodo == arbol.getTNULL() || nodo == nullptr) return;
        
        nodo->x = x;
        nodo->y = y;
        
        float nuevoOffset = offset / 2.0f;
        
        if (nodo->izq != arbol.getTNULL()) {
            calcularPosiciones(nodo->izq, x - offset, y + separacionVertical, nuevoOffset, nivel + 1);
        }
        if (nodo->der != arbol.getTNULL()) {
            calcularPosiciones(nodo->der, x + offset, y + separacionVertical, nuevoOffset, nivel + 1);
        }
    }
    
    void dibujarLinea(float x1, float y1, float x2, float y2) {
        sf::Vertex linea[] = {
            sf::Vertex(sf::Vector2f(x1, y1), colorLinea),
            sf::Vertex(sf::Vector2f(x2, y2), colorLinea)
        };
        ventana.draw(linea, 2, sf::Lines);
    }
    
    void dibujarNodo(Nodo<int>* nodo) {
        if (nodo == arbol.getTNULL() || nodo == nullptr) return;
        
        // Dibujar líneas a los hijos primero
        if (nodo->izq != arbol.getTNULL()) {
            dibujarLinea(nodo->x, nodo->y, nodo->izq->x, nodo->izq->y);
        }
        if (nodo->der != arbol.getTNULL()) {
            dibujarLinea(nodo->x, nodo->y, nodo->der->x, nodo->der->y);
        }
        
        // Dibujar el círculo del nodo
        sf::CircleShape circulo(radioNodo);
        circulo.setOrigin(radioNodo, radioNodo);
        circulo.setPosition(nodo->x, nodo->y);
        circulo.setFillColor(nodo->color == ROJO ? colorRojo : colorNegro);
        circulo.setOutlineThickness(3.f);
        circulo.setOutlineColor(sf::Color(80, 80, 80));
        ventana.draw(circulo);
        
        // Dibujar el valor
        sf::Text texto;
        texto.setFont(fuente);
        texto.setString(std::to_string(nodo->dato));
        texto.setCharacterSize(16);
        texto.setFillColor(colorTexto);
        
        sf::FloatRect bounds = texto.getLocalBounds();
        texto.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        texto.setPosition(nodo->x, nodo->y);
        ventana.draw(texto);
        
        // Recursión para los hijos
        dibujarNodo(nodo->izq);
        dibujarNodo(nodo->der);
    }
    
public:
    Visualizador(sf::RenderWindow& win, ArbolRojoNegro<int>& arb) 
        : ventana(win), arbol(arb) {}
    
    bool cargarFuente(const std::string& ruta) {
        return fuente.loadFromFile(ruta);
    }
    
    void setFuente(const sf::Font& f) {
        fuente = f;
    }
    
    void dibujar() {
        if (arbol.estaVacio()) return;
        
        // Calcular posiciones de los nodos
        float anchoVentana = ventana.getSize().x;
        float offsetInicial = anchoVentana / 4.0f;
        
        // Ajustar offset según la altura del árbol
        int altura = arbol.getAltura();
        if (altura > 4) {
            offsetInicial = anchoVentana / (pow(2, altura - 2));
        }
        
        calcularPosiciones(arbol.getRaiz(), anchoVentana / 2.0f, offsetY, offsetInicial, 0);
        
        // Dibujar el árbol
        dibujarNodo(arbol.getRaiz());
    }
    
    void dibujarLeyenda() {
        float x = 20.f;
        float y = ventana.getSize().y - 100.f;
        
        // Cuadro de leyenda
        sf::RectangleShape fondo(sf::Vector2f(200.f, 90.f));
        fondo.setPosition(x - 10.f, y - 10.f);
        fondo.setFillColor(sf::Color(255, 255, 255, 230));
        fondo.setOutlineThickness(2.f);
        fondo.setOutlineColor(sf::Color(150, 150, 150));
        ventana.draw(fondo);
        
        // Nodo rojo
        sf::CircleShape circuloRojo(12.f);
        circuloRojo.setFillColor(colorRojo);
        circuloRojo.setPosition(x, y);
        ventana.draw(circuloRojo);
        
        sf::Text textoRojo;
        textoRojo.setFont(fuente);
        textoRojo.setString("= Nodo Rojo");
        textoRojo.setCharacterSize(14);
        textoRojo.setFillColor(sf::Color::Black);
        textoRojo.setPosition(x + 30.f, y);
        ventana.draw(textoRojo);
        
        // Nodo negro
        sf::CircleShape circuloNegro(12.f);
        circuloNegro.setFillColor(colorNegro);
        circuloNegro.setPosition(x, y + 35.f);
        ventana.draw(circuloNegro);
        
        sf::Text textoNegro;
        textoNegro.setFont(fuente);
        textoNegro.setString("= Nodo Negro");
        textoNegro.setCharacterSize(14);
        textoNegro.setFillColor(sf::Color::Black);
        textoNegro.setPosition(x + 30.f, y + 35.f);
        ventana.draw(textoNegro);
    }
    
    void dibujarInstrucciones() {
        float x = ventana.getSize().x - 280.f;
        float y = ventana.getSize().y - 130.f;
        
        sf::RectangleShape fondo(sf::Vector2f(270.f, 120.f));
        fondo.setPosition(x - 10.f, y - 10.f);
        fondo.setFillColor(sf::Color(255, 255, 255, 230));
        fondo.setOutlineThickness(2.f);
        fondo.setOutlineColor(sf::Color(150, 150, 150));
        ventana.draw(fondo);
        
        sf::Text texto;
        texto.setFont(fuente);
        texto.setCharacterSize(13);
        texto.setFillColor(sf::Color::Black);
        
        std::vector<std::string> instrucciones = {
            "Controles:",
            "1-9: Insertar numero",
            "Shift + 1-9: Eliminar numero",
            "R: Insertar aleatorio",
            "C: Limpiar arbol",
            "ESC: Salir"
        };
        
        for (size_t i = 0; i < instrucciones.size(); i++) {
            texto.setString(instrucciones[i]);
            texto.setPosition(x, y + i * 18.f);
            if (i == 0) texto.setStyle(sf::Text::Bold);
            else texto.setStyle(sf::Text::Regular);
            ventana.draw(texto);
        }
    }
    
    void dibujarTitulo() {
        sf::Text titulo;
        titulo.setFont(fuente);
        titulo.setString("Visualizador de Arbol Rojo-Negro");
        titulo.setCharacterSize(28);
        titulo.setFillColor(sf::Color(50, 50, 50));
        titulo.setStyle(sf::Text::Bold);
        
        sf::FloatRect bounds = titulo.getLocalBounds();
        titulo.setOrigin(bounds.left + bounds.width / 2.0f, 0);
        titulo.setPosition(ventana.getSize().x / 2.0f, 20.f);
        ventana.draw(titulo);
    }
    
    void dibujarInfo(const std::string& mensaje) {
        sf::Text info;
        info.setFont(fuente);
        info.setString(mensaje);
        info.setCharacterSize(16);
        info.setFillColor(sf::Color(70, 130, 180));
        
        sf::FloatRect bounds = info.getLocalBounds();
        info.setOrigin(bounds.left + bounds.width / 2.0f, 0);
        info.setPosition(ventana.getSize().x / 2.0f, 55.f);
        ventana.draw(info);
    }
};

#endif
