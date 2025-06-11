#include "GeometryDash.h"
#include "Engine.h"
#include "Home.h"
#include "GameOver.h"
#include "Level.h"
#include "Player.h"

std::vector<Game*> GeometryDash::levels = {};
Game*   GeometryDash::current_level = nullptr;
int     GeometryDash::level_index = 0;
Player* GeometryDash::player = nullptr;
Audio*  GeometryDash::audio = nullptr;
bool    GeometryDash::viewBBox = false;

void GeometryDash::Init() 
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(MENU, "Resources/Menu.wav");
    audio->Add(MUSIC, "Resources/Music.wav");
    audio->Add(TRANSITION, "Resources/Transition.wav");

    // bounding box não visível
    viewBBox = false;

    // cria jogador
    player = new Player();

    // cria níveis
    levels = {
        new Home(),
        new Level(1),
        new Level(2),
        new GameOver(),
    };

    // inicializa nível de abertura do jogo
    current_level = levels[0];
    current_level->Init();
}

void GeometryDash::Update()
{
    // habilita/desabilita visualização da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // atualiza nível
    current_level->Update();
} 

void GeometryDash::Draw()
{
    // desenha nível
    current_level->Draw();
} 

void GeometryDash::Finalize()
{
    current_level->Finalize();

    delete player;
    delete audio;

    for (auto level : levels) delete level;
}

void GeometryDash::NextLevel() 
{
    current_level->Finalize();
    level_index = (level_index + 1) % levels.size();
    current_level = levels[level_index];
    current_level->Init();
};

void GeometryDash::GameOverL()
{
    current_level->Finalize();
    level_index = levels.size() - 1;
    current_level = levels[level_index];
    current_level->Init();
};


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
