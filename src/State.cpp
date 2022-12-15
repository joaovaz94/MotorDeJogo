#include "include/State.h"
#include <iostream>
#include "include/Face.h"
#include "include/Vec2.h"
#include <math.h>
#include "include/TileSet.h"
#include "include/TileMap.h"
#include "include/Camera.h"
#include "include/CameraFollower.h"
#include "include/Alien.h"
const double PI = M_PI;


State::State() {
    this->quitRequested = false;
	started = false;
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

	//Criação de Alien no mapa
	GameObject *gameObjectAliens = new GameObject();
	int qtdMinions = 2;
	Alien *alien = new Alien(*gameObjectAliens, qtdMinions);
	gameObjectAliens->AddComponent(alien);
	//gameObjectAliens->box.SetPosicaoCentro(700,500);
	gameObjectAliens->box.SetPosicaoCentro(Vec2(512, 300) - Vec2(gameObjectAliens->box.x,gameObjectAliens->box.y));

	objectArray.emplace_back(gameObjectAliens);

	
	music = new Music("assets/audio/stageState.ogg");
    music->Play(-1);

	started = true;
}

State::~State() {
    this->objectArray.clear();
}

void State::Start() {
	LoadAssets();

	for(int i=0; i < (int)objectArray.size(); i++) {
		objectArray[i].get()->Start();
	}
	started = true;
}

void State::LoadAssets() {
}

void State::Update(float dt){
	InputManager &input = InputManager::GetInstance();
	Camera::Update(dt);

	//Checar se o jogador apertou ESC para sair 
	if(input.IsKeyDown(ESCAPE_KEY) || input.QuitRequested()) {
		quitRequested = true;
	}

	//Se apertar espaço cria face de pinguin
	//Tirando Faces de pinguins pois não devem ser criadas
	/*
	if(input.IsKeyDown(SPACE_BAR_KEY)) {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( input.GetMouseX(), input.GetMouseY() );
				AddObject((int)objPos.x + Camera::pos.x, (int)objPos.y + Camera::pos.x);
	}
	*/

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
    for(int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i].get()->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}



std::weak_ptr< GameObject > State::AddObject(GameObject *go) {

	std::shared_ptr< GameObject > ponteirpCompartilhado(go);
	objectArray.push_back(ponteirpCompartilhado);

	if(started) {
		ponteirpCompartilhado->Start();
	}
	std::weak_ptr < GameObject > ptrRetorno(ponteirpCompartilhado);
	return ptrRetorno;

	/*
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
	*/
}

std::weak_ptr< GameObject > State::GetObjectPtr(GameObject *go) {
	for(int i=0; i < (int)objectArray.size(); i++) {
		if( objectArray[i].get() == go){
			std::weak_ptr <GameObject> ptrRetorno(objectArray[i]);
			return ptrRetorno;
		}
	}
	std::weak_ptr <GameObject> ptrNulo;
	return ptrNulo;
}