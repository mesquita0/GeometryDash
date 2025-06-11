#include "LevelLoader.h"
#include "GeometryDash.h"
#include "Level.h"
#include "WorldEntity.h"
#include <fstream>
#include <limits>
#include <string>

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
        entity = new WorldEntity(i, ground_level, GROUND, Color{ cR, cG, cB, 1 });
        entity->Translate(0, entity->Height() / 2.0f);
        level.scene->Add(entity, STATIC);
        i += entity->Width();
    }

    level.scene->Add(new WorldEntity(length - window->Width() - 20, ground_level, FINISH_BEFORE, white), STATIC);
    level.scene->Add(new WorldEntity(length - 140, ground_level, FINISH, white), STATIC);

    // Adiciona jogador na cena
    level.scene->Add(GeometryDash::player, MOVING);
    GeometryDash::player->MoveTo(100, ground_level - GeometryDash::player->Height() / 2.0f);

    float posX;
    uint  entityType;

    // Carrega entidades do jogo
    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // Lê linha com informações da entidade
            fin >> entityType;
            entity = new WorldEntity(posX, ground_level, (EntityType)entityType, white);
            entity->Translate(0, -1.0f * entity->Height() / 2.0f);
            level.scene->Add(entity, STATIC);
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
