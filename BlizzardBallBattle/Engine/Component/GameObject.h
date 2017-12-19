#pragma once

#include "Component.h"
#include <string>
#include <typeinfo>
#include <vector>
#include <map>
#include "Updateable.h"
#include "Transform.h"
#include <iostream>

class GameObject : public Updateable {
private:
   std::map<std::string, std::vector<Component*>> components;
   int id;
   bool isGlobal;
   Transform* transform;
   
   template <typename T>
   std::string GetClassName() {
       return typeid(T).name();
   }

public:

   GameObject(bool isGlobal);

   int getId() {
       return id;
   }

   template <typename T> 
   T GetComponent() {
	   if (HasComponent<T>()) {
		   return (T)components[GetClassName<T>()].front();
	   }
	   else {
           std::cout << "ERROR::FAILED TO FIND COMPONENT " << GetClassName<T>() << "  FOR OBJECT " << id << std::endl;
		   return NULL;
	   }
   }
   
   template <typename T> 
   std::vector<T> GetComponents() {
       return (T)components[GetClassName<T>()];
   }
   
   template <typename T> 
   void AddComponent(T component) {
       std::string id = GetClassName<T>();
       if (!HasComponent<T>()) {
           std::vector<Component*> typeList;
           typeList.push_back((Component*)component);
           components.insert(std::pair<std::string, std::vector<Component*>>(id, typeList));
       } else {
           components[id].push_back(component);
       }
   }
   
   template <typename T> 
   void RemoveComponents() {
        std::vector<Component*> componentList = components[GetClassName<T>()];
        for (size_t i = componentList.size() - 1; i >= 0; i--){
            delete componentList[i];
        }

        components[GetClassName<T>()].clear();
    }
    
   void RemoveAllComponents() {
    for (std::map<std::string, std::vector<Component*>>::iterator it=components.begin(); it!=components.end(); ++it) {
        for (size_t i = 0; i < it->second.size(); i++){
			//it->second[i]->~Component();
            delete it->second[i];
        }
        it->second.clear();
    }
	components.clear();
   }
   
   template <typename T> 
   bool HasComponent() {
       return components.find(GetClassName<T>()) != components.end();
   }

   void OnStart() {};
   void OnComponentsUpdate(int ticks);
   void OnUpdate(int ticks){};
   void OnEnd() {};
   Transform* GetTransform();

   void Destroy(GameObject* gameObject);
   
   virtual ~GameObject();

   //template <class T>
   //vector<Component*> GetComponentsByType();
};