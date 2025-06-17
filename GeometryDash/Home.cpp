#include "Engine.h"
#include "GeometryDash.h"
#include "Home.h"
#include "GeometryDash.h"
#include "Home.h"
#include "GameOver.h"
#include "Player.h"
#include "Background.h"
#include "LevelLoader.h"
#include "WorldEntity.h"

Home::Home(Level* level1) {
    this->level1 = level1;
}

void Home::Init()
{
    level1->Init();

    title = new Sprite("Resources/Title.png");
    play = new Sprite("Resources/PressEnter.png");

    // Remover player da home
    level1->scene->Remove(GeometryDash::player, MOVING);

    tileset = new TileSet("Resources/PressEnter.png", 72, 48, 1, 5);
    anim = new Animation(tileset, 0.180f, true);

    // inicia com música
    GeometryDash::audio->Play(MENU, true);
}

void Home::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // se a tecla ENTER for pressionada
    if (window->KeyPress(VK_RETURN))
    {
        GeometryDash::audio->Stop(MENU);
        GeometryDash::audio->Play(TRANSITION);
        GeometryDash::player->Level(0);
        GeometryDash::NextLevel();

    }
    else
    {
        level1->Update();
        anim->NextFrame();
    }
}

void Home::Draw()
{
    level1->Draw();
    title->Draw(window->CenterX(), 85, Layer::FRONT);
    anim->Draw(810, 275);
}

void Home::Finalize()
{
    delete anim;
    delete tileset;

    level1->scene->Add(GeometryDash::player, MOVING);
}
