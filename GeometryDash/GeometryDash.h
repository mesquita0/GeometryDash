#pragma once
#include "Game.h"
#include "Audio.h"
#include "Player.h"
#include "Resources.h"
#include <vector>

enum Sounds {MENU, MUSIC, DIED, TRANSITION};

class GeometryDash : public Game
{
private:
    static std::vector<Game*> levels;
    static int level_index;

public:
    static Player * player;         // jogador 
    static Audio * audio;           // sistema de áudio
    static Game * current_level;    // nível atual do jogo
    static bool viewBBox;           // estado da bounding box
    static int game_speed;
    static bool loopEnvironment;

    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo

    static void NextLevel();        // muda para próximo nível do jogo
    static void GameOverL();
};
