#include "include/Face.h"
#include "include/Sound.h"

Face::Face(GameObject& associated) : Component(associated) {
    this->hitpoints = 30;
}

void Face::Damage(int damage) {

    this->hitpoints -= damage;
    if(this->hitpoints <= 0) {
        this->associated.RequestDelete();
        if(this->associated.GetComponent("Sound")) {
            Sound* som = (*Sound) this->associated.GetComponent("Sound");
    }
}

bool Face::Is(std::string type) {

    if(type == "Face") {
        return true;
    }
    else {
        return false;
    }
}
