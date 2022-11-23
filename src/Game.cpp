#include "include/Game.h"
#include "include/Resources.h"
#include <iostream>

//Inicializa ponteiro para zero para ser inicializado na primeira chamada do GetInstance
Game *Game::instance = nullptr;

//Definição de método de retornar instnacia de Game de acordo com padrãp Singleton
Game& Game::GetInstance() {

    if(Game::instance == nullptr) {
        Game::instance = new Game("Janela", 640, 480);
        std::cout << "Jogo iniciado em GetInstance\n";
    }
    return *Game::instance;
}

//Construtor da instância Game
Game::Game(std::string title, int widith, int height){

    frameStart = 0;
    dt = 0;

    if(Game::instance != nullptr) {
        std::cout <<  "Erro de lógica, jogo instanciado erroneamente\n";
    }   
    else {
        std::cout << "Jogo instanciado corretamente\n";
        Game::instance = this;
    }
    
    Game::instance = this;

    //inicialização de biblioteca SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        SDL_Log("Não foi possível inicializar a biblioteca SDL erro: %s", SDL_GetError());
        std::cout <<"Erro de SDL\n";
    }

    //inicialização de biblioteca de imagens
    int flags_img = IMG_INIT_JPG | IMG_INIT_PNG;
    //int iniciada_img = IMG_Init(flags_img);
    int iniciada_img = IMG_Init(flags_img);
    if((iniciada_img&flags_img) != flags_img) {
        std::cout << "Erro: " << IMG_GetError();
        std::cout << "Erro ao iniciar suporte de jpg e png";
    }
    

    //Criação da Janela de Jogo
    this->window = SDL_CreateWindow(
        title.c_str(),    //Título da janela
        SDL_WINDOWPOS_CENTERED, //Posição inicial de x
        SDL_WINDOWPOS_CENTERED, //Posição inicial de y
        widith,                    //Largura em pixels
        height,                    //Altura em pixels
        0                       //Flags para a janela
    );
    if(Game::window == nullptr){
        std::cout << "Erro ao iniciar janela";
    }

    //Criação de Renderizador para a Janela
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if(Game::renderer == nullptr){
        std::cout << "Erro ao iniciar renderizador";
    }

    //inicialização de biblioteca de audio
    int flags_aud = MIX_INIT_MP3 | MIX_INIT_OGG;
    int iniciada_aud = Mix_Init(flags_aud);
    if((iniciada_aud&flags_aud) != flags_aud) {
        std::cout << "Erro: " << Mix_GetError();
        std::cout << "Erro ao iniciar suporte de mp3 e ogg";
    }
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 1024)) {
        std::cout << "Erro: " << Mix_GetError();
        std::cout << "Erro ao iniciar OpenAudio";
    }
    //Alocação do número de trilhas de audio
    Mix_AllocateChannels(32);

    this->state = new State();

}

Game::~Game() {
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

State& Game::GetState() {
    return *(this->state);
}

SDL_Renderer* Game::GetRenderer() {
   return this->renderer; 
}

void Game::Run() {
    //Fazer loop de jogo
    state->Start();
    while(!state->QuitRequested()) {
        CalculateDeltaTime();
        //Que faz
        //1. Verifica, controla e carrega as telas de jogo
        //2. Os dados de input são recebidos e processados
        InputManager::GetInstance().Update();
        //3. Osobjetos tem seus respectivos estados (posição, HP, ...)
        state->Update(GetDeltaTime());// Descobrir qual float passar como parametro
        //4. Os objetos são desenhados na tela
        state->Render();
        SDL_RenderPresent(this->renderer);
        SDL_Delay(33);
    } //Fim do Loop

    //Liberar Recursos Carregados depois do Fim do Loop do Jogo
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

void Game::CalculateDeltaTime() {
    int frameAntigo = frameStart;
    frameStart = SDL_GetTicks();
    dt = (frameStart - frameAntigo) / 1000.0;
}

float Game::GetDeltaTime() {
    return dt;
}