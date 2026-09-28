// --- RoundedButton.hpp ---
#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class RoundedButton
{
public:
    RoundedButton() : mWidth(0), mHeight(0) {} // Constructor en línea

    // Declaraciones de funciones (la lógica va en el .cpp)
    void init(const std::wstring& label, float width, float height, const sf::Font& font, float x, float y);
    void setFillColor(const sf::Color& color);
    void setPosition(float x, float y);
    void move(float dx, float dy);
    sf::FloatRect getGlobalBounds() const;
    void draw(sf::RenderWindow& window);

private:
    sf::CircleShape mLeftCap;
    sf::CircleShape mRightCap;
    sf::RectangleShape mMiddle;
    sf::Text mText;
    
    sf::Vector2f mPosition;
    float mWidth;
    float mHeight;
};