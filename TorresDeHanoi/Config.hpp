// --- Config.hpp ---
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

// --- Configuración Global ---
namespace Config
{
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 600;

    const int MIN_DISKS = 3;
    const int MAX_DISKS = 8;

    const float TOWER_WIDTH = 20.f;
    const float DISK_HEIGHT = 25.f;
    const float DISK_WIDTH_BASE = 50.f;
    const float DISK_WIDTH_STEP = 30.f;

    const float ANIMATION_HEIGHT = 150.f;
    const float ANIMATION_SPEED = 0.15f;

    const sf::Color BG_COLOR(24, 28, 31);
    const sf::Color TOWER_COLOR(200, 200, 200);
    const sf::Color TEXT_COLOR(230, 230, 230);
    const sf::Color WIN_TEXT_COLOR(116, 196, 118);

    const sf::Color BUTTON_COLOR_NORMAL(69, 123, 157);
    const sf::Color BUTTON_COLOR_HOVER(119, 173, 207);

    // Paleta de colores para los discos
    const std::vector<sf::Color> DISK_COLORS = {
        sf::Color(230, 57, 70),  // Rojo
        sf::Color(241, 150, 52), // Naranja
        sf::Color(249, 199, 79), // Amarillo
        sf::Color(116, 196, 118),// Verde
        sf::Color(69, 123, 157), // Azul
        sf::Color(29, 53, 87),   // Azul oscuro
        sf::Color(168, 218, 220),// Celeste
        sf::Color(234, 113, 142) // Rosa
    };
}