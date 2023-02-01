#include "include/Bullet.h"
#include "include/Sprite.h"
#include <iostream>
#include "include/Collider.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer) : Component(associated){

    Sprite *spriteBullet = new Sprite(associated, sprite, frameCount, frameTime);
    associated.AddComponent(spriteBullet);
    Collider *colisor = new Collider(associated);
    associated.AddComponent(colisor);
    //std::cout << "Angulo Passado: " << angle << std::endl;
    this->speed = Vec2(1,0).GetRotated(angle) * speed;
    //std::cout << "Bullet angle: " << this->speed.toStr() << std::endl;
    distanceLeft = maxDistance;
    this->damage = damage;
    this->type = "Bullet";
    this->targetsPlayer = targetsPlayer;
}


void Bullet::Start() {}

void Bullet::Update(float dt) {

    if( distanceLeft <= 0) {
        //std::cout << "Acabou a distancia" << std::endl;
        associated.RequestDelete();
    }
    else {
        Vec2 deslocamento = (speed * dt);
        associated.box.SetPosicao(associated.box.Posicao() + deslocamento);
        //associated.box += (speed * dt);
        distanceLeft -= deslocamento.GetMagnitude();
        //std::cout << "Bullet pos: " << associated.box.Posicao().toStr() << std::endl;
        //std::cout << "Bullet distancia restante: " << distanceLeft << std::endl;
    }

}

void Bullet::Render() {

}

bool Bullet::Is(std::string type) {

    if(type == "Bullet") {
        return true;
    }
    else {
        return false;
    }
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::NotifyCollision(GameObject &other) {
    if((other.GetComponent("PenguinBody") != nullptr && targetsPlayer )|| (other.GetComponent("Alien") != nullptr && !targetsPlayer)){
        associated.RequestDelete();
    }
}