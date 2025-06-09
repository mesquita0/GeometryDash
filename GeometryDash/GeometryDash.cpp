#include "Engine.h"
#include "GeometryDash.h"
#include "Home.h"
#include "GameOver.h"
#include "Player.h"

Game*   GeometryDash::level = nullptr;
Player* GeometryDash::player = nullptr;
Audio*  GeometryDash::audio = nullptr;
bool    GeometryDash::viewBBox = false;

void GeometryDash::Init() 
{
    // cria sistema de �udio
    audio = new Audio();
    audio->Add(MENU, "Resources/Menu.wav");
    audio->Add(MUSIC, "Resources/Music.wav");
    audio->Add(TRANSITION, "Resources/Transition.wav");

    // bounding box n�o vis�vel
    viewBBox = false;

    // cria jogador
    player = new Player();

    // inicializa n�vel de abertura do jogo
    level = new Home();
    level->Init();
}

void GeometryDash::Update()
{
    // habilita/desabilita visualiza��o da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;    

    // atualiza n�vel
    level->Update();
} 

void GeometryDash::Draw()
{
    // desenha n�vel
    level->Draw();
} 

void GeometryDash::Finalize()
{
    level->Finalize();

    delete player;
    delete audio;
    delete level;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura o motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(900, 450);
    engine->window->Color(30, 50, 80);
    engine->window->Title("Geometry Dash");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new GeometryDash());

    delete engine;
    return status;
}
