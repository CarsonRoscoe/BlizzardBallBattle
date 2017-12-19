#include "Receiver.h"


Receiver::Receiver(GameObject* gameObject, std::string netID) : Component(gameObject) {
    this->netID = netID;
    //Add to map of type "event", key "id"
    std::cout << "RECEIVER SUBSCRIBBED" << std::endl;

    Subscribe("UPDATE",  [](std::map<std::string, void*> data) -> void {
        float x = std::stof(*(std::string*)data["x"]);
        float y = std::stof(*(std::string*)data["y"]);
        float z = std::stof(*(std::string*)data["z"]);
        float angle = std::stof(*(std::string*)data["rotation"]);
        float scale = std::stof(*(std::string*)data["scale"]);
        Receiver* self = (Receiver*)data["this"];
        Transform* transform = self->gameObject->GetTransform();
        transform->setPosition(x, y, z );
        transform->setRotation(angle);
        transform->setScale(scale);
    }, this);
}

Receiver::~Receiver() {
    //Unsubscribe
}

void Receiver::Subscribe(std::string event, Callback callback, void* owner) {
    MessageManager::Subscribe(netID + "|" + event, callback, owner);
}