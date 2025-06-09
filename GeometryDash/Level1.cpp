#include "GeometryDash.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

Scene * Level1::scene = nullptr;

void Level1::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background(Color{ 1,1,1,1 });
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(GeometryDash::player, MOVING);

    // ----------------------
    // plataformas
    // ----------------------

    Platform * plat;
    float posX, posY;
    uint  platType;
    Color white { 1,1,1,1 };

    ifstream fin;
    fin.open("Level1.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // lê linha com informações da plataforma
            fin >> posY; fin >> platType;
            plat = new Platform(posX, 250, platType, white);
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

    // inicia com música
    GeometryDash::audio->Frequency(MUSIC, 0.94f);
    GeometryDash::audio->Frequency(TRANSITION, 1.0f);
    GeometryDash::audio->Play(MUSIC);
}

void Level1::Update()
{
    if (window->KeyPress(VK_ESCAPE))
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
    else if (GeometryDash::player->Level() == 1 || window->KeyPress('N'))
    {
        GeometryDash::NextLevel<Level2>();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }    
}

void Level1::Draw()
{
    backg->Draw();
    scene->Draw();

    if (GeometryDash::viewBBox)
        scene->DrawBBox();
}

void Level1::Finalize()
{
    scene->Remove(GeometryDash::player, MOVING);
    delete scene;
}
