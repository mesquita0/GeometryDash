#include "Engine.h"
#include "GameOver.h"
#include "GeometryDash.h"
#include "Home.h"

void GameOver::Init()
{
    title = new Sprite("Resources/GameOver.png");
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
