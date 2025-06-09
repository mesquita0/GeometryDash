#pragma once
#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Background.h"

class Level2 : public Game
{
private:
    Background* backg = nullptr;   // pano de fundo animado

public:
    static Scene* scene;           // cena do nível

    void Init();                    // inicialização do nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finalização do nível
};
