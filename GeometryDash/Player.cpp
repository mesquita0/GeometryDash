#include "Player.h"
#include "GeometryDash.h"
#include "Platform.h"

Player::Player()
{
    tileset = new TileSet("Resources/cube.png", 67, 51, 4, 16);
    anim = new Animation(tileset, 0.05f, true);

    // cria bounding box
    BBox(new Rect(
        -1.0f * (tileset->TileWidth() - 30) / 2.0f + 1,
        -1.0f * (tileset->TileHeight() - 14) / 2.0f - 1,
        (tileset->TileWidth() - 30) / 2.0f + 1,
        (tileset->TileHeight() - 14) / 2.0f - 1));
    
    // inicializa estado do player
    level = 0;
    velY = 0;
    run_animation = false;
    is_alive = true;

    // posição inicial
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
}

Player::~Player()
{
    delete anim;
    delete tileset;    
}

void Player::Reset()
{
    // volta ao estado inicial
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
    level = 0;
    anim->Frame(0);
    run_animation = false;
    is_alive = true;
}

void Player::OnCollision(Object * obj)
{
    if (obj->Type() == FINISH)
    {
        // chegou ao final do nível
        level++;
    }
    else if (obj->Type() == OBSTACLE) {
        is_alive = false;
    }
    else
    {
        // Setar frame para um de não rotação
        if (run_animation) {
            int frames_to_finish_animation = (anim->Frame() % 4);
            if (frames_to_finish_animation != 0) 
                anim->Frame(anim->Frame() + (4 - frames_to_finish_animation));
        }
        run_animation = false;

        // mantém personagem em cima da plataforma
        velY = 0;

        // ----------------------------------------------------------
        // Processa teclas pressionadas
        // ----------------------------------------------------------
        // jogador só pode pular enquanto estiver 
        // em cima de uma plataforma
        // ----------------------------------------------------------

        if (window->KeyDown(VK_SPACE))
        {
            // toca efeito sonoro
            GeometryDash::audio->Play(TRANSITION);

            // Ação Pulo
            velY = 350;

            run_animation = true;
        }
    }
}

void Player::Update()
{
    Translate(0, -velY * gameTime);

    // ação da gravidade sobre o personagem
    velY -= 1000 * gameTime;

    // atualiza animação
    if (run_animation) anim->NextFrame();
}
