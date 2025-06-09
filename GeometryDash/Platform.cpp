#include "Platform.h"

Platform::Platform(float posX, float posY, uint platType, Color tint) : color(tint)
{
    switch (platType)
    {
    case SMALL:  platform = new Sprite("Resources/SmallGray.png"); type = SMALL; break;
    case MEDIUM: platform = new Sprite("Resources/MediumGray.png"); type = MEDIUM; break;
    case LARGE:  platform = new Sprite("Resources/LongGray.png"); type = LARGE; break;
    case FINISH: platform = new Sprite("Resources/Finish.png"); type = FINISH; break;
    }
    
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
