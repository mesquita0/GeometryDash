#include "Engine.h"
#include "GeometryDash.h"
#include "Home.h"
#include "Level1.h"

void Home::Init()
{
    backg = new Sprite("Resources/TitleScreen.png");
    tileset = new TileSet("Resources/PressEnter.png", 72, 48, 1, 5);
    anim = new Animation(tileset, 0.180f, true);
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
        GeometryDash::NextLevel<Level1>();
    }
    else
    {
        anim->NextFrame();
    }
}

void Home::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    anim->Draw(545, 275);
}

void Home::Finalize()
{
    delete anim;
    delete tileset;
    delete backg;
}
