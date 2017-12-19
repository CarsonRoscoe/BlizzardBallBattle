#include "Sender.h"
#include "NetworkingManager.h"

Sender::Sender(GameObject* gameObject, std::string ID) : Component(gameObject) {
    this->ID = ID;
}

void Sender::SendUpdate() {
    std::map<std::string, std::string> payload;
    Transform* transform = gameObject->GetTransform();
    payload["x"] = std::to_string(transform->getX());
    payload["y"] = std::to_string(transform->getY());
    payload["z"] = std::to_string(transform->getZ());
    payload["rotation"] = std::to_string(transform->getRotation());
    payload["scale"] = std::to_string(transform->getScale());
	SendNetworkMessage("UPDATE", payload);
}

void Sender::SendNetworkMessage(std::string messageKey,  std::map<std::string, std::string> payload) {
    std::remove_if(messageKey.begin(), messageKey.end(), isspace);
    NetworkingManager::GetInstance()->PrepareMessageForSending(this->ID + "|" + messageKey, payload);
}

void Sender::OnUpdate(int ticks) {
    SendUpdate();
}