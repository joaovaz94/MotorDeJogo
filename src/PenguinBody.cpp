#include "include/PenguinBody.h"
#include "include/PenguinCannon.h"
#include "include/State.h"
#include "include/Game.h"
#include "include/Sprite.h"
#include "include/Collider.h"

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
    //std::cout << "PenguinBody iniciado" << std::endl;
}

void PenguinBody::Update(float dt) {
    if(hp <= 0) {
        this->associated.RequestDelete();
    }
    else{
    //std::cout << "PenguinBody update" << std::endl;
	    InputManager &input = InputManager::GetInstance();
        //Vec2 penguinCenter = associated.box.Center();
        Vec2 penguinBegin = associated.box.Center() - Vec2(associated.box.h / 2,0);
        //Vec2 rotacao = associated.box.Medidas() /2 +associated.box.Center();
        Vec2 vZero = Vec2(0,0);
        //float velocidadeAngular = 1 / (M_PI * 16);    

        if(input.IsKeyDown(W_KEY)) {
            if(linearSpeed <= 300) {
            //if(speed.x <= 300) {
                linearSpeed++;
                //speed = speed + Vec2(1, 0);

            }
        }
        if(input.IsKeyDown(S_KEY)) {
            if(linearSpeed >= -300) {
            //if(speed.x >= -300) {
                linearSpeed--;
                //speed = speed - Vec2(1, 0);
            }
        }
        if(input.IsKeyDown(A_KEY)) {
            //speed = speed + speed.GetRotated(M_PI / 90);
            //speed = speed.RotateAroundVec(penguinCenter, -M_PI / 90);
            //rotacao = rotacao + rotacao.RotateAroundVec(penguinCenter, velocidadeAngular);
            //rotacao = rotacao + rotacao.RotateAroundVec(penguinCenter ,velocidadeAngular);
            //speed = speed.GetRotated(M_PI / 90);
            //speed = speed +speed.RotateAroundVec(penguinBegin, M_PI / 180 );
            speed = speed.GetRotated(M_PI / 90);
            //angle += M_PI /90;
            //speed =  speed.RotateAroundVec(vZero, M_PI/45);
            //speed = speed.RotateAroundVec(speed, -angle);
            //speed =  speed.RotateAroundVec(penguinCenter, -M_PI / 90);
        }
        if(input.IsKeyDown(D_KEY)) {
            //speed = speed + speed.GetRotated(-M_PI / 90);
            //speed = speed.RotateAroundVec(penguinCenter, M_PI / 90);
            //rotacao = rotacao + rotacao.RotateAroundVec(penguinCenter ,-velocidadeAngular);
            //associated.angleDeg -= linearSpeed;
            //speed = speed + speed.RotateAroundVec(penguinBegin , -M_PI / 180);
            speed = speed.GetRotated(-M_PI / 90);
            //angle -= M_PI /90;
            //speed = speed.RotateAroundVec(vZero, -M_PI/45);
            //speed = speed.RotateAroundVec(speed, -angle);
            //speed =  speed.RotateAroundVec(penguinCenter, +M_PI / 90);

        }
        std::cout << "Pos penguin antes: " << associated.box.Posicao().toStr() << std::endl;
        //speed = speed + Vec2(linearSpeed / 100, linearSpeed / 100);
        //speed = speed + Vec2(linearSpeed / 100, 0);
        //speed = speed.RotateAroundVec(penguinCenter, -angle * 180 * 100);
        speed = speed.Normalize();
        Vec2 variacao = (speed * (dt * linearSpeed));
        associated.box = associated.box + variacao;
        //associated.box.SetPosicao( associated.box + variacao);
        //associated.angleDeg = angle * 180;
        //associated.angleDeg = penguinCenter.AnguloParaAlvo(rotacao);
        associated.angleDeg = speed.atan() * 180 / M_PI;
        //angle = speed.atan() * 90 / M_PI;
        std::cout << "Pos penguin: " << associated.box.Posicao().toStr() << std::endl;
        std::cout << "Speed penguin: " << speed.toStr() << std::endl;
        std::cout << "Variacao penguin: " << variacao.toStr() << std::endl;
        std::cout << "Angle penguin: " << angle << std::endl;
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