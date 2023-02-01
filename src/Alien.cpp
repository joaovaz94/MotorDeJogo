#include "include/Alien.h"
#include "include/Sprite.h"
#include "include/State.h"
#include "include/Game.h"
#include "include/InputManager.h"
#include "include/Camera.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "include/Minion.h"
#include "include/Collider.h"
#include "include/Bullet.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {
    
    Sprite *spriteAlien = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(spriteAlien);

    Collider *colisor = new Collider(associated);
    associated.AddComponent(colisor);

    speed = Vec2(1,0);
    hp = 10;
    qtdMinions = nMinions;

    state = RESTING;

    alienCount++;

}
 Alien::~Alien() {
    //esvaziar o Array com minions
    minionArray.clear();
    alienCount--;
 }
 void Alien::Start() {
    //Popular o Array com minions
    State *state = &Game::GetInstance().GetState();
    std::weak_ptr<GameObject> alienCenter = state->GetObjectPtr(&associated);

    for(int i=0; i < qtdMinions; i++){
        GameObject *objetoMinion = new GameObject();
        float grausMinion = (M_PI * i * 360 / qtdMinions) / 180;
        Minion *minion = new Minion(*objetoMinion, alienCenter, grausMinion);
        minionArray.push_back(state->AddObject(objetoMinion));
        objetoMinion->AddComponent(minion);
    }
 }

 void Alien::Update(float dt) {


    if(hp > 0 ){
        if(state == RESTING){
            //std::cout << "Alien decansando, tempo: " << restTimer.Get() << std::endl;
            if(restTimer.Get() >= 0.5){
                speed = Vec2();
                //destination = Camera::pos - (Vec2(associated.box.w, associated.box.h)/2);
                Vec2 posAtual = associated.box.Posicao();
                destination = Camera::pos + Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT /2);
                //Vec2 direcao = destination - associated.box.Center();
                //speed = Vec2::Rotate(speed, -speed.AnguloParaAlvo(direcao));
                speed = (destination - posAtual).Normalize();
                //speed = speed.GetRotated(associated.box.Center().AnguloParaAlvo(destination));
                //speed = (destination - posAtual).Normalize();
                //speed = speed.Normalize();
                std::cout << "Alien Speed: " << speed.toStr()  << std::endl;
                std::cout << "Alien alvo: " << destination.toStr()  << std::endl;
                std::cout << "Alien pos: " << posAtual.toStr()  << std::endl;
                state = MOVING;
            }
            restTimer.Update(dt);
        }
        else { 
            associated.box.SetPosicao(associated.box.Posicao() + (speed * dt * 300));
            if(associated.box.Center().DistanciaDoVetor(destination) < 10){
                destination = Camera::pos + Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT /2);
                //destination = Camera::pos - (Vec2(associated.box.w, associated.box.h)/2);
                std::cout << "Alien vai atirar, alvo: " << destination.toStr()  << std::endl;
                int minionMaisProximo = GetMinionProximo(destination);
                std::shared_ptr<GameObject> minionApontado = minionArray[minionMaisProximo].lock();
                Minion *minionObjeto = (Minion *)minionApontado->GetComponent("Minion");
                minionObjeto->Shoot(destination);
                state = RESTING;
                restTimer.Restart();
            }
        }
            //associated.box = associated.box + speed * dt;

    }
    else {
        this->associated.RequestDelete();
    }
 }

void Alien::Render() {

}

bool Alien::Is(std::string type) {

    if(type == "Alien") {
        return true;
    }
    else {
        return false;
    }
}

int Alien::GetMinionProximo(Vec2 posTiro) {
    int maisProximo = 0;
    float minimaDistancia = MAXFLOAT;
    for(int i=0;i < (int)minionArray.size(); i++) {
        float distanciaAtual = minionArray[i].lock()->box.Center().DistanciaDoVetor(posTiro); 
        if (distanciaAtual < minimaDistancia) {
            minimaDistancia = distanciaAtual;
            maisProximo = i;
        }
    }
    return maisProximo;
}

void Alien::NotifyCollision(GameObject &other) {
    if(other.GetComponent("Bullet") != nullptr) {
        Bullet *bullet = (Bullet *)other.GetComponent("Bullet");
        if(bullet != nullptr && !bullet->targetsPlayer) {
            this->hp = this->hp - bullet->GetDamage();
            if(this->hp <= 0) {
                associated.RequestDelete();

                GameObject *morteDoAlien = new GameObject();
                morteDoAlien->AddComponent(new Sprite(*morteDoAlien, "assets/img/aliendeath.png", 4 , 0.1 , 0.4 ));
                Sound *somDeMorte = new Sound(*morteDoAlien, "assets/audio/boom.wav");
                somDeMorte->Play(1);
                morteDoAlien->AddComponent(somDeMorte);
                morteDoAlien->box.SetPosicaoCentro(associated.box.Center());
                Game::GetInstance().GetState().AddObject(morteDoAlien);
            }
        }
    }
}