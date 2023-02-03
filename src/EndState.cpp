#include "include/EndState.h"
#include "include/GameObject.h"
#include "include/Sprite.h"
#include "include/InputManager.h"
#include "include/TitleState.h"
#include "include/Game.h"
#include "include/Camera.h"
#include "include/Text.h"
#include "include/GameData.h"

EndState::EndState() {

    GameObject *finalImageGO = new GameObject();
    Sprite *sprite;
    std::string textoresultado  = "ESC para sair e ESPACO para jogar";

    if (GameData::playerVictory)
    {
        sprite = new Sprite(*finalImageGO, "assets/img/win.jpg");
        backgrounMusic = new Music("assets/audio/endStateWin.ogg");
    }
    else {

        sprite = new Sprite(*finalImageGO, "assets/img/lose.jpg");
        backgrounMusic = new Music("assets/audio/endStateLose.ogg");
    }

    finalImageGO->AddComponent(sprite);
    finalImageGO->box.SetPosicao(Vec2(0,0));
    AddObject(finalImageGO);

    GameObject *textoFimGO = new GameObject();
    textoFimGO->box.SetPosicaoCentro( 100, 500);
    textoFimGO->AddComponent(new Text(*textoFimGO, "assets/font/Call me maybe.ttf", 50, Text::BLENDED, textoresultado, {255, 0, 0, SDL_ALPHA_OPAQUE}));
    this->AddObject(textoFimGO);
}

EndState::~EndState() {
    objectArray.clear();
}

void EndState::LoadAssets() {
    
}

void EndState::Update(float dt) {

	InputManager &input = InputManager::GetInstance();
    UpdateArray(dt);
	if((input.KeyPress(ESCAPE_KEY)) || (InputManager::GetInstance().QuitRequested())) {
		quitRequested = true;
	}
	if((input.KeyPress(SPACE_BAR_KEY))) {
        popRequested = true;
        //State *stage = new TitleState();
        //Game::GetInstance().Push(stage);
	}
}

void EndState::Render() {
    RenderArray();
}

void EndState::Start() {
    Camera::Reset();
    LoadAssets();
    StartArray();
    started = true;
    backgrounMusic->Play();
}

void EndState::Pause() {
    backgrounMusic->Stop();
}

void EndState::Resume() {

    backgrounMusic->Play();
    Camera::Reset();
}