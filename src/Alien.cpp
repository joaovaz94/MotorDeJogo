#include "include/Alien.h"
#include "include/Sprite.h"
#include "include/InputManager.h"
#include "include/Camera.h"
#include <iostream>
#include <math.h>


 Alien::Action::Action(ActionType type, float x, float y) {
    this->type = type;
    pos = Vec2(x,y);
}

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {
    
    //Sprite *spriteAlien = new Sprite(associated, "./assets/img/alien.png");
    Sprite *spriteAlien = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(spriteAlien);

    speed = Vec2();
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

            //std::cout << "Alien mouse esquerdo" << std::endl;
        }
        if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
            //Botão Direito deve movimentar alien para posição
            Action acaoMover(Action::ActionType::MOVE, (input.GetMouseX() + Camera::pos.x), (input.GetMouseY() + Camera::pos.y));
            //Action acaoMover(Action::ActionType::MOVE, (input.GetMouseX() ), (input.GetMouseY()));
            taskQueue.push(acaoMover);
            //std::cout << "Alien mouse direito" << std::endl;
        }
        //std::cout << "Alien Ok 1" << std::endl;
        
        //Reseta a speed
        speed = Vec2();
        //Checar se há alguma ação na fila
        if(taskQueue.size() > 0) {
            Action acaoAtual = taskQueue.front();

            std::cout << "Acao tipo: "<< acaoAtual.type << std::endl;
            std::cout << "posMouse: " << acaoAtual.pos.toStr() << std::endl;
            if(acaoAtual.type == Action::ActionType::MOVE) {
                Vec2 destino = acaoAtual.pos - (Vec2(associated.box.w, associated.box.h)/2);
                Vec2 posAtual = associated.box.Posicao();
                std::cout << "destino: " << destino.toStr() << std::endl;
                std::cout << "posAtual: " << posAtual.toStr() << std::endl;

                //Calcular se o Alien já chega à posição no próximo frame
                //Vec2 diferenca = destino - posAtual;
                //diferenca = diferenca.Normalize();
                speed = (destino - posAtual).Normalize();
                //std::cout << "diferença: " << diferenca.toStr() << std::endl;
                //float velLinear = 300;
                //speed = diferenca;
                std::cout << "speed: " << speed.toStr() << std::endl;
                //std::cout << "Magnitude diferenca: " << diferenca.GetMagnitude() << std::endl;

                //acho que o problema está aqui:
                associated.box.SetPosicao(associated.box.Posicao() + (speed * dt * 300));
                //Vec2 adicao = (speed * dt * velLinear);
                //Vec2 comoVai = associated.box.Center() + adicao;
                //associated.box.SetPosicaoCentro(comoVai);

                std::cout << "Associated.box : " << associated.box.Center().toStr() << std::endl;
                std::cout << "dt : " << dt << std::endl;
                //std::cout << "Adicao : " << adicao.toStr() << std::endl;
                //std::cout << "Como vai: " << comoVai.toStr() << std::endl;

                //senão tiver muito perto:
                if((destino - posAtual).GetMagnitude() < 10.0) {
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