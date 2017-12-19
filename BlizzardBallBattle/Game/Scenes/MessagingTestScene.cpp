#include "MessagingTestScene.h"
#include "MessageManager.h"
#include <iostream>

void MessagingTestScene::OnStart() {
	//subscribe a function to the event "test", store the unique id for this event for later removal.
	int id = MessageManager::Subscribe("test", [](std::map<std::string, void*> data) -> void {
	
	  //converting a void* to its respective std::string*. Do it this way if its not a primitive type.
	  std::string *str = static_cast<std::string *>(data["somedata"]);
	
	  //converting a void* to its respective int*, do it this way if its primitive data type.
	  int *in = (int *)(&data["someint"]);
	
	  //printing out the data we got from the data.
	  std::cout << *in << " " << *str << std::endl;
	}, (void*)0);
	
	//create data map to pass into the callback, notice how the data is pointers.
	std::map<std::string, void*> data;
	std::string* s = new std::string("AMAZING");
	data["somedata"] = s;
	data["someint"] = (int *)44;
	
	//send the event.
	MessageManager::SendEvent("test", data);
	
	//unsubscribe the listener from the event.
	MessageManager::UnSubscribe("test", id);
	
	//send the event again. No listeners for this event so nothing happens.
	MessageManager::SendEvent("test", data);
}

void MessagingTestScene::OnEnd() {
}

void MessagingTestScene::OnUpdate(int ticks) {
}