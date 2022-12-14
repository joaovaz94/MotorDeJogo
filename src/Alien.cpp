#include "include/Alien.h"
#include "include/Sprite.h"
#include "include/InputManager.h"
#include "include/Camera.h"
#include <iostream>


 Alien::Action::Action(ActionType type, float x, float y) {
    this->type = type;
    pos = Vec2(x,y);
}

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {
    
    //Sprite *spriteAlien = new Sprite(associated, "./assets/img/alien.png");
    Sprite *spriteAlien = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(spriteAlien);

    speed = Vec2(10,10);
    hp = 10;


}
 Alien::~Alien() {
    //esvaziar o Array com minions
    minionArray.clear();
 }
 void Alien::Start() {
    //Popular o Array com minions

 }

 void Alien::Update(float dt) {

    //std::cout << "Alien no inicio  do update" << std::endl;

    if(hp >= 0 ){
	    InputManager &input = InputManager::GetInstance();
        //Conferir se houve input para  o Alien
        if (input.MousePress(LEFT_MOUSE_BUTTON)) {
            //Botão Esquerdo deve atirar
            Action acaoAtirar(Action::ActionType::SHOOT, (input.GetMouseX() + Camera::pos.x), (input.GetMouseY() + Camera::pos.y));
            taskQueue.push(acaoAtirar);

            std::cout << "Alien mouse esquerdo" << std::endl;
        }
        if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
            //Botão Direito deve movimentar alien para posição
            Action acaoMover(Action::ActionType::MOVE, (input.GetMouseX() + Camera::pos.x), (input.GetMouseY() + Camera::pos.y));
            taskQueue.push(acaoMover);
            std::cout << "Alien mouse direito" << std::endl;
        }
        //std::cout << "Alien Ok 1" << std::endl;

        //Checar se há alguma ação na fila
        if(taskQueue.size() > 0) {
            for(int i=0; i < (int)taskQueue.size(); i++) {
                Action acaoAtual = taskQueue.front();

                std::cout << "Alien Ok 2" << std::endl;
                if(acaoAtual.type == Action::ActionType::MOVE) {
                    Vec2 destino = acaoAtual.pos - Vec2(associated.box.w /2,associated.box.h /2);
                    Vec2 posAtual = associated.box.Center();
                    std::cout << "destino: " << destino.toStr() << std::endl;
                    std::cout << "posAtual: " << posAtual.toStr() << std::endl;

                    //Calcular se o Alien já chega à posição no próximo frame
                    Vec2 diferenca = destino - posAtual;
                    diferenca = diferenca.Normalize();
                    std::cout << "diferença: " << diferenca.toStr() << std::endl;
                    float velLinear = 2;
                    speed = diferenca;
                    std::cout << "speed: " << diferenca.toStr() << std::endl;
                    std::cout << "Alien Ok 3" << std::endl;

                    associated.box.SetPosicaoCentro(associated.box.Center() + (speed * dt * velLinear));

                    //senão tiver muito perto:
                    if(speed.GetMagnitude() < 0.3) {
                        associated.box.x = destino.x; 
                        associated.box.y = destino.y; 
                        taskQueue.pop();
                    }
                    std::cout << "Alien Ok 4" << std::endl;
                }
                if(acaoAtual.type == Action::ActionType::SHOOT) {
                    //Ainda a implementar
                    taskQueue.pop();
                }
            }
        }
        //std::cout << "Alien no fim  do update" << std::endl;
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