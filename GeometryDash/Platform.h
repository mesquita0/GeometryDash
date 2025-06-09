#pragma once
#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites

enum PLATTYPES { SMALL, MEDIUM, LARGE, FINISH };

class Platform : public Object
{
private:
    Sprite * platform = nullptr;            // sprite da plataforma
    Color color;                            // cor da plataforma

public:
    Platform(float posX, float posY, 
             uint platType, 
             Color tint);                   // construtor    
    ~Platform();                            // destrutor

    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
}; 

inline void Platform::Draw()
{ platform->Draw(x, y, z, 1.0f, 0.0f, color); }
