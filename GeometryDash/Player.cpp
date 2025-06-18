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
    gravity = -1;
    rotation = 0;
    run_animation = false;
    is_alive = true;
    end_level = true;
    points = 0;
    max_points = 1;

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
    velY = 0;
    gravity = -1;
    rotation = 0;
    run_animation = false;
    is_alive = true;
    end_level = true;
}

void Player::Reset(int level)
{
    Reset();
    this->level = level;
}

void Player::OnCollision(Object * obj)
{
    switch (obj->Type())
    {
    case _FINISH:
        level++;
        points = max_points;
        break;

    case _STOP_CAMERA:
        end_level = true;
        break;

    case _MOVE_CAMERA:
        end_level = false;
        break;

    case THORN:
    case INVERTED_THORN:
    case THORN_PIT:
    case _BLOCK_SIDE:
        is_alive = false;
        break;

    case JUMP_PAD:
        jump(500);
        break;

    case JUMP_RING:
        if (window->KeyDown(VK_SPACE))
            jump(350);
        break;

    case GRAVITY_PORTAL_UP:
        gravity = 1;
        if (velY <= 0) velY = gravity * 1000 * gameTime;
        break;

    case GRAVITY_PORTAL_DOWN:
        gravity = -1;
        if (velY >= 0) velY = gravity * 1000 * gameTime;
        break;

    case BLOCK:
    case GROUND:
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

        if (velY * gravity >= 0)
            velY = 0;

        // mantém personagem em cima da plataforma
        if (gravity == -1 && velY == 0)
            MoveTo(x, obj->Y() - ((WorldEntity*)obj)->Height() / 2.0f - (sprite->Height()) / 2.0f);
        else if (gravity == 1 && velY == 0)
            MoveTo(x, obj->Y() + ((WorldEntity*)obj)->Height() / 2.0f + (sprite->Height()) / 2.0f);

        if (window->KeyDown(VK_SPACE))
            jump(350);
        break;
    }
}

void Player::Update()
{
    Translate(0, -velY * gameTime);

    float dx = GeometryDash::game_speed * gameTime;
    points += dx;
    if (end_level) 
        Translate(dx, 0);

    // ação da gravidade sobre o personagem
    velY += gravity * 1000 * gameTime;

    // atualiza animação
    if (run_animation) {
        rotation += 2 * gameTime * M_PI;

        if (rotation > 2 * M_PI)
            rotation -= 2 * M_PI;
    }

    OutputDebugString(std::to_string(GeometryDash::loopEnvironment).c_str());
}
