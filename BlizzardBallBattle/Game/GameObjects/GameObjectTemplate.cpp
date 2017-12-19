#include "GameObjectTemplate.h"

/*
Constructor called when the GameObject is created. Any GameObject specific creation code can go here.
This includes adding relevant components or any setup.

By default, GameObject's base class has a Transform component
*/
GameObjectTemplate::GameObjectTemplate() : GameObject(false) {
    //Adding a base component. You create the new Component, pass it 'this', cast to a Component* then add it
    AddComponent<ComponentTemplate*>(new ComponentTemplate(this));

    dataToDestroyForExample = new ExampleClass();
}

//Destructor called when the GameObject is being destroyed. Do any special cleanup code here.
//HINT: If you ever type "new", you should probably delete it.
//The only exception is we can assume components will be deleted by the GameObject base class
GameObjectTemplate::~GameObjectTemplate() {
    //delete(dataToDestroyForExample);
}

//An example method showing how you can create your own methods that ca do anything
void GameObjectTemplate::ExampleMethod() {
    std::cout << "GameObjectTemplate's ExampleMethod was called" << std::endl;

    //For our example, we will grab the ComponentTemplate component and call it's ExampleMethod
    ComponentTemplate* component = GetComponent<ComponentTemplate*>();
    component->ExampleMethod();
}