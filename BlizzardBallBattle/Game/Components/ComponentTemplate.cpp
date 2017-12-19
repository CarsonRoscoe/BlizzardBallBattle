#include "ComponentTemplate.h"

//The constructor that passes GameObject into the parent/Component classes constructor
ComponentTemplate::ComponentTemplate(GameObject* gameObject) : Component(gameObject)  {
    std::cout << "CompontentTemplate Constructor Invoked" << std::endl;
}

//The destructor called when this component is deleted. Do any cleanup here
ComponentTemplate::~ComponentTemplate() {
    std::cout << "ComponentTempalte Destructor Invoked. Time To Cleanup" << std::endl;
}

void ComponentTemplate::ExampleMethod() {
    std::cout << "Example Method Invoked On ComponentTemplate Class" << std::endl;
}