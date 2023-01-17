#include "include/PenguinCannon.h"
#include "include/Sprite.h"
#include "include/Camera.h"
#include "include/Bullet.h"
#include "include/State.h"
#include "include/Game.h"
#include "include/InputManager.h"

PenguinCannon::PenguinCannon(GameObject &associated, std::weak_ptr< GameObject > penguinBody) : Component(associated)  {

    Sprite *spritePenguin = new Sprite(associated, "assets/img/cubngun.png");
    associated.AddComponent(spritePenguin);

    angle = 0;
    pbody = penguinBody;
}

PenguinCannon::~PenguinCannon() {

}

void PenguinCannon::Update(float dt) {
    if(pbody.lock()->IsDead()) {
        associated.RequestDelete();
    }
    else {
        associated.box.SetPosicaoCentro(pbody.lock()->box.Center());
	    InputManager &input = InputManager::GetInstance();

        int mousePosX =  input.GetMouseX() + Camera::pos.x;
        int mousePosY =  input.GetMouseY() + Camera::pos.y;
        Vec2 mouseVec = Vec2(mousePosX,mousePosY);
        angle = - associated.box.Center().AnguloParaAlvo(mouseVec) * 180 / M_PI;
        associated.angleDeg = angle;

        if (input.MousePress(LEFT_MOUSE_BUTTON)) {
            Shoot();
        }
    }
}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(std::string type) {

    if(type == "PenguinCannon") {
        return true;
    }
    else {
        return false;
    }
}

void PenguinCannon::Shoot() {

    float angulo = associated.angleDeg;
    Vec2 saidaBullet = associated.box.Center().GetRotated(angulo) + (associated.box.Medidas()/2) ;
    //Vec2 saidaBullet = associated.box.Center() + Vec2(10,10) * angulo;
    GameObject *objetoBullet = new GameObject();

    objetoBullet->box.SetPosicaoCentro(saidaBullet);
    //objetoBullet->box.SetPosicao(saidaBullet);
    //objetoBullet->angleDeg = -180 * angle / M_PI;
    objetoBullet->angleDeg = angle;
    Bullet *bullet = new Bullet(*objetoBullet, angulo , 300, 10, 800,"assets/img/penguinbullet.png");
    objetoBullet->AddComponent(bullet);

    State *state = &Game::GetInstance().GetState();
    state->AddObject(objetoBullet);
}