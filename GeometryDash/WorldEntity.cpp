#include "WorldEntity.h"
#include "GeometryDash.h"

WorldEntity::WorldEntity(float posX, float posY, EntityTypeSprite platType, Color tint) : color(tint)
{
    switch (platType)
    {
    case GROUND1:         type = GROUND;         entity = new Sprite("Resources/Block/GroundSquare.png"); break;
    case THORN1:          type = THORN;          entity = new Sprite("Resources/Thorn/Spike01.png"); break;
    case THORN2:          type = THORN;          entity = new Sprite("Resources/Thorn/Spike02.png"); break;
    case INVERTED_THORN1: type = INVERTED_THORN; entity = new Sprite("Resources/Thorn/InvertedSpike01.png"); break;
    case INVERTED_THORN2: type = INVERTED_THORN; entity = new Sprite("Resources/Thorn/InvertedSpike02.png"); break;
    case SMALL_THORN1:    type = THORN;          entity = new Sprite("Resources/Thorn/SmallSpike01.png"); break;
    case SMALL_THORN2:    type = THORN;          entity = new Sprite("Resources/Thorn/SmallSpike02.png"); break;
    case THORN_PIT1:      type = THORN_PIT;      entity = new Sprite("Resources/Thorn/ThornPit01.png"); break;
    case THORN_PIT2:      type = THORN_PIT;      entity = new Sprite("Resources/Thorn/ThornPit02.png"); break;
    case THORN_PIT3:      type = THORN_PIT;      entity = new Sprite("Resources/Thorn/ThornPit03.png"); break;
    case BLOCK_GRID:      type = BLOCK;          entity = new Sprite("Resources/Block/GridBlock01.png"); break;
    case BLOCK1:          type = BLOCK;          entity = new Sprite("Resources/Block/Block01.png"); break;
    case BLOCK2:          type = BLOCK;          entity = new Sprite("Resources/Block/Block02.png"); break;
    case BLOCK3:          type = BLOCK;          entity = new Sprite("Resources/Block/Block03.png"); break;
    case BLOCK4:          type = BLOCK;          entity = new Sprite("Resources/Block/Block04.png"); break;
    case BLOCK5:          type = BLOCK;          entity = new Sprite("Resources/Block/Block05.png"); break;
    case JUMP_PAD1:       type = JUMP_PAD;       entity = new Sprite("Resources/Transporter/YellowJumpPad.png"); break;
    case JUMP_RING1:      type = JUMP_RING;      entity = new Sprite("Resources/Transporter/YellowJumpRing.png"); break;
    case FINISH_BEFORE:   type = _FINISH_BEFORE; break;
    case BLOCK_SIDE:      type = _BLOCK_SIDE; break;
    case FINISH:          type = _FINISH; break;
    }

    if (entity) {
        width  = entity->Width();
        height = entity->Height();
    }
    
    if (type == GROUND || type == BLOCK || type == THORN_PIT || type == JUMP_PAD || type == JUMP_RING) {
        BBox(new Rect(-entity->Width()/2.0f, 
                      -entity->Height()/2.0f, 
                       entity->Width()/2.0f, 
                       entity->Height()/2.0f));
    }
    else if (type == _BLOCK_SIDE) {
        int square_side = 34;

        BBox(new Rect(-square_side/2.0f, 
                      -square_side/2.0f + 7, 
                       -square_side/2.0f, 
                       square_side/2.0f));
    }
    else if (type == THORN) {
        Point points[3] = { 
            {-entity->Width() / 2.0f, entity->Height() / 2.0f},
            {entity->Width() / 2.0f, entity->Height() / 2.0f},
            {0.0, -entity->Height() / 2.0f},
        };
        BBox(new Poly(points, 3));
    }
    else if (type == INVERTED_THORN) {
        Point points[3] = {
            {-entity->Width() / 2.0f, -entity->Height() / 2.0f},
            {entity->Width() / 2.0f, -entity->Height() / 2.0f},
            {0.0, entity->Height() / 2.0f},
        };
        BBox(new Poly(points, 3));
    }
    else if (type == _FINISH_BEFORE || type == _FINISH) {
        BBox(new Rect(-10, 
                       -posY,
                       10,
                       window->Height() - posY));
    }

    MoveTo(posX, posY, Layer::MIDDLE);
}

WorldEntity::~WorldEntity()
{
    delete entity;
}

void WorldEntity::Update()
{
    if (!GeometryDash::player->IsEndLevel())
        Translate(-250.0f * gameTime, 0);
}
