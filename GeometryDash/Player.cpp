#include "Player.h"
#include "GeometryDash.h"
#include "WorldEntity.h"

#ifndef M_PI
#   define M_PI 3.1415926535897932384626433832
#endif 

Player::Player()
{
    sprite = new Sprite("Resources/cube.png");

    // cria bounding box
    BBox(new Rect(
        -1.0f * (sprite->Width()) / 2.0f,
        -1.0f * (sprite->Height()) / 2.0f,
        (sprite->Width()) / 2.0f,
        (sprite->Height()) / 2.0f));
    
    // inicializa estado do player
    level = 0;
    velY = 0;
    rotation = 0;
    run_animation = false;
    is_alive = true;
    end_level = false;

    // posição inicial
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
}

Player::~Player()
{
    delete sprite;
}

void Player::Reset()
{
    // volta ao estado inicial
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
    level = 0;
    rotation = 0;
    run_animation = false;
    is_alive = true;
    end_level = false;
}

void Player::Reset(int level)
{
    Reset();
    this->level = level;
}

void Player::OnCollision(Object * obj)
{
    if (obj->Type() == _FINISH)
    {
        // chegou ao final do nível
        level++;
    }
    else if (obj->Type() == _FINISH_BEFORE) {
        end_level = true;
    }
    else if (obj->Type() == THORN || obj->Type() == INVERTED_THORN || obj->Type() == THORN_PIT || obj->Type() == _BLOCK_SIDE) {
        is_alive = false;
    }
    else if (obj->Type() == JUMP_PAD) {
        velY = 500;
        run_animation = true;
    }
    else if (obj->Type() == JUMP_RING) {
        if (window->KeyDown(VK_SPACE))
        {
            velY = 350;
            run_animation = true;
        }
    }
    else if (obj->Type() == GROUND || obj->Type() == BLOCK)
    {
        // Setar frame para um de não rotação
        if (run_animation) {
            if (rotation <= 0.1 || rotation > 0.1 + 3 * M_PI / 2)
                rotation = 0;
            else if (rotation - M_PI / 2 <= 0.1)
                rotation = M_PI / 2;
            else if (rotation - M_PI <= 0.1)
                rotation = M_PI;
            else
                rotation = 3 * M_PI / 2;
        }
        run_animation = false;

        velY = 0;

        // mantém personagem em cima da plataforma
        MoveTo(x, obj->Y() - ((WorldEntity*)obj)->Height() / 2.0f - (sprite->Height()) / 2.0f);

        // ----------------------------------------------------------
        // Processa teclas pressionadas
        // ----------------------------------------------------------
        // jogador só pode pular enquanto estiver 
        // em cima de uma plataforma
        // ----------------------------------------------------------

        if (window->KeyDown(VK_SPACE))
        {
            // Ação Pulo
            velY = 350;

            run_animation = true;
        }
    }
}

void Player::Update()
{
    Translate(0, -velY * gameTime);

    if (end_level) 
        Translate(250 * gameTime, 0);

    // ação da gravidade sobre o personagem
    velY -= 1000 * gameTime;

    // atualiza animação
    if (run_animation) {
        rotation += M_PI / 30;

        if (rotation > 2 * M_PI)
            rotation -= 2 * M_PI;
    }
}
