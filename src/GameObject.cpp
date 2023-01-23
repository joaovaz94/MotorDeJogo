#include "include/GameObject.h"

GameObject::GameObject () {
    this->isDead = false;
    this->started = false;
    angleDeg = 0;
}

GameObject::~GameObject() {
    int cont = this->components.size();

    for(int i=cont -1; i >= 0; i--) {
        components.erase(components.begin() + i);
    }
}

void GameObject::Start() {

    for(int i=0; i < (int)components.size(); i++) {
        components[i]->Start();
    }
    started = true;
}

void GameObject::Update(float dt){

    for(int i=0; i < (int)this->components.size(); i++ ) {
        components[i]->Update(dt);
    }
}

void GameObject::Render() {

    for(int i=0; i < (int)this->components.size(); i++ ) {
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
    this->components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    for(int i=0; i< (int)this->components.size(); i++){
        if(components[i].get() == cpt) {
            components.erase(components.begin() + i);
        }
    }
}

Component* GameObject::GetComponent(std::string type) {

    for(int i=0; i < (int)this->components.size(); i++ ) {
        if(components[i]->Is(type)){
            return components[i].get();
        }
    }

    return nullptr;
}

void GameObject::NotifyCollision(GameObject &other) {
    for(int i=0; i < components.size();i++) {
        components[i].get()->NotifyCollision(other);
    }
}