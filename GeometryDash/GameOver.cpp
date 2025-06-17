#include "Engine.h"
#include "GameOver.h"
#include "GeometryDash.h"
#include "Home.h"

void GameOver::Init()
{
    if (GeometryDash::player->Level() == 0) {
        title = new Sprite("Resources/GameOver1.png");
    }
    else {
        title = new Sprite("Resources/GameOver2.png");
    }
}

void GameOver::Update()
{
    if (window->KeyPress(VK_ESCAPE) || window->KeyPress(VK_RETURN))
        GeometryDash::NextLevel();
}

void GameOver::Draw()
{
    title->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

void GameOver::Finalize()
{
    delete title;
}
