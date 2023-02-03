#include "include/State.h"

State::State()
{

    popRequested = false;
    quitRequested = false;
    started = false;
}

State::~State()
{
    objectArray.clear();
}

std::weak_ptr< GameObject > State::AddObject(GameObject* object) {

	std::shared_ptr< GameObject > ponteirpCompartilhado(object);
	objectArray.push_back(ponteirpCompartilhado);

	if(started) {
		ponteirpCompartilhado->Start();
	}
	std::weak_ptr < GameObject > ptrRetorno(ponteirpCompartilhado);
	return ptrRetorno;
}

std::weak_ptr< GameObject > State::GetObjectPtr(GameObject* object) {

	for(int i=0; i < (int)objectArray.size(); i++) {
		if( objectArray[i].get() == object){
			std::weak_ptr <GameObject> ptrRetorno(objectArray[i]);
			return ptrRetorno;
		}
	}
	std::weak_ptr <GameObject> ptrNulo;
	return ptrNulo;
} 

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::StartArray() {
    for(unsigned i=0; i < objectArray.size(); i++){
        objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt) {
    for(unsigned i=0; i < objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray() {
    for(unsigned i=0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}