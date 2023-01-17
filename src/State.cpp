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
#include "include/PenguinBody.h"
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
	//gameObjectMap->box.x = 0;
	//gameObjectMap->box.y = 0;
	gameObjectMap->box.SetPosicao(Vec2(0,0));
	objectArray.emplace_back(gameObjectMap);

	//Criação de Alien no mapa
	GameObject *gameObjectAliens = new GameObject();
	int qtdMinions = 3;
	Alien *alien = new Alien(*gameObjectAliens, qtdMinions);
	gameObjectAliens->AddComponent(alien);
	//gameObjectAliens->box.SetPosicaoCentro(700,500);
	gameObjectAliens->box.SetPosicao((Vec2(512, 300) - gameObjectAliens->box.Medidas())/2);

	AddObject(gameObjectAliens);

	//Criação de Penguin no Jogo
	GameObject *gameObjectPenguin = new GameObject();
	PenguinBody *penguinBody = new PenguinBody(*gameObjectPenguin);
	gameObjectPenguin->AddComponent(penguinBody);
	gameObjectPenguin->box.SetPosicaoCentro(Vec2(704,640));

	//objectArray.emplace_back(gameObjectPenguin);
	AddObject(gameObjectPenguin);

	Camera::Follow(gameObjectPenguin);

	
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


	for (int i=0; i < (int)objectArray.size(); i++) {
		objectArray[i].get()->Update(dt);
		//objectArray[i]->Update(dt);
	}

	for (int i=0; i < (int)objectArray.size(); i++) {
		if(objectArray[i].get()->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::Render() {
    //Trata da Parte 4 de Game::Run

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