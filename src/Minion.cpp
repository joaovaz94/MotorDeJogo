#include "include/Minion.h"
#include "include/Sprite.h"
#include "include/Bullet.h"
#include "include/State.h"
#include "include/Game.h"
#include <math.h>
#include <iostream>

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated){
    Sprite *spriteMinion = new Sprite(associated, "assets/img/minion.png");
    associated.AddComponent(spriteMinion);
    this->alienCenter = alienCenter;
    arc = arcOffsetDeg;
    std::shared_ptr<GameObject> alienObjeto = alienCenter.lock();
    this->type = "Minion";

    associated.box.SetPosicao(alienObjeto->box.Posicao());
    //associated.AddComponent(spriteMinion);
}

Minion::~Minion() {
}

void Minion::Update(float dt) {

    //Velocidade angular
    float velocidadeAngular = 1 / (M_PI * 16);    
    Vec2 offsetPadrao = Vec2(200, 0);
    Vec2 centroMinion = associated.box.Medidas() /2;
    Vec2 centroAlien = alienCenter.lock()->box.Posicao();
    //std::cout << "Centro do minion: " << centroAlien.toStr() << std::endl;
    //Calculo da posição inicial do minion nesse update
    Vec2 posInicial = centroAlien - centroMinion + offsetPadrao.GetRotated(arc);

    arc += velocidadeAngular;
    associated.box.SetPosicao(posInicial);
}

void Minion::Render() {

}


bool Minion::Is(std::string type) {

    if(type == "Minion") {
        return true;
    }
    else {
        return false;
    }
}

void Minion::Shoot(Vec2 pos) {
    //Irá atirar projétil na direção indicada

    Vec2 saidaBullet = associated.box.Center();
    float angulo = saidaBullet.AnguloParaAlvo(pos);
    std::cout << "local de saida do tiro: " << saidaBullet.toStr() << std::endl;
    GameObject *objetoBullet = new GameObject();

    objetoBullet->box.SetPosicaoCentro(saidaBullet);
    Bullet *bullet = new Bullet(*objetoBullet, angulo , 100, 10, 500,"assets/img/minionbullet1.png");
    objetoBullet->AddComponent(bullet);

    State *state = &Game::GetInstance().GetState();
    state->AddObject(objetoBullet);
}