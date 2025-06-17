#include "Engine.h"
#include "GameOver.h"
#include "GeometryDash.h"
#include "Home.h"
#include <format>

void GameOver::Init()
{
    progress_bar = new Sprite("Resources/util.png");
    empty_bar = new Sprite("Resources/util.png");
    progress_bar_color = new Color{ 0, 1, 0, 1 };
    empty_bar_color = new Color{ 0, 0, 0, 1 };

    font = new Font("Resources/Font.png");
    font->Spacing(60);

    if (GeometryDash::player->Level() == 0) {
        title = new Sprite("Resources/GameOver1.png");
    }
    else {
        title = new Sprite("Resources/GameOver2.png");
    }

    playerPercentage = GeometryDash::player->percentage();
    progress_barX = (275 + 350 * playerPercentage) - progress_bar->Width() / 2.0f;

    OutputDebugString(std::to_string(playerPercentage).c_str());
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
    font->Draw(window->CenterX() - 35, window->CenterY() + 32, std::format("{:.1f}%", playerPercentage * 100), Color{1, 1, 1, 1}, Layer::FRONT, 0.4);
}

void GameOver::Finalize()
{
    delete progress_bar;
    delete progress_bar_color;
    delete empty_bar;
    delete empty_bar_color;
    delete font;
    delete title;
}
