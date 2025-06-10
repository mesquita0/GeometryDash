#include "Platform.h"

Platform::Platform(float posX, float posY, PlatType platType, Color tint) : color(tint)
{
    type = platType;
    switch (platType)
    {
    case GROUND: platform = new Sprite("Resources/groundSquare_01_001.png"); break;
    case OBSTACLE: platform = new Sprite("Resources/obstacle_triangle.png"); break;
    case OBSTACLE_SMALL: platform = new Sprite("Resources/obstacle_small_triangle.png"); break;
    }

    width = platform->Width();
    
    if (type == GROUND) {
        BBox(new Rect(-platform->Width()/2.0f, 
                      -platform->Height()/2.0f, 
                       platform->Width()/2.0f, 
                       platform->Height()/2.0f));
    }
    else {
        float offset = -17.0f;
        Point points[3] = { 
            {platform->Width() / 2.0f + offset, offset},
            {offset, platform->Height() + offset},
            {platform->Width() + offset, platform->Height() + offset}
        };
        BBox(new Poly(points, 3));
    }

    MoveTo(posX, posY, Layer::MIDDLE);
}

Platform::~Platform()
{
    delete platform;
}

void Platform::Update()
{
    // move plataforma apenas no eixo x
    Translate(-200.0f * gameTime, 0);
}
