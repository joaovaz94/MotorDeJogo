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
        return;
    }
    this->associated.RequestDelete();

    Component *GOsom = this->associated.GetComponent("Sound");
    //Sound *s = new Sound(GOsom);
    if (GOsom != nullptr)
    {
        //GOsom->associated.GetComponent("Sound").Play();
    }
}

void Face::Update(float dt){

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
