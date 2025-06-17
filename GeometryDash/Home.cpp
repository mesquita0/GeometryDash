#include "Engine.h"
#include "GeometryDash.h"
#include "Home.h"

#include "GeometryDash.h"
#include "Home.h"

#include "GameOver.h"
#include "Player.h"

#include "Background.h"
#include "WorldEntity.h"

Scene* Home::scene = nullptr;

void Home::Init()
{
    scene = new Scene();

    title = new Sprite("Resources/Title.png");
    play = new Sprite("Resources/PressEnter.png");

    backg = new Background(Color{ 0.4,0.4,0.4,1 });
    scene->Add(backg, STATIC);



    // Chão do jogo
    int ground_level = 390;
    WorldEntity* plat; 
    int i = 0;
    while (i < 50000) {
        plat = new WorldEntity(i, ground_level, GROUND1, Color{ 0.4,0.4,0.4,1 }); 
        scene->Add(plat, STATIC);
        i += plat->Width();
    }

    tileset = new TileSet("Resources/PressEnter.png", 72, 48, 1, 5);
    anim = new Animation(tileset, 0.180f, true);
    //GeometryDash::audio->Play(MENU, true);
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
        GeometryDash::player->Reset(0);
        GeometryDash::NextLevel();

    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
        anim->NextFrame();
    }
}

void Home::Draw()
{
    backg->Draw();
    scene->Draw();
    title->Draw(window->CenterX(), 85, Layer::FRONT);
    //play->Draw(window->CenterX(), 300, Layer::FRONT);
    anim->Draw(810, 275);
}

void Home::Finalize()
{
    delete anim;
    delete tileset;
    delete backg;

}
