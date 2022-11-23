#include "include/Alien.h"
#include "include/Sprite.h"
#include "include/InputManager.h"
#include "include/Camera.h"


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

    if(hp <= 0 ){
	    InputManager &input = InputManager::GetInstance();
        //Conferir se houve input para  o Alien
        if (input.MousePress(LEFT_MOUSE_BUTTON)) {
            //Botão Esquerdo deve atirar
            Action acaoAtirar(Action::ActionType::SHOOT, (input.GetMouseX() + Camera::pos.x), (input.GetMouseY() + Camera::pos.y));
            taskQueue.push(acaoAtirar);
        }
        if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
            //Botão Direito deve movimentar alien para posição
            Action acaoMover(Action::ActionType::MOVE, (input.GetMouseX() + Camera::pos.x), (input.GetMouseY() + Camera::pos.y));
            taskQueue.push(acaoMover);
        }

        //Checar se há alguma ação na fila
        if(taskQueue.size() > 0) {
            for(int i=0; i < (int)taskQueue.size(); i++) {
                Action acaoAtual = taskQueue.front();
                if(acaoAtual.type == Action::ActionType::MOVE) {
                    Vec2 destino = acaoAtual.pos;
                    Vec2 posAtual = associated.box.Center();

                    //Calcular se o Alien já chega à posição no próximo frame
                    Vec2 diferenca = destino - posAtual;
                    diferenca = diferenca.Normalize();
                    float velLinear = 5;
                    speed = diferenca * velLinear * dt;

                    associated.box.SetPosicaoCentro(destino.x, destino.y);

                    //senão tiver muito perto:
                    if(speed.x < 1.0) {
                    associated.box.x = destino.x; 
                    associated.box.y = destino.y; 
                    taskQueue.pop();
                    }
                }
                if(acaoAtual.type == Action::ActionType::SHOOT) {
                    //Ainda a implementar
                    taskQueue.pop();
                }
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