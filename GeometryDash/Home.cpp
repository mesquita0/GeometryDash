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
    GeometryDash::loopEnvironment = true;
    level1->Init();
    GeometryDash::audio->Stop(MUSIC);

    title = new Sprite("Resources/Title.png");
    play = new Sprite("Resources/PressEnter.png");

    titleY = 85;
    vel_titleY = 0;

    // Remover player da home
    level1->scene->Remove(GeometryDash::player, MOVING);

    tileset = new TileSet("Resources/PressEnter.png", 72, 48, 1, 5);
    anim = new Animation(tileset, 0.180f, true);

    // inicia com m�sica
    GeometryDash::audio->Play(MENU, true);
}

void Home::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    titleY += vel_titleY * gameTime;

    // Passar para o level 1 quando o titulo sair da tela
    if (titleY + title->Height() / 2.0f < 0)
    {
        GeometryDash::player->Level(0);
        GeometryDash::NextLevel();
    }
    else if (window->KeyPress(VK_RETURN)) // come�ar a transi��o pro level 1
    {
        vel_titleY = -500;
        GeometryDash::audio->Stop(MENU);
        GeometryDash::audio->Play(TRANSITION);
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
    title->Draw(window->CenterX(), titleY, Layer::FRONT);
    anim->Draw(810, 275);
}

void Home::Finalize()
{
    delete anim;
    delete tileset;

    level1->scene->Add(GeometryDash::player, MOVING);
    GeometryDash::loopEnvironment = false;
    GeometryDash::audio->Play(MUSIC, true);
}
