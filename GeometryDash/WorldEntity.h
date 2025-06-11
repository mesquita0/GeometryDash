#pragma once
#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites

enum EntityType { GROUND, THORN, SMALL_THORN, SQUARE, FINISH_BEFORE, FINISH };

class WorldEntity : public Object
{
private:
    Sprite * entity = nullptr;            // sprite da plataforma
    Color color;                            // cor da plataforma
    uint  width = 0;
    uint  height = 0;

public:
    WorldEntity(float posX, float posY, 
                EntityType platType,
                Color tint);                       
    ~WorldEntity();                            

    uint Width() const;
    uint Height() const;

    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
}; 

inline uint WorldEntity::Width() const { return width;  }

inline uint WorldEntity::Height() const { return height;  }

inline void WorldEntity::Draw()
{ if (entity) entity->Draw(x, y, z, 1.0f, 0.0f, color); }
