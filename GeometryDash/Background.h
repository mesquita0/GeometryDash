#pragma once
#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background � composto por sprites

class Background : public Object
{
private:
    Image * imgF;                      // imagem de fundo

    Sprite * backg1;                   // pano de fundo din�mico 1
    Sprite * backg2;                   // pano de fundo din�mico 2

    Color color;                        // cor do pano de fundo

public:
    Background(Color tint);             // construtor
    ~Background();                      // destrutor

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
}; 
