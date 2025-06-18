#pragma once
#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Background.h"

class Level : public Game
{
private:
    int level_number;

public:
    Background* backg = nullptr;   // pano de fundo animado
    static Scene* scene;           // cena do n�vel
    int num_ground_blocks = 0;

    Level(int level_number);

    void Init();                    // inicializa��o do n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza��o do n�vel

    int levelNumber();
};

inline int Level::levelNumber()
{ return level_number; }
