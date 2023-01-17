#include "include/PenguinBody.h"
#include "include/PenguinCannon.h"
#include "include/State.h"
#include "include/Game.h"
#include "include/Sprite.h"

PenguinBody *PenguinBody::player;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated)  {

    Sprite *spritePenguin = new Sprite(associated, "assets/img/penguin.png");
    associated.AddComponent(spritePenguin);

    speed = Vec2();
    linearSpeed = 0;
    angle = 0;
    hp = 10;
    player = this;
    //std::cout << "PenguinBody instanciado" << std::endl;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {

    State *state = &Game::GetInstance().GetState();

    GameObject *objetoCanhao = new GameObject();
    PenguinCannon *penguinCanhao = new PenguinCannon(*objetoCanhao, state->GetObjectPtr(&associated)); 
    objetoCanhao->AddComponent(penguinCanhao);
    pcannon = state->AddObject(objetoCanhao);
    //std::cout << "PenguinBody iniciado" << std::endl;
}

void PenguinBody::Update(float dt) {
    if(hp <= 0) {
        this->associated.RequestDelete();
    }
    else{
    //std::cout << "PenguinBody update" << std::endl;
	    InputManager &input = InputManager::GetInstance();
        linearSpeed = 1 / (M_PI * 16);    

        if(input.IsKeyDown(W_KEY)) {
            if(speed.x <= 10) {
                speed = speed + Vec2(1, 0);
            }
        }
        if(input.IsKeyDown(S_KEY)) {
            if(speed.x >= -10) {
                speed = speed + Vec2(-1, 0);
            }
        }
        if(input.IsKeyDown(A_KEY)) {
            speed = speed + speed.GetRotated(M_PI / 90);
        }
        if(input.IsKeyDown(D_KEY)) {
            speed = speed + speed.GetRotated(-M_PI / 90);
            //associated.angleDeg -= linearSpeed;
        }
        associated.box += speed * dt;
        associated.angleDeg = speed.atan() * 90 / M_PI;
    }
}

void PenguinBody::Render() {
    
}

bool PenguinBody::Is(std::string type) {

    if(type == "PenguinBody") {
        return true;
    }
    else {
        return false;
    }
}