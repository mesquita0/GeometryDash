#pragma once
#include "Game.h"
#include "Audio.h"
#include "Player.h"
#include "Resources.h"
#include <vector>

enum Sounds {MENU, MUSIC, TRANSITION};

class GeometryDash : public Game
{
private:
    static std::vector<Game*> levels;
    static Game * current_level;            // n�vel atual do jogo
    static int    level_index;

public:
    static Player * player;         // jogador 
    static Audio * audio;           // sistema de �udio
    static bool viewBBox;           // estado da bounding box

    void Init();                    // inicializa jogo
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo

    static void NextLevel();        // muda para pr�ximo n�vel do jogo
    static void GameOverL();
};
