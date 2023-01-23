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


 Alien::Action::Action(ActionType type, float x, float y) {
    this->type = type;
    pos = Vec2(x,y);
}

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {
    
    Sprite *spriteAlien = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(spriteAlien);

    Collider *colisor = new Collider(associated);
    associated.AddComponent(colisor);

    speed = Vec2();
    hp = 10;
    qtdMinions = nMinions;


}
 Alien::~Alien() {
    //esvaziar o Array com minions
    minionArray.clear();
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
	    InputManager &input = InputManager::GetInstance();

        int mousePosX =  input.GetMouseX() + Camera::pos.x;
        int mousePosY =  input.GetMouseY() + Camera::pos.y;
        if (input.MousePress(LEFT_MOUSE_BUTTON)) {
            //Botão Esquerdo deve atirar
            //Action acaoAtirar(Action::ActionType::SHOOT, (input.GetMouseX() + Camera::pos.x), (input.GetMouseY() + Camera::pos.y));
            Action acaoAtirar(Action::ActionType::SHOOT, mousePosX, mousePosY);
            taskQueue.push(acaoAtirar);

        }
        if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
            //Botão Direito deve movimentar alien para posição
            //Action acaoMover(Action::ActionType::MOVE, (input.GetMouseX() + Camera::pos.x), (input.GetMouseY() + Camera::pos.y));
            Action acaoMover(Action::ActionType::MOVE, mousePosX, mousePosY);
            taskQueue.push(acaoMover);
        }
        
        //Reseta a speed
        speed = Vec2();

        //std::cout << "Posicao Alien: " << associated.box.Center().toStr() << std::endl;

        associated.angleDeg += M_PI * dt * 6;
        //associated.box.SetPosicao(associated.box.Posicao() + Camera::pos);
        //Checar se há alguma ação na fila
        if(taskQueue.size() > 0) {
            Action acaoAtual = taskQueue.front();

            if(acaoAtual.type == Action::ActionType::MOVE) {
                Vec2 destino = acaoAtual.pos - (Vec2(associated.box.w, associated.box.h)/2);
                Vec2 posAtual = associated.box.Posicao();

                //Calcular se o Alien já chega à posição no próximo frame
                speed = (destino - posAtual).Normalize();

                //mudando a posição em velocidade constante
                associated.box.SetPosicao(associated.box.Posicao() + (speed * dt * 300));


                //senão tiver muito perto:
                if((destino - posAtual).GetMagnitude() < 10.0) {
                    associated.box.x = destino.x; 
                    associated.box.y = destino.y; 
                    taskQueue.pop();
                }
            }
            if(acaoAtual.type == Action::ActionType::SHOOT) {
                int minionMaisProximo = GetMinionProximo(acaoAtual.pos);
                //std::shared_ptr<GameObject> minionApontado = minionArray[minonAleatorio].lock();
                std::shared_ptr<GameObject> minionApontado = minionArray[minionMaisProximo].lock();
                //std::cout << "Minion sorteado: " << minonAleatorio << std::endl;
                Minion *minionObjeto = (Minion *)minionApontado->GetComponent("Minion");
                minionObjeto->Shoot(acaoAtual.pos);
                //std::cout << "Posicao para tiro: " << acaoAtual.pos.toStr() << std::endl;
                taskQueue.pop();
            }
        }
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