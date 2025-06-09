#pragma once
#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites

enum PlatType { GROUND, OBSTACLE, FINISH };

class Platform : public Object
{
private:
    Sprite * platform = nullptr;            // sprite da plataforma
    Color color;                            // cor da plataforma
    uint  width;

public:
    Platform(float posX, float posY, 
             PlatType platType,
             Color tint);                   // construtor    
    ~Platform();                            // destrutor

    uint Width() const;

    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
}; 

inline uint Platform::Width() const { return width;  }

inline void Platform::Draw()
{ platform->Draw(x, y, z, 1.0f, 0.0f, color); }
