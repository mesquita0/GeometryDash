#include "Background.h"
#include "GeometryDash.h"

Background::Background(Color tint) : color(tint)
{
    MoveTo(window->CenterX(), window->CenterY(), Layer::BACK);

    // carrega imagem
    imgF = new Image("Resources/Backgrounds/game_bg_01_001-hd.png");

    // cria sprites do plano de fundo 
    backg1 = new Sprite(imgF);
    backg2 = new Sprite(imgF);
}

Background::~Background()
{
    delete imgF;
    delete backg1;
    delete backg2;
}

void Background::Update()
{
    // move sprites
    if (!GeometryDash::player->IsEndLevel())
        this->Translate(-50 * gameTime, 0);
}

void Background::Draw()
{
    // desenha plano de fundo
    backg1->Draw(x, y, Layer::MIDDLE, 1.0f, 0.0f, color);
    backg2->Draw(x + imgF->Width(), window->Height()/2.0f, Layer::MIDDLE, 1.0f, 0.0f, color);

    // traz pano de fundo de volta para dentro da tela
    if (x + imgF->Width()/2.0f < 0)
        this->Translate(imgF->Width(), 0);
}
