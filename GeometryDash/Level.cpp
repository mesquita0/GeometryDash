#include "Level.h"
#include "GeometryDash.h"
#include "Home.h"
#include "LevelLoader.h"
#include "GameOver.h"
#include "Player.h"
#include "Background.h"
#include <string>

using std::string;

Scene * Level::scene = nullptr;

Level::Level(int level_number) : n(level_number) {}

void Level::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    loadLevel(*this, window, "Level" + std::to_string(n) + ".txt");

    // inicia com música
    GeometryDash::audio->Frequency(MUSIC, 0.94f);
    GeometryDash::audio->Play(MUSIC);
}

void Level::Update()
{
    scene->Update();
    scene->CollisionDetection();

    if (GeometryDash::player->Bottom() < 0 || GeometryDash::player->Top() > window->Height() || !GeometryDash::player->IsAlive())
    {
        GeometryDash::audio->Stop(MUSIC);
        GeometryDash::audio->Play(DIED);
        GeometryDash::GameOverL();
        GeometryDash::player->Reset(n-1); 
    }
    else if (GeometryDash::player->Level() != n - 1 || window->KeyPress('N'))
    {
        GeometryDash::player->Reset(n);
        GeometryDash::NextLevel();
    } 
}

void Level::Draw()
{
    backg->Draw();
    scene->Draw();

    if (GeometryDash::viewBBox)
        scene->DrawBBox();
}

void Level::Finalize()
{
    scene->Remove(GeometryDash::player, MOVING);
    delete scene;
}
