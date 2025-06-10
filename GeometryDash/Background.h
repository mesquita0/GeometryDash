#pragma once
#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background é composto por sprites

class Background : public Object
{
private:
    Image * imgF;                      // imagem de fundo

    Sprite * backg1;                   // pano de fundo dinâmico 1
    Sprite * backg2;                   // pano de fundo dinâmico 2

    Color color;                        // cor do pano de fundo

public:
    Background(Color tint);             // construtor
    ~Background();                      // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
}; 
