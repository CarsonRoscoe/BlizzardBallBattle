#pragma once

#include <string>
#include "TransformState.h"
#include "GameObject.h"
#include <vector>
#include "MessageManager.h"
#include "Transform.h"
#include <iostream>

class Receiver : public Component {
private:
    std::string netID;
    std::vector<int> messengingIDs;

public:
    void Subscribe(std::string event, Callback callback, void* owner);
    Receiver(GameObject* gameObject, std::string netID);
    ~Receiver(); //Could be death message later
    //void ReceiveUpdate(TransformState* equivalentTransform);
	void OnStart(){};
	void OnUpdate(int ticks){};
	void OnEnd(){};
};