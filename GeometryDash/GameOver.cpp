#include "Engine.h"
#include "GameOver.h"
#include "GeometryDash.h"
#include "Home.h"

void GameOver::Init()
{
    progress_bar = new Sprite("Resources/util.png");
    empty_bar = new Sprite("Resources/util.png");
    progress_bar_color = new Color{ 0, 1, 0, 1 };
    empty_bar_color = new Color{ 0, 0, 0, 1 };

    if (GeometryDash::player->Level() == 0) {
        title = new Sprite("Resources/GameOver1.png");
    }
    else {
        title = new Sprite("Resources/GameOver2.png");
    }

    progress_barX = (275 + 350 * GeometryDash::player->percentage()) - 
                    progress_bar->Width() / 2.0f;

    OutputDebugString(std::to_string(GeometryDash::player->percentage()).c_str());
}

void GameOver::Update()
{
    if (window->KeyPress(VK_ESCAPE) || window->KeyPress(VK_RETURN))
        GeometryDash::NextLevel();
}

void GameOver::Draw()
{
    title->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);
    empty_bar->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 1, 0, *empty_bar_color);
    progress_bar->Draw(progress_barX, window->CenterY(), Layer::BACK, 1, 0, *progress_bar_color);
}

void GameOver::Finalize()
{
    delete progress_bar;
    delete progress_bar_color;
    delete empty_bar;
    delete empty_bar_color;
    delete title;
}
