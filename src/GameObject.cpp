#include "include/GameObject.h"

GameObject::GameObject () {
    this->isDead = false;
}

GameObject::~GameObject() {
    int cont = this->components.size();

    for(int i=cont -1; i >= 0; i--) {
        components.erase(components.begin() + i);
    }
}

void GameObject::Update(float dt){

    for(int i=0; i < this->components.size(); i++ ) {
        components[i]->Update();
    }
}

void GameObject::Render() {

    for(int i=0; i < this->components.size(); i++ ) {
        components[i]->Render();
    }
}

bool GameObject::IsDead() {
    return this->isDead;
}

void GameObject::RequestDelete() {
    this->isDead = true;
}

void GameObject::AddComponent(Component* cpt){
    this->components.push_back(cpt);
}

Component* GameObject::GetComponent(std::string type) {

    for(int i=0; i < this->components.size(); i++ ) {
        if(components[i]->Is(type)){
            return components[i];
        }
    }

    return nullptr;
}