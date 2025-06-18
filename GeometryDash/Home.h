#pragma once
#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Game.h" 
#include "Scene.h"
#include "Player.h"
#include "Background.h"
#include "Level.h"

class Home : public Game
{
private:
    Sprite* title = nullptr;
    Sprite* play = nullptr;
    TileSet* tileset = nullptr;    // tileset da anima��o
    Animation* anim = nullptr;     // anima��o do menu
    Level* level1 = nullptr;

public:
    Home(Level* level1);

    void Init();                    // inicia n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza n�vel

    int offsetGround();
};

inline int Home::offsetGround()
{ return level1->num_ground_blocks; }
