#pragma once
#include "Game.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class GameOver : public Game
{
private:
    Sprite * title = nullptr;       // tela de fim
    Sprite * progress_bar = nullptr;
    Sprite * empty_bar = nullptr;
    Color  * progress_bar_color = nullptr;
    Color  * empty_bar_color = nullptr;
    float progress_barX;

public:
    void Init();                    // inicialização do nível
    void Update();                  // lógica da tela de fim
    void Draw();                    // desenho da tela
    void Finalize();                // finalização do nível
};
