#pragma once
#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Game.h" 
#include "Scene.h"
#include "Player.h"
#include "Background.h"

class Home : public Game
{
private:
    Sprite* title = nullptr;   // pano de fundo animado 
    Sprite* play = nullptr;
    Background* backg = nullptr;   // pano de fundo animado
    TileSet* tileset = nullptr;    // tileset da animação
    Animation* anim = nullptr;     // animação do menu

public:
    static Scene* scene;

    void Init();                    // inicia nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza nível
};
