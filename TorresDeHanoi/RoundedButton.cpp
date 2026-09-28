// --- RoundedButton.cpp ---
#include "RoundedButton.hpp"
#include "Config.hpp" // Necesita los colores de Config

void RoundedButton::init(const std::wstring& label, float width, float height, const sf::Font& font, float x, float y)
{
    mWidth = width;
    mHeight = height;

    float radius = height / 2.f;
    // Asegura que middleWidth no sea negativo si width < height
    float middleWidth = (width > height) ? (width - height) : 0.f;

    mLeftCap.setRadius(radius);
    mLeftCap.setOrigin(radius, radius);

    mRightCap.setRadius(radius);
    mRightCap.setOrigin(radius, radius);

    mMiddle.setSize(sf::Vector2f(middleWidth, height));
    mMiddle.setOrigin(middleWidth / 2.f, radius);

    mText.setFont(font);
    mText.setString(label);
    mText.setCharacterSize(30);
    mText.setFillColor(Config::TEXT_COLOR);

    sf::FloatRect textBounds = mText.getLocalBounds();
    mText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);

    setPosition(x, y); // Llama a setPosition para colocar todo
    setFillColor(Config::BUTTON_COLOR_NORMAL); // Establece el color inicial
}

void RoundedButton::setFillColor(const sf::Color& color)
{
    mLeftCap.setFillColor(color);
    mMiddle.setFillColor(color);
    mRightCap.setFillColor(color);
}

void RoundedButton::setPosition(float x, float y)
{
    mPosition = {x, y}; // Guarda la posición central deseada
    float radius = mHeight / 2.f;
    float middleWidth = (mWidth > mHeight) ? (mWidth - mHeight) : 0.f;

    // Calcula las posiciones de las partes basándose en la posición central (x, y)
    mLeftCap.setPosition(x - middleWidth / 2.f, y);
    mRightCap.setPosition(x + middleWidth / 2.f, y);
    mMiddle.setPosition(x, y); // El rectángulo central se posiciona en (x, y)
    mText.setPosition(x, y);   // El texto también se centra en (x, y)
}

void RoundedButton::move(float dx, float dy)
{
    // Mueve todas las partes del botón
    mLeftCap.move(dx, dy);
    mRightCap.move(dx, dy);
    mMiddle.move(dx, dy);
    mText.move(dx, dy);
    // Actualiza la posición central guardada
    mPosition.x += dx;
    mPosition.y += dy;
}

sf::FloatRect RoundedButton::getGlobalBounds() const
{
    // Devuelve la caja delimitadora general del botón
    return sf::FloatRect(
        mPosition.x - mWidth / 2.f, // Esquina superior izquierda x
        mPosition.y - mHeight / 2.f,// Esquina superior izquierda y
        mWidth,                     // Ancho total
        mHeight                     // Alto total
    );
}

void RoundedButton::draw(sf::RenderWindow& window)
{
    // Dibuja las partes del botón
    window.draw(mMiddle);
    window.draw(mLeftCap);
    window.draw(mRightCap);
    window.draw(mText);
}