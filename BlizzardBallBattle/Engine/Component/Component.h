#pragma once
#include "Updateable.h"

class GameObject;

class Component : public Updateable {
public:
   Component(GameObject* gameObject);
   virtual ~Component();
   GameObject* GetGameObject();
   virtual void OnStart() = 0;
   virtual void OnUpdate(int ticks) = 0;
   virtual void OnEnd() = 0;
   void Destroy(GameObject* gameObject);
protected:
   GameObject* gameObject;
};