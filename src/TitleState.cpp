#include "include/TitleState.h"
#include "include/GameObject.h"
#include "include/Sprite.h"
#include "include/InputManager.h"
#include "include/StageState.h"
#include "include/Game.h"
#include "include/Camera.h"
#include "include/Text.h"

TitleState::TitleState() {

    GameObject *titleImageGO = new GameObject();
	titleImageGO->AddComponent(new Sprite(*titleImageGO, "assets/img/title.jpg"));
    AddObject(titleImageGO);

    GameObject *textoComecoGO = new GameObject();
    textoComecoGO->box.SetPosicaoCentro(GAME_SCREEN_WIDTH/2, 500);
    textoComecoGO->AddComponent(new Text(*textoComecoGO, "assets/font/Call me maybe.ttf", 50, Text::BLENDED, "Press space to play", {255, 0, 0, SDL_ALPHA_OPAQUE}));
    this->AddObject(textoComecoGO);
}

TitleState::~TitleState() {
    objectArray.clear();
}

void TitleState::LoadAssets() {
    
}

void TitleState::Update(float dt) {


	InputManager &input = InputManager::GetInstance();
    UpdateArray(dt);
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
    LoadAssets();
    StartArray();
    started = true;
}

void TitleState::Pause() {

}

void TitleState::Resume() {

}