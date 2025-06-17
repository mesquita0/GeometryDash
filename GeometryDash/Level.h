#pragma once
#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Background.h"

class Level : public Game
{
private:

public:
    int n;
    Background* backg = nullptr;   // pano de fundo animado
    static Scene* scene;           // cena do n�vel

    Level(int level_number);

    void Init();                    // inicializa��o do n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza��o do n�vel
};
