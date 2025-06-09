#include "Platform.h"

Platform::Platform(float posX, float posY, PlatType platType, Color tint) : color(tint)
{
    type = platType;
    switch (platType)
    {
    case GROUND: platform = new Sprite("Resources/groundSquare_01_001.png"); break;
    }

    width = platform->Width();
    
    BBox(new Rect(-platform->Width()/2.0f, 
                  -platform->Height()/2.0f, 
                   platform->Width()/2.0f, 
                   platform->Height()/2.0f));

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
