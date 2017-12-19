#include "MessageManager.h"

MessageManager* MessageManager::instance;

MessageManager* MessageManager::GetInstance() {
    if (instance == NULL)
        instance = new MessageManager();
    return instance;
}

int MessageManager::Subscribe(std::string event, Callback callback, void* owner) {
    MessageManager* self = MessageManager::GetInstance();
    CallbackReceiver callbackReceiver;
    callbackReceiver.callback = callback;
    callbackReceiver.owner = owner;

    int id = rand();

    std::map<std::string, std::map<int, CallbackReceiver> >::iterator it = self->subs.find(event);
    if (it != self->subs.end())
        it->second[id] = callbackReceiver;
    else {
        std::map<int, CallbackReceiver> eventList;
        eventList[id] = callbackReceiver;
        self->subs[event] = eventList;
    }
    return id;
}

void MessageManager::UnSubscribe(std::string event, int id) {
    MessageManager* self = MessageManager::GetInstance();

    std::map<std::string, std::map<int, CallbackReceiver> >::iterator it = self->subs.find(event);
    if (it != self->subs.end())
        it->second.erase(id);
}

void MessageManager::SendEvent(std::string event, std::map<std::string, void*> data) {
    MessageManager* self = MessageManager::GetInstance();

    std::map<std::string, std::map<int, CallbackReceiver> >::iterator it = self->subs.find(event);
    if (it != self->subs.end())
        for (std::map<int, CallbackReceiver>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2) {
            data["this"] = (void*)it2->second.owner;
            it2->second.callback(data);
        }
    //TODO: Clear all void* data that isn't "this"
}