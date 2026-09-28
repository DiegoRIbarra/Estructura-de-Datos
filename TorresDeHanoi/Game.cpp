// --- Game.cpp ---
#include "Game.hpp"
#include "Config.hpp"
#include <iostream>
#include <cmath>

// Constructor
Game::Game() : mWindow(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Torres de Hanoi"),
             mCurrentState(GameState::SETUP), // <-- EMPIEZA EN SETUP
             mNextState(GameState::SETUP),    // <-- EMPIEZA EN SETUP
             mNumDisks(Config::MIN_DISKS),
             mIsHoldingDisk(false),
             mHeldDiskSize(0),
             mSourceTower(-1),
             mMoveCount(0),
             mAnimStage(0),
             mAnimTargetTower(-1),
             mpPressedButton(nullptr),
             mButtonClickedThisFrame(false)
{
    mTowers.resize(3);
    // Activa VSync para evitar tearing/parpadeo (mejor que limitar FPS manualmente)
    mWindow.setVerticalSyncEnabled(true);

    if (!mFont.loadFromFile("arial.ttf"))
    {
        if (!mFont.loadFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            std::cerr << "Error: No se pudo cargar la fuente 'arial.ttf'." << std::endl;
        }
    }

    // Configurar UIs
    setupTowerShapes();
    setupSetupUI();
    setupGameUI();
    setupAlertaUI();
}

// Bucle principal (¡REESTRUCTURADO!)
void Game::run()
{
    while (mWindow.isOpen())
    {
        // --- 1. PREPARAR FRAME ---
        mNextState = mCurrentState;      // Asume que el estado no cambiará
        mButtonClickedThisFrame = false; // Resetea la bandera de clic

        // --- 2. PROCESAR EVENTOS ---
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mWindow.close();

            // Llama al manejador de eventos del estado ACTUAL
            // Estos manejadores modificarán mNextState si es necesario
            switch (mCurrentState)
            {
                case GameState::SETUP:          processSetupEvents(event); break;
                case GameState::PLAYING:        processPlayingEvents(event); break;
                case GameState::JUEGO_TERMINADO:processTerminadoEvents(event); break;
                case GameState::ANIMATING:      break; // Animación no procesa input
            }
        } // Fin del bucle de eventos (pollEvent)

        // --- 3. ACTUALIZAR LÓGICA ---
        if (mCurrentState == GameState::ANIMATING)
        {
            updateAnimation(); // Puede poner mNextState = PLAYING
        }
        else if (mCurrentState == GameState::PLAYING)
        {
            updatePlaying();   // Llama a checkWinCondition
        }
        // Llamamos checkWinCondition *después* de actualizar la lógica de PLAYING
        // para que pueda poner mNextState = JUEGO_TERMINADO si se gana
        if(mCurrentState == GameState::PLAYING)
        {
            checkWinCondition();
        }

        // --- 4. APLICAR CAMBIO DE ESTADO ---
        // Importante: esto va DESPUÉS de la lógica para no perder mNextState
        mCurrentState = mNextState;


        // --- 5. DIBUJAR ---
        mWindow.clear(Config::BG_COLOR);
        switch (mCurrentState)
        {
            case GameState::SETUP:
                renderSetup();
                break;
            case GameState::PLAYING:
            case GameState::ANIMATING:
                renderPlaying();
                break;
            case GameState::JUEGO_TERMINADO:
                renderPlaying();
                renderAlerta();
                break;
        }
        mWindow.display();

    } // Fin del bucle principal (while isOpen)
}

// --- MÉTODOS DE SETUP ---

void Game::setupSetupUI()
{
    mSetupTitle.setFont(mFont);
    mSetupTitle.setString(L"Elige la dificultad:");
    mSetupTitle.setCharacterSize(30);
    mSetupTitle.setFillColor(Config::TEXT_COLOR);
    centerText(mSetupTitle, Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT * 0.15f);

    float buttonHeight = 80.f;
    float buttonY = Config::WINDOW_HEIGHT * 0.5f;
    mButtonMinus.init(L"<", buttonHeight, buttonHeight, mFont, Config::WINDOW_WIDTH / 2.f - 200.f, buttonY);
    mButtonPlus.init(L">", buttonHeight, buttonHeight, mFont, Config::WINDOW_WIDTH / 2.f + 200.f, buttonY);
    mButtonStart.init(L"JUGAR", 200.f, buttonHeight, mFont, Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT * 0.85f);
}

void Game::processSetupEvents(sf::Event& event)
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow));

    // Hover
    if (mpPressedButton != &mButtonMinus) mButtonMinus.setFillColor(mButtonMinus.getGlobalBounds().contains(mousePos) ? Config::BUTTON_COLOR_HOVER : Config::BUTTON_COLOR_NORMAL);
    if (mpPressedButton != &mButtonPlus) mButtonPlus.setFillColor(mButtonPlus.getGlobalBounds().contains(mousePos) ? Config::BUTTON_COLOR_HOVER : Config::BUTTON_COLOR_NORMAL);
    if (mpPressedButton != &mButtonStart) mButtonStart.setFillColor(mButtonStart.getGlobalBounds().contains(mousePos) ? Config::BUTTON_COLOR_HOVER : Config::BUTTON_COLOR_NORMAL);

    // Clic
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (mButtonClickedThisFrame) return;

        if (mButtonMinus.getGlobalBounds().contains(mousePos)) pressButton(mButtonMinus);
        else if (mButtonPlus.getGlobalBounds().contains(mousePos)) pressButton(mButtonPlus);
        else if (mButtonStart.getGlobalBounds().contains(mousePos)) pressButton(mButtonStart);
    }

    // Soltar
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        if (mpPressedButton == nullptr) return;
        RoundedButton* clickedButton = mpPressedButton;
        releaseButton();

        if (!mButtonClickedThisFrame && clickedButton->getGlobalBounds().contains(mousePos))
        {
            bool stateChanged = false;
            if (clickedButton == &mButtonMinus) {
                if (mNumDisks > Config::MIN_DISKS) mNumDisks--;
            } else if (clickedButton == &mButtonPlus) {
                if (mNumDisks < Config::MAX_DISKS) mNumDisks++;
            } else if (clickedButton == &mButtonStart) {
                resetGame(mNumDisks);
                mNextState = GameState::PLAYING;
                stateChanged = true;
            }

            if (stateChanged) {
                mButtonClickedThisFrame = true;
                // No necesita return aquí, ya que el bucle de eventos terminará
            }
        }
    }
}

void Game::renderSetup()
{
    mWindow.draw(mSetupTitle);

    mWindow.draw(mTowerShapes[1]);
    for (int i = 0; i < mNumDisks; ++i)
    {
        int diskSize = mNumDisks - i;
        sf::RectangleShape disk = createDiskShape(diskSize);
        float xPos = mTowerPositions[1];
        float yPos = (Config::WINDOW_HEIGHT * 0.8f) - (i * Config::DISK_HEIGHT);
        disk.setPosition(xPos, yPos);
        mWindow.draw(disk);
    }

    mButtonMinus.draw(mWindow);
    mButtonPlus.draw(mWindow);
    mButtonStart.draw(mWindow);

    // mWindow.display(); // <- Esta línea no debe ir aquí, se llama una sola vez al final de run()
}

// --- MÉTODOS DE JUEGO ---

void Game::setupGameUI()
{
    mInstructionText.setFont(mFont);
    mInstructionText.setString(L"Haz clic para levantar y soltar un disco.");
    mInstructionText.setCharacterSize(20);
    mInstructionText.setFillColor(Config::TEXT_COLOR);
    // Mueve las instrucciones más abajo para no chocar con los botones superiores
    centerText(mInstructionText, Config::WINDOW_WIDTH / 2.f, 80.f);

    mMoveCountText.setFont(mFont);
    mMoveCountText.setCharacterSize(24);
    mMoveCountText.setFillColor(Config::TEXT_COLOR);
    mMoveCountText.setPosition(20, 20);

    mButtonSalir.init(L"Salir", 100.f, 50.f, mFont, Config::WINDOW_WIDTH - 70.f, 35.f);
    // Botón AutoResolver a la izquierda del botón Salir
    mButtonAuto.init(L"AutoResolver", 170.f, 50.f, mFont, Config::WINDOW_WIDTH - 70.f - 200.f, 35.f);
}

void Game::processPlayingEvents(sf::Event& event)
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow));

    if (mpPressedButton != &mButtonSalir)
        mButtonSalir.setFillColor(mButtonSalir.getGlobalBounds().contains(mousePos) ? Config::BUTTON_COLOR_HOVER : Config::BUTTON_COLOR_NORMAL);
    if (mpPressedButton != &mButtonAuto)
        mButtonAuto.setFillColor(mButtonAuto.getGlobalBounds().contains(mousePos) ? Config::BUTTON_COLOR_HOVER : Config::BUTTON_COLOR_NORMAL);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (!mButtonClickedThisFrame && mButtonSalir.getGlobalBounds().contains(mousePos))
        {
            pressButton(mButtonSalir);
            // No hacemos return aquí
        } else if (!mButtonClickedThisFrame && mButtonAuto.getGlobalBounds().contains(mousePos)) {
            pressButton(mButtonAuto);
        } else if (!mButtonClickedThisFrame && !mIsHoldingDisk && !mAutoSolving) { // Desactiva interacción con discos mientras AutoResolver corre
             handleClick(event.mouseButton.x);
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        if (!mButtonClickedThisFrame && mpPressedButton == &mButtonSalir)
        {
            RoundedButton* clickedButton = mpPressedButton;
            releaseButton();
            if (clickedButton->getGlobalBounds().contains(mousePos))
            {
                mNextState = GameState::SETUP;
                // Limpia AutoResolver si estaba activo
                mAutoSolving = false;
                mAutoMoves.clear();
                mAutoIndex = 0;
                mButtonClickedThisFrame = true;
                // No necesita return
            }
        } else if (!mButtonClickedThisFrame && mpPressedButton == &mButtonAuto)
        {
            RoundedButton* clickedButton = mpPressedButton;
            releaseButton();
            if (clickedButton->getGlobalBounds().contains(mousePos) && !mAutoSolving)
            {
                // Reinicia juego y prepara lista de movimientos
                resetGame(mNumDisks);
                mAutoMoves.clear();
                buildSolutionMoves(mNumDisks, 0, 2, 1);
                mAutoIndex = 0;
                mAutoTotalMoves = static_cast<int>(mAutoMoves.size());
                mAutoSolving = true;
                mButtonClickedThisFrame = true;
            }
        } else if (mIsHoldingDisk && !mAutoSolving) { // Si se estaba sosteniendo un disco, intenta soltarlo
             handleClick(event.mouseButton.x);
             releaseButton(); // Asegura liberar cualquier botón presionado por error
        } else {
             releaseButton(); // Libera si no fue el botón Salir y no se sostenía disco
        }
    }
}


void Game::updatePlaying()
{
    if (mIsHoldingDisk)
    {
        mHeldDiskShape.setPosition(
            static_cast<float>(sf::Mouse::getPosition(mWindow).x),
            Config::ANIMATION_HEIGHT);
    }

    // Disparar siguiente movimiento automático si corresponde
    if (mAutoSolving && mCurrentState == GameState::PLAYING && mAutoIndex < mAutoMoves.size())
    {
        auto [from, to] = mAutoMoves[mAutoIndex];
        startAutoMove(from, to);
        ++mAutoIndex;
    }
}

void Game::renderPlaying()
{
    for (const auto &tower : mTowerShapes) mWindow.draw(tower);
    for (int i = 0; i < mTowers.size(); ++i) {
        for (int j = 0; j < mTowers[i].size(); ++j) {
           int diskSize = mTowers[i][j];
            sf::RectangleShape disk = createDiskShape(diskSize);
            float xPos = mTowerPositions[i];
            float yPos = (Config::WINDOW_HEIGHT * 0.8f) - (j * Config::DISK_HEIGHT);
            disk.setPosition(xPos, yPos);
            mWindow.draw(disk);
        }
    }
     if (mIsHoldingDisk) mWindow.draw(mHeldDiskShape);
    else if (mCurrentState == GameState::ANIMATING) mWindow.draw(mAnimatingDisk);
    mWindow.draw(mInstructionText);
    mWindow.draw(mMoveCountText);
    mButtonSalir.draw(mWindow);
    mButtonAuto.draw(mWindow);
}

void Game::handleClick(int mouseX)
{
    // Solo procesa si no estamos ya animando
    if (mCurrentState != GameState::PLAYING) return;

    int clickedTower = getTowerAt(mouseX);
    if (clickedTower == -1) return;

    if (mIsHoldingDisk) { // Intentando soltar
        if (tryMove(clickedTower)) {
            mIsHoldingDisk = false; // Suelta el control del mouse
            mNextState = GameState::ANIMATING; // Agenda animación
            mAnimStage = 1; // Empieza cruzando
            mAnimTargetTower = clickedTower;
            mAnimatingDisk = mHeldDiskShape; // Pasa el disco a la animación
            mAnimTargetPos = sf::Vector2f(mTowerPositions[mAnimTargetTower], Config::ANIMATION_HEIGHT);
        } else { // Movimiento inválido
            mTowers[mSourceTower].push_back(mHeldDiskSize); // Devuelve el disco
            mIsHoldingDisk = false;
            mSourceTower = -1;
        }
    } else { // Intentando levantar
        if (!mTowers[clickedTower].empty()) {
            mHeldDiskSize = mTowers[clickedTower].back();
            mTowers[clickedTower].pop_back();
            mIsHoldingDisk = true;
            mSourceTower = clickedTower;
            mHeldDiskShape = createDiskShape(mHeldDiskSize);
            // La posición se actualiza en updatePlaying()
        }
    }
}


bool Game::tryMove(int targetTower)
{
     if (targetTower == mSourceTower) return false; // No se puede soltar en la misma torre
    if (mTowers[targetTower].empty()) return true; // Siempre se puede soltar en torre vacía
    int topDiskOnTarget = mTowers[targetTower].back();
    return mHeldDiskSize < topDiskOnTarget; // Solo si es más pequeño que el de arriba
}

void Game::checkWinCondition()
{
    // Solo revisa si estamos jugando (para evitar re-trigger en animación)
    if (mCurrentState == GameState::PLAYING && (mTowers[1].size() == mNumDisks || mTowers[2].size() == mNumDisks))
    {
        mNextState = GameState::JUEGO_TERMINADO; // Agenda cambio a pantalla de victoria
        mAlertaTextoMovimientos.setString(L"¡Ganaste en " + std::to_wstring(mMoveCount) + L" movimientos!");
        centerText(mAlertaTextoMovimientos, Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT / 2.f + 10.f);
    }
}

int Game::getTowerAt(int mouseX) const
{
     for (int i = 0; i < 3; ++i) {
        float towerX = mTowerPositions[i];
        // Ajusta el ancho de clic basado en el disco más grande posible
        float clickWidth = Config::DISK_WIDTH_BASE + (Config::MAX_DISKS * Config::DISK_WIDTH_STEP);
        if (mouseX >= towerX - clickWidth / 2.f && mouseX <= towerX + clickWidth / 2.f) {
            return i;
        }
    }
    return -1;
}

// --- MÉTODOS DE ANIMACIÓN ---

void Game::updateAnimation()
{
    // Interpolación suavizada pero con clamp para evitar "rebotes" o acercamientos infinitos
    sf::Vector2f pos = mAnimatingDisk.getPosition();
    sf::Vector2f delta = (mAnimTargetPos - pos) * Config::ANIMATION_SPEED;
    // Si el paso es mayor que la distancia restante en un eje, salta directo al objetivo en ese eje
    auto almostEqual = [](float a, float b){ return std::abs(a - b) < 0.5f; };
    float nextX = almostEqual(pos.x, mAnimTargetPos.x) ? mAnimTargetPos.x : pos.x + delta.x;
    float nextY = almostEqual(pos.y, mAnimTargetPos.y) ? mAnimTargetPos.y : pos.y + delta.y;
    mAnimatingDisk.setPosition(nextX, nextY);

    bool reachedX = almostEqual(nextX, mAnimTargetPos.x);
    bool reachedY = almostEqual(nextY, mAnimTargetPos.y);

    if (reachedX && reachedY)
    {
        mAnimatingDisk.setPosition(mAnimTargetPos);
        if (mAnimStage == 1)
        {
            // Terminó de CRUZAR: ahora bajamos a la altura correcta de la torre destino
            mAnimStage = 2;
            mAnimTargetPos.y = (Config::WINDOW_HEIGHT * 0.8f)
                             - (mTowers[mAnimTargetTower].size() * Config::DISK_HEIGHT);
        }
        else if (mAnimStage == 2)
        {
            // Fin de animación: fija estado y limpia banderas para evitar bucles
            mTowers[mAnimTargetTower].push_back(mHeldDiskSize);
            mHeldDiskSize = 0;
            mSourceTower = -1;
            mAnimStage = 0;
            mAnimTargetTower = -1;
            mMoveCount++;
            updateMoveCountText();
            // Si estamos en modo AutoResolver, decide siguiente paso o terminar
            if (mAutoSolving && mAutoIndex >= mAutoMoves.size())
            {
                mAutoSolving = false;
                mNextState = GameState::JUEGO_TERMINADO;
                mAlertaTextoMovimientos.setString(L"Se solucionó en " + std::to_wstring(mAutoTotalMoves) + L" pasos");
                centerText(mAlertaTextoMovimientos, Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT / 2.f + 10.f);
            }
            else
            {
                mNextState = GameState::PLAYING;
            }
        }
    }
}

// --- MÉTODOS DE ALERTA ---

void Game::setupAlertaUI()
{
    mAlertaFondo.setSize(sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
    mAlertaFondo.setFillColor(sf::Color(0, 0, 0, 150));
    mAlertaTitulo.setFont(mFont);
    mAlertaTitulo.setString(L"¡Felicidades!");
    mAlertaTitulo.setCharacterSize(40);
    mAlertaTitulo.setFillColor(Config::WIN_TEXT_COLOR);
    centerText(mAlertaTitulo, Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT / 2.f - 60.f);
    mAlertaTextoMovimientos.setFont(mFont);
    mAlertaTextoMovimientos.setCharacterSize(24);
    mAlertaTextoMovimientos.setFillColor(Config::TEXT_COLOR);
    mButtonFin.init(L"Fin", 150.f, 60.f, mFont, Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT / 2.f + 60.f);
}

void Game::processTerminadoEvents(sf::Event& event)
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow));

    if (mpPressedButton != &mButtonFin)
        mButtonFin.setFillColor(mButtonFin.getGlobalBounds().contains(mousePos) ? Config::BUTTON_COLOR_HOVER : Config::BUTTON_COLOR_NORMAL);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (!mButtonClickedThisFrame && mButtonFin.getGlobalBounds().contains(mousePos))
            pressButton(mButtonFin);
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        if (mpPressedButton == nullptr) return;
        RoundedButton* clickedButton = mpPressedButton;
        releaseButton();

        if (!mButtonClickedThisFrame && clickedButton == &mButtonFin && clickedButton->getGlobalBounds().contains(mousePos))
        {
            mNextState = GameState::SETUP; // <-- Regresa a SETUP
            // Limpia AutoResolver
            mAutoSolving = false;
            mAutoMoves.clear();
            mAutoIndex = 0;
            mButtonClickedThisFrame = true;
            // No necesita return
        }
    }
}

void Game::renderAlerta()
{
    mWindow.draw(mAlertaFondo);
    mWindow.draw(mAlertaTitulo);
    mWindow.draw(mAlertaTextoMovimientos);
    mButtonFin.draw(mWindow);
}


// --- FUNCIONES HELPER ---

void Game::pressButton(RoundedButton &button) { if (mpPressedButton) releaseButton(); button.move(2, 2); mpPressedButton = &button; }
void Game::releaseButton() { if (mpPressedButton) mpPressedButton->move(-2, -2); mpPressedButton = nullptr; }
void Game::setupTowerShapes() { float th = Config::WINDOW_HEIGHT*0.6f; float yp = Config::WINDOW_HEIGHT*0.8f-th; for(int i=0;i<3;++i){ mTowerPositions[i]=(Config::WINDOW_WIDTH/4.f)*(i+1); mTowerShapes[i].setSize({Config::TOWER_WIDTH,th}); mTowerShapes[i].setFillColor(Config::TOWER_COLOR); mTowerShapes[i].setOrigin(Config::TOWER_WIDTH/2.f,0.f); mTowerShapes[i].setPosition(mTowerPositions[i],yp); } }
void Game::resetGame(int numDisks) { for(auto& t:mTowers)t.clear(); for(int s=numDisks;s>=1;--s)mTowers[0].push_back(s); mMoveCount=0; mIsHoldingDisk=false; mSourceTower=-1; updateMoveCountText(); }
sf::RectangleShape Game::createDiskShape(int size) { float w=Config::DISK_WIDTH_BASE+(size*Config::DISK_WIDTH_STEP); sf::RectangleShape d({w,Config::DISK_HEIGHT}); d.setFillColor(Config::DISK_COLORS[size%Config::DISK_COLORS.size()]); d.setOrigin(w/2.f,Config::DISK_HEIGHT); return d; }
void Game::centerText(sf::Text &text, float x, float y) { sf::FloatRect b=text.getLocalBounds(); text.setOrigin(b.left+b.width/2.f,b.top+b.height/2.f); text.setPosition(x,y); }
void Game::updateMoveCountText() { mMoveCountText.setString(L"Movimientos: " + std::to_wstring(mMoveCount)); }

// --- AutoResolver helpers ---
void Game::buildSolutionMoves(int n, int from, int to, int aux)
{
    if (n <= 0) return;
    buildSolutionMoves(n - 1, from, aux, to);
    mAutoMoves.emplace_back(from, to);
    buildSolutionMoves(n - 1, aux, to, from);
}

void Game::startAutoMove(int from, int to)
{
    if (from < 0 || from > 2 || to < 0 || to > 2) return;
    if (mTowers[from].empty()) return;
    mHeldDiskSize = mTowers[from].back();
    mTowers[from].pop_back();
    mSourceTower = from;
    mIsHoldingDisk = false;
    mAnimatingDisk = createDiskShape(mHeldDiskSize);
    mAnimatingDisk.setPosition(mTowerPositions[from], Config::ANIMATION_HEIGHT);
    mAnimStage = 1;
    mAnimTargetTower = to;
    mAnimTargetPos = { mTowerPositions[to], Config::ANIMATION_HEIGHT };
    mNextState = GameState::ANIMATING;
}