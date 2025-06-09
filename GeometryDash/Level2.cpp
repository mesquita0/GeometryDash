#include "GeometryDash.h"
#include "Home.h"
#include "Level2.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

Scene* Level2::scene = nullptr;

void Level2::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    Color dark{ 0.4f, 0.4f, 0.4f, 1.0f };
    backg = new Background(dark);
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(GeometryDash::player, MOVING);

    // ----------------------
    // plataformas
    // ----------------------

    Platform* plat;
    float posX, posY;
    uint  platType;

    ifstream fin;
    fin.open("Level2.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // lê linha com informações da plataforma
            fin >> posY; fin >> platType;
            plat = new Platform(posX, posY, platType, dark);
            scene->Add(plat, STATIC);
        }
        else
        {
            // ignora comentários
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }

        fin >> posX;
    }
    fin.close();

    GeometryDash::audio->Frequency(MUSIC, 1.00f);
    GeometryDash::audio->Frequency(TRANSITION, 0.85f);
}

void Level2::Update()
{
    if (window->KeyPress(VK_ESCAPE) || GeometryDash::player->Level() == 2 || window->KeyPress('N'))
    {
        GeometryDash::audio->Stop(MUSIC);
        GeometryDash::NextLevel<Home>();
        GeometryDash::player->Reset();
    }
    else if (GeometryDash::player->Bottom() < 0 || GeometryDash::player->Top() > window->Height())
    {
        GeometryDash::audio->Stop(MUSIC);
        GeometryDash::NextLevel<GameOver>();
        GeometryDash::player->Reset();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
}

void Level2::Draw()
{
    backg->Draw();
    scene->Draw();

    if (GeometryDash::viewBBox)
        scene->DrawBBox();
}

void Level2::Finalize()
{
    scene->Remove(GeometryDash::player, MOVING);
    delete scene;
}
