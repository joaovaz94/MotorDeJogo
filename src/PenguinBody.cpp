#include "include/PenguinBody.h"
#include "include/PenguinCannon.h"
#include "include/State.h"
#include "include/Game.h"
#include "include/Sprite.h"
#include "include/Collider.h"
#include "include/Bullet.h"
#include "include/Camera.h"

PenguinBody *PenguinBody::player;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated)  {

    Sprite *spritePenguin = new Sprite(associated, "assets/img/penguin.png");
    associated.AddComponent(spritePenguin);
    Collider *colisor = new Collider(associated);
    associated.AddComponent(colisor);

    speed = Vec2(1,0);
    linearSpeed = 0;
    angle = 0;
    hp = 10;
    player = this;
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
}

void PenguinBody::Update(float dt) {
    //if(hp <= 0) {
    //    this->associated.RequestDelete();
    //    Camera::Unfollow();
    //}
    //else{
	    InputManager &input = InputManager::GetInstance();

        if(input.IsKeyDown(W_KEY)) {
            if(linearSpeed <= 300) {
                linearSpeed++;

            }
        }
        if(input.IsKeyDown(S_KEY)) {
            if(linearSpeed >= -300) {
                linearSpeed--;
            }
        }
        if(input.IsKeyDown(A_KEY)) {
            speed = speed.GetRotated(-M_PI / 90);
        }
        if(input.IsKeyDown(D_KEY)) {
            speed = speed.GetRotated(M_PI / 90);
        }
        speed = speed.Normalize();
        Vec2 variacao = (speed * (dt * linearSpeed));
        associated.box = associated.box + variacao;
        associated.angleDeg = speed.atan() * 180 / M_PI;
    //}
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

void PenguinBody::NotifyCollision(GameObject &other) {
    State *state = &Game::GetInstance().GetState();
    if (other.GetComponent("Bullet") != nullptr)
    {
        Bullet *bullet = (Bullet *)other.GetComponent("Bullet");
        if (bullet->targetsPlayer)
        {
            this->hp = this->hp - bullet->GetDamage();
            std::cout << "Penguin hp" << std::to_string(this->hp) << std::endl;

            if(this->hp <= 0) {
                std::cout << "Penguin Morreu" << std::endl;
                this->associated.RequestDelete();
                Camera::Unfollow();

                GameObject *mortePenguin = new GameObject();
                mortePenguin->AddComponent(new Sprite(*mortePenguin ,"assets/img/penguindeath.png" ,5 ,0.1 ,0.5 ));
                Sound *somDeMorte = new Sound(*mortePenguin, "assets/audio/boom.wav");
                somDeMorte->Play(1);
                mortePenguin->AddComponent(somDeMorte);
                mortePenguin->box.SetPosicaoCentro(associated.box.Center());
                state->AddObject(mortePenguin);    
            }
        }
    }
}