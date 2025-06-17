#include "LevelLoader.h"
#include "GeometryDash.h"
#include "Level.h"
#include "WorldEntity.h"
#include <fstream>
#include <limits>
#include <string>

constexpr int finish_offset = 140;
constexpr int player_start_offset = 100;

void loadLevel(Level& level, Window* window, const std::string& path) {
    std::ifstream fin;
    fin.open(path);
    Color white{ 1,1,1,1 };

    int background;
    float cR, cG, cB;

    // Ignora comentários
    fin >> background;
    while (!fin.good())
    {
        fin.clear();
        fin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        fin >> background;
    }

    // Carregar background
    fin >> cR;
    fin >> cG;
    fin >> cB;
    level.backg = new Background(Color{ cR, cG, cB, 1 });
    level.scene->Add(level.backg, STATIC);

    int ground_level, length;
    WorldEntity* entity;

    // Ignora comentários
    fin >> ground_level;
    while (!fin.good())
    {
        fin.clear();
        fin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        fin >> ground_level;
    }

    // Carrega chão do jogo
    fin >> length;
    fin >> cR;
    fin >> cG;
    fin >> cB;
    int i = 0;
    while (i < (length + window->Width())) {
        entity = new WorldEntity(i, ground_level, GROUND1, Color{ cR, cG, cB, 1 });
        entity->Translate(0, entity->Height() / 2.0f);
        level.scene->Add(entity, STATIC);
        i += entity->Width();
    }

    level.scene->Add(new WorldEntity(length - window->Width() - 20, ground_level, FINISH_BEFORE, white), STATIC);
    level.scene->Add(new WorldEntity(length - finish_offset, ground_level, FINISH, white), STATIC);

    // Adiciona jogador na cena
    level.scene->Add(GeometryDash::player, MOVING);
    GeometryDash::player->MoveTo(player_start_offset, ground_level - GeometryDash::player->Height() / 2.0f);
    GeometryDash::player->maxPoints(length - finish_offset - player_start_offset);

    float posX, posY;
    uint  entityType;

    // Carrega entidades do jogo
    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // Pega a posição y da entidade
            while (fin.peek() == ' ') fin.get();
            if (std::isdigit(fin.peek())) {
                fin >> posY;
            }
            else {
                posY = ground_level;
                fin.get();
            }

            // Lê linha com informações da entidade
            fin >> entityType;
            entity = new WorldEntity(posX, posY, (EntityTypeSprite)entityType, white);
            entity->Translate(0, -1.0f * entity->Height() / 2.0f);

            level.scene->Add(entity, STATIC);
            if (entity->Type() == BLOCK)
                level.scene->Add(new WorldEntity(posX, entity->Y(), BLOCK_SIDE, white), STATIC);
        }
        else
        {
            // Ignora comentários
            fin.clear();
            fin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }

        fin >> posX;
    }
    fin.close();
}
