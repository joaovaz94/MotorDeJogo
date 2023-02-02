#include "include/StageState.h"
#include "include/TitleState.h"
#include "include/Game.h"
#include <iostream>
//#include "include/Face.h"
#include "include/Vec2.h"
#include <math.h>
#include "include/TileSet.h"
#include "include/TileMap.h"
#include "include/Camera.h"
#include "include/CameraFollower.h"
#include "include/Alien.h"
#include "include/PenguinBody.h"
#include "Colision.cpp"
const double PI = M_PI;


StageState::StageState() : backgroundMusic("assets/audio/stageState.ogg") {

    this->quitRequested = false;
	started = false;


	GameObject *gameObjectFundo = new GameObject();
	CameraFollower *cameraFollower =  new CameraFollower(*gameObjectFundo);

	gameObjectFundo->AddComponent(new Sprite(*gameObjectFundo, "assets/img/ocean.jpg"));
	gameObjectFundo->AddComponent(cameraFollower);
	//objectArray.emplace_back(gameObjectFundo);
	AddObject(gameObjectFundo);
	//this->bg->Render();

	GameObject *gameObjectMap = new GameObject();

	TileSet *tileset = new TileSet(64, 64, "assets/img/tileset.png");
	TileMap *tilemap = new TileMap(*gameObjectMap, "assets/map/tileMap.txt", tileset);
	gameObjectMap->AddComponent(tilemap);
	//gameObjectMap->box.x = 0;
	//gameObjectMap->box.y = 0;
	gameObjectMap->box.SetPosicao(Vec2(0,0));
	//objectArray.emplace_back(gameObjectMap);
	AddObject(gameObjectMap);

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

}

StageState::~StageState() {
    this->objectArray.clear();
}

void StageState::Start() {
	LoadAssets();

	StartArray();
	backgroundMusic.Play();
	started = true;
}

void StageState::LoadAssets() {
}

void StageState::Pause() {
	backgroundMusic.Stop();
}

void StageState::Resume() {
	backgroundMusic.Play();
}

void StageState::Update(float dt){
	InputManager &input = InputManager::GetInstance();
	Camera::Update(dt);

	//Checar se o jogador apertou ESC para sair 
	if(input.IsKeyDown(ESCAPE_KEY)) {
		State *state = new TitleState();
		Game::GetInstance().Push(state);
	}
	//Fazer Pause aqui

	UpdateArray(dt);

	std::vector<std::weak_ptr< GameObject >> temCollider;
	for (int i=0; i < (int)objectArray.size(); i++) {
		if(objectArray[i].get()->GetComponent("Collider") != nullptr) {
			temCollider.push_back(objectArray[i]);
		}
	}
	for (int i=0; i < (int)temCollider.size(); i++) {
		for(int j = i +1; j < temCollider.size();j++){
			if(Collision::IsColliding(temCollider[i].lock()->box, temCollider[j].lock()->box, temCollider[i].lock()->angleDeg * M_PI / 180, temCollider[j].lock()->angleDeg * M_PI / 180)){
				GameObject *objeto1 = temCollider[i].lock().get();
				GameObject *objeto2 = temCollider[j].lock().get();
				objeto1->NotifyCollision(*objeto2);
				objeto2->NotifyCollision(*objeto1);
			}
		}
	}

	for (int i=0; i < (int)objectArray.size(); i++) {
		if(objectArray[i].get()->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void StageState::Render() {
    //Trata da Parte 4 de Game::Run

    //for(int i = 0; i < (int)objectArray.size(); i++){
    //    objectArray[i].get()->Render();
    //}

	RenderArray();
}

//bool StageState::QuitRequested() {
//    return quitRequested;
//}



//std::weak_ptr< GameObject > StageState::AddObject(GameObject *go) {
//
//	std::shared_ptr< GameObject > ponteirpCompartilhado(go);
//	objectArray.push_back(ponteirpCompartilhado);
//
//	if(started) {
//		ponteirpCompartilhado->Start();
//	}
//	std::weak_ptr < GameObject > ptrRetorno(ponteirpCompartilhado);
//	return ptrRetorno;
//
//}

//std::weak_ptr< GameObject > StageState::GetObjectPtr(GameObject *go) {
//	for(int i=0; i < (int)objectArray.size(); i++) {
//		if( objectArray[i].get() == go){
//			std::weak_ptr <GameObject> ptrRetorno(objectArray[i]);
//			return ptrRetorno;
//		}
//	}
//	std::weak_ptr <GameObject> ptrNulo;
//	return ptrNulo;
//}