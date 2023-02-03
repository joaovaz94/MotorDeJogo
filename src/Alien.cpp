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

Alien::Alien(GameObject &associated, float setTimeOffset) : Component(associated) {
    
    Sprite *spriteAlien = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(spriteAlien);

    Collider *colisor = new Collider(associated);
    associated.AddComponent(colisor);

    speed = Vec2(1,0);
    hp = 10;
    qtdMinions = 3;

    timeOffset = setTimeOffset;
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
    State *state = &Game::GetInstance().GetCurrentState();
    std::weak_ptr<GameObject> alienCenter = state->GetObjectPtr(&associated);

    for(int i=0; i < qtdMinions; i++){
        GameObject *objetoMinion = new GameObject();
        float grausMinion = (M_PI * i * 360 / qtdMinions) / 180;
        Minion *minion = new Minion(*objetoMinion, alienCenter, grausMinion);
        minionArray.push_back(state->AddObject(objetoMinion));
        objetoMinion->AddComponent(minion);
    }
 }

 void Alien::Update(float dt)
 {

    if (state == RESTING)
    {
        if (restTimer.Get() >= 10.5)
        {
            Vec2 posAtual = associated.box.Posicao();
            destination = Camera::pos + Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2);
            speed = (destination - posAtual).Normalize();
            state = MOVING;
        }
        restTimer.Update(dt + timeOffset);
    }
    else
    {
        Vec2 novaPos = associated.box.Posicao() + (speed * dt * 300);
        if(novaPos.x > -40 && novaPos.x < 1340 && novaPos.y > -10 && novaPos.y < 1280 ){
            associated.box.SetPosicao(associated.box.Posicao() + (speed * dt * 300));
        }
        if (associated.box.Center().DistanciaDoVetor(destination) < 100)
        {
            destination = Camera::pos + Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2);
            int minionMaisProximo = GetMinionProximo(destination);
            std::shared_ptr<GameObject> minionApontado = minionArray[minionMaisProximo].lock();
            Minion *minionObjeto = (Minion *)minionApontado->GetComponent("Minion");
            minionObjeto->Shoot(destination);
            speed = Vec2();
            restTimer.Restart();
            state = RESTING;
        }
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
                Game::GetInstance().GetCurrentState().AddObject(morteDoAlien);
            }
        }
    }
}