#include "include/TitleState.h"
#include "include/GameObject.h"
#include "include/Sprite.h"
#include "include/InputManager.h"
#include "include/StageState.h"
#include "include/Game.h"
#include "include/Camera.h"

TitleState::TitleState() {

    GameObject *titleImageGO = new GameObject();
	titleImageGO->AddComponent(new Sprite(*titleImageGO, "assets/img/title.jpg"));
    AddObject(titleImageGO);
}

TitleState::~TitleState() {
}

void TitleState::LoadAssets() {
    
}

void TitleState::Update(float dt) {


	InputManager &input = InputManager::GetInstance();

	if(input.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	if(input.KeyPress(SPACE_BAR_KEY)) {
        State *stage = new StageState();
        Game::GetInstance().Push(stage);
	}
}

void TitleState::Render() {
    RenderArray();
}

void TitleState::Start() {
    Camera::Reset();
}

void TitleState::Pause() {

}

void TitleState::Resume() {

}