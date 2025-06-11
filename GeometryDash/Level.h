#pragma once
#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Background.h"

class Level : public Game
{
private:
    int n;

public:
    Background* backg = nullptr;   // pano de fundo animado
    static Scene* scene;           // cena do nível

    Level(int level_number);

    void Init();                    // inicialização do nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finalização do nível
};
