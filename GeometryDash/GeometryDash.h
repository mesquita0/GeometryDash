#pragma once
#include "Game.h"
#include "Audio.h"
#include "Player.h"
#include "Resources.h"

enum Sounds {MENU, MUSIC, TRANSITION};

class GeometryDash : public Game
{
private:
    static Game * level;            // n�vel atual do jogo
    bool is_paused;

public:
    static Player * player;         // jogador 
    static Audio * audio;           // sistema de �udio
    static bool viewBBox;           // estado da bounding box

    void Init();                    // inicializa jogo
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo

    template<class T>
    static void NextLevel()         // muda para pr�ximo n�vel do jogo
    {
        if (level)
        {
            level->Finalize();
            delete level;
            level = new T();
            level->Init();
        }
    };
};
