#include "Game.h"

//Inicializa ponteiro para zero para ser inicializado na primeira chamada do GetInstance
//Game *Game::instance = 0;

//Definição de método de retornar instnacia de Game de acordo com padrãp Singleton
Game& Game::GetInstance() {

    if(instance == nullptr) {
        instance = new Game("Janela", 640, 480);
    }
    return *instance;
}

//Construtor da instância Game
Game::Game(std::string title, int widith, int height){

    if(instance != nullptr) {
        instance = this;
    }   
    else {
        throw  "Erro de lógica, jogo instanciado erroneamente\n";
    }

    //inicialização de biblioteca SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        SDL_Log("Não foi possível inicializar a biblioteca SDL erro: %s", SDL_GetError());
        throw "Erro de SDL\n";
    }

    //inicialização de biblioteca de imagens
    int flags_img = IMG_INIT_JPG | IMG_INIT_PNG;
    int iniciada_img = IMG_Init(flags_img);
    if((iniciada_img&flags_img) != flags_img) {
        std::cout << "Erro: " << IMG_GetError();
        throw "Erro ao iniciar suporte de jpg e png";
    }
    
    //inicialização de biblioteca de audio
    int flags_aud = MIX_INIT_MP3 | MIX_INIT_OGG;
    int iniciada_aud = Mix_Init(flags_aud);
    if((iniciada_aud&flags_aud) != flags_aud) {
        std::cout << "Erro: " << Mix_GetError();
        throw "Erro ao iniciar suporte de mp3 e ogg";
    }
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 1024)) {
        std::cout << "Erro: " << Mix_GetError();
        throw "Erro ao iniciar OpenAudio";
    }
    //Alocação do número de trilhas de audio
    Mix_AllocateChannels(32);

    //Criação da Janela de Jogo
    SDL_Window* window = SDL_CreateWindow(
        "Janela do Joguinho",    //Título da janela
        SDL_WINDOWPOS_CENTERED, //Posição inicial de x
        SDL_WINDOWPOS_CENTERED, //Posição inicial de y
        widith,                    //Largura em pixels
        height,                    //Altura em pixels
        0                       //Flags para a janela
    );

    //Criação de Renderizador para a Janela
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
    return *state;
}

SDL_Renderer* Game::GetRenderer() {
   return renderer; 
}

void Game::Run() {
    //Fazer loop de jogo
    //Que faz
    //1. Verifica, controla e carrega as telas de jogo
    //2. Os dados de input são recebidos e processados
    //3. Osobjetos tem seus respectivos estados (posição, HP, ...)
    //4. Os objetos são desenhados na tela
}