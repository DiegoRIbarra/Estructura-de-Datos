// --- Game.hpp ---
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "RoundedButton.hpp"

// --- Estados del Juego ---
enum class GameState
{
    SETUP,
    PLAYING,
    ANIMATING,
    JUEGO_TERMINADO
};

class Game
{
public:
    Game();
    void run();

private:
    // --- MÉTODOS DE SETUP (DIFICULTAD) ---
    void setupSetupUI();
    void processSetupEvents(sf::Event& event);
    void renderSetup();

    // --- MÉTODOS DE JUEGO (PLAYING) ---
    void setupGameUI();
    void processPlayingEvents(sf::Event& event);
    void updatePlaying();
    void renderPlaying();
    void handleClick(int mouseX);
    bool tryMove(int targetTower);
    void checkWinCondition();
    int getTowerAt(int mouseX) const;
    // Auto resolver
    void buildSolutionMoves(int n, int from, int to, int aux);
    void startAutoMove(int from, int to);

    // --- MÉTODOS DE ANIMACIÓN ---
    void updateAnimation();

    // --- MÉTODOS DE ALERTA ---
    void setupAlertaUI();
    void processTerminadoEvents(sf::Event& event);
    void renderAlerta();

    // --- FUNCIONES HELPER (Comunes) ---
    void pressButton(RoundedButton &button);
    void releaseButton();
    void setupTowerShapes();
    void resetGame(int numDisks);
    sf::RectangleShape createDiskShape(int size);
    void centerText(sf::Text &text, float x, float y);
    void updateMoveCountText();

    // --- Miembros Privados (Variables) ---

    // Componentes de SFML
    sf::RenderWindow mWindow;
    sf::Font mFont;

    // Estado del juego
    GameState mCurrentState;
    GameState mNextState; // Para cambio de estado retrasado
    std::vector<std::vector<int>> mTowers;
    int mNumDisks;
    int mMoveCount;

    // Estado de "agarrar" disco
    bool mIsHoldingDisk;
    int mHeldDiskSize;
    int mSourceTower;
    sf::RectangleShape mHeldDiskShape;

    // Estado de Animación
    int mAnimStage;
    int mAnimTargetTower;
    sf::Vector2f mAnimTargetPos;
    sf::RectangleShape mAnimatingDisk;

    // UI (Juego)
    sf::Text mInstructionText;
    sf::Text mMoveCountText;
    RoundedButton mButtonSalir; // Ahora regresa a SETUP
    RoundedButton mButtonAuto;  // Auto resolver

    // UI (Setup)
    sf::Text mSetupTitle;
    RoundedButton mButtonMinus;
    RoundedButton mButtonPlus;
    RoundedButton mButtonStart;
    // (Botón Regresar eliminado)

    // UI (Alerta de Victoria)
    sf::RectangleShape mAlertaFondo;
    sf::Text mAlertaTitulo;
    sf::Text mAlertaTextoMovimientos;
    RoundedButton mButtonFin; // Ahora regresa a SETUP

    // Puntero para el estado del clic
    RoundedButton* mpPressedButton;

    // Bandera para evitar doble clic (Aunque ya no es estrictamente necesaria con mNextState, no estorba)
    bool mButtonClickedThisFrame;

    // Vista
    sf::RectangleShape mTowerShapes[3];
    float mTowerPositions[3];

    // Auto resolver
    bool mAutoSolving = false;
    std::vector<std::pair<int,int>> mAutoMoves;
    size_t mAutoIndex = 0;
    int mAutoTotalMoves = 0;
};