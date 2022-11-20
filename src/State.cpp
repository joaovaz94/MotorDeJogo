#include "include/State.h"
#include <iostream>
#include "include/Face.h"
#include "include/Vec2.h"
#include <math.h>
#include "include/TileSet.h"
#include "include/TileMap.h"
#include "include/Camera.h"
#include "include/CameraFollower.h"
const double PI = M_PI;


//State::State() :music("./resources/audio/stageState.ogg"), bg("./resources/img/ocean.jpg") {
State::State() {
    this->quitRequested = false;
	GameObject *gameObjectFundo = new GameObject();
	bg = new Sprite(*gameObjectFundo, "assets/img/ocean.jpg");
	CameraFollower *cameraFollower =  new CameraFollower(*gameObjectFundo);

	gameObjectFundo->AddComponent(bg);
	gameObjectFundo->AddComponent(cameraFollower);
	objectArray.emplace_back(gameObjectFundo);
	//this->bg->Render();

	GameObject *gameObjectMap = new GameObject();

	TileSet *tileset = new TileSet(64, 64, "assets/img/tileset.png");
	TileMap *tilemap = new TileMap(*gameObjectMap, "assets/map/tileMap.txt", tileset);
	gameObjectMap->AddComponent(tilemap);
	gameObjectMap->box.x = 0;
	gameObjectMap->box.y = 0;
	objectArray.emplace_back(gameObjectMap);

	music = new Music("assets/audio/stageState.ogg");
    music->Play(-1);
}

State::~State() {
    this->objectArray.clear();
}

void State::LoadAssets() {
	//
}

void State::Update(float dt){
	//Input();
	InputManager &input = InputManager::GetInstance();
	Camera::Update(dt);

	//Checar se o jogador apertou ESC para sair 
	if(input.IsKeyDown(ESCAPE_KEY) || input.QuitRequested()) {
		quitRequested = true;
	}

	//Se apertar espaço cria face de pinguin
	if(input.IsKeyDown(SPACE_BAR_KEY)) {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( input.GetMouseX(), input.GetMouseY() );
				AddObject((int)objPos.x + Camera::pos.x, (int)objPos.y + Camera::pos.x);
	}


	for (int i=0; i < (int)objectArray.size(); i++) {
		objectArray[i].get()->Update(dt);
	}

	for (int i=0; i < (int)objectArray.size(); i++) {
		//Tratamento pra quando a face morrer
		if(objectArray[i].get()->IsDead()) {
			objectArray[i].get()->RemoveComponent(objectArray[i].get()->GetComponent("Sprite"));
			objectArray[i].get()->RemoveComponent(objectArray[i].get()->GetComponent("Face"));
			Sound *soundToErase = (Sound *)objectArray[i].get()->GetComponent("Sound");
			//soundToErase->Play(1);
			if((!soundToErase->IsOpen()) || (soundToErase == nullptr)) {
				objectArray[i].get()->RemoveComponent(soundToErase);
				objectArray.erase(objectArray.begin() + i);
			}
		}
	}
}

void State::Render() {
    //Trata da Parte 4 de Game::Run

    //Não entendi muito bem
    //bg.Render(this->bg.GetWidth(),this->bg.GetWidth());
    //bg.Render(0,0);
    for(int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i].get()->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

/*
void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}
*/

void State::AddObject(int mouseX, int mouseY) {

    GameObject *inimigo = new GameObject();
    Sprite *pinguin = new Sprite(*inimigo, "./assets/img/penguinface.png");
	inimigo->AddComponent(pinguin);
    
	//Adicionando a posicao de um GameObject
    inimigo->box.w = pinguin->GetWidth();
    inimigo->box.h = pinguin->GetHeigth();
    inimigo->box.x = mouseX + Camera::pos.x - (inimigo->box.w /2);
    inimigo->box.y = mouseY + Camera::pos.y - (inimigo->box.h /2);

    Sound *som_pinguin = new Sound(*inimigo, "./assets/audio/boom.wav" );
	inimigo->AddComponent(som_pinguin);

    Face *face_pinguin = new Face(*inimigo);
	inimigo->AddComponent(face_pinguin);

    //colocar este objeto de penguin no vetor de objetos
    objectArray.emplace_back(inimigo);
}