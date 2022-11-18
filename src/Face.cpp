#include "include/Face.h"
#include "include/Sound.h"

Face::Face(GameObject& associated) : Component(associated) {
    this->hitpoints = 30;
}

Face::~Face() {

}

void Face::Damage(int damage) {

    this->hitpoints -= damage;
    if (this->hitpoints > 0)
    {
		Sound *somDeMorte = (Sound *)associated.GetComponent("Sound");
        this->associated.RequestDelete();
        somDeMorte->Play(1);
        return;
    }

    Component *GOsom = this->associated.GetComponent("Sound");
    //Sound *s = new Sound(GOsom);
    if (GOsom != nullptr)
    {
        //GOsom->associated.GetComponent("Sound").Play();
    }
}

void Face::Update(float dt){

    InputManager &input = InputManager::GetInstance();

    if (input.MousePress(LEFT_MOUSE_BUTTON)) {

        if (associated.box.Contains({(float)input.GetMouseX(), (float)input.GetMouseY()})) {
            Damage(std::rand() % 10 + 10);
        }
    }
}

void Face::Render() {

}

bool Face::Is(std::string type) {

    if(type == "Face") {
        return true;
    }
    else {
        return false;
    }
}
