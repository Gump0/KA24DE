//////////////////////////////////////////////////////////////////////////////////////////////////////
// base-class for components, this detirmines each components individual behaviors and required data
// when being "hooked-up" to entity objects
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "component.h"

void Component::Update() { }

void Component::ComponentDebug(int objectId)
{
    std::string id = std::to_string(objectId);
    std::cout << id << " I am a component, but idk which one I am (inherited component overrides this method?)\n";
}

Component::Component() { }

Component::~Component() { }
