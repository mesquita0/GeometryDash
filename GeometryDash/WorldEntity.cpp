#include "WorldEntity.h"
#include "GeometryDash.h"

WorldEntity::WorldEntity(float posX, float posY, EntityType platType, Color tint) : color(tint)
{
    type = platType;
    switch (platType)
    {
    case GROUND: entity = new Sprite("Resources/groundSquare_01_001.png"); break;
    case THORN: entity = new Sprite("Resources/obstacle_triangle.png"); break;
    case SMALL_THORN: entity = new Sprite("Resources/obstacle_small_triangle.png"); break;
    case SQUARE: entity = new Sprite("Resources/square.png"); break;
    default: entity = nullptr;
    }

    if (entity) {
        width  = entity->Width();
        height = entity->Height();
    }
    
    if (type == GROUND || type == SQUARE) {
        BBox(new Rect(-entity->Width()/2.0f, 
                      -entity->Height()/2.0f, 
                       entity->Width()/2.0f, 
                       entity->Height()/2.0f));
    }
    else if (type == SQUARE_SIDE) {
        int square_side = 34;

        BBox(new Rect(-square_side/2.0f, 
                      -square_side/2.0f + 7, 
                       -square_side/2.0f, 
                       square_side/2.0f));
    }
    else if (type == THORN || type == SMALL_THORN) {
        Point points[3] = { 
            {-entity->Width() / 2.0f, entity->Height() / 2.0f},
            {entity->Width() / 2.0f, entity->Height() / 2.0f},
            {0.0, -entity->Height() / 2.0f},
        };
        BBox(new Poly(points, 3));
    }
    else if (type == FINISH_BEFORE || type == FINISH) {
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
