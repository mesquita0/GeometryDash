#pragma once
#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites

class Player : public Object
{
private:
    Sprite    * sprite;                 // animação do personagem
    float       velY;                   // velocidade vertical
    int         level;                  // nível finalizado
    float       rotation;
    bool        run_animation;
    bool        is_alive;
    bool        end_level;
    
public:
    Player();                           // construtor
    ~Player();                          // destrutor

    void Reset();                       // volta ao estado inicial
    void Reset(int level);              
    int Level();                        // último nível finalizado                     
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo
    float Height();                        
    bool  IsAlive();
    bool  IsEndLevel();

    void OnCollision(Object * obj);     // resolução da colisão
    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

inline int Player::Level()
{ return level; }

inline float Player::Bottom()
{ return y + sprite->Height()/2; }

inline float Player::Top()
{ return y - sprite->Height()/2; }

inline float Player::Height() { return sprite->Height(); }

inline bool Player::IsAlive() { return is_alive; }

inline bool Player::IsEndLevel() { return end_level; }

inline void Player::Draw()
{ sprite->Draw(x, y, z, 1.0f, rotation); }
