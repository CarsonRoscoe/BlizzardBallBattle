#pragma once
#include <string>
#include <map>
#include <stdlib.h>
#include <iostream>
#include <memory>

typedef void (*Callback)(std::map<std::string, void*>);

struct CallbackReceiver {
    void* owner;
    Callback callback;
};

class MessageManager {
private:
    static MessageManager* instance;
    static MessageManager* GetInstance();
    std::map<std::string, std::map<int, CallbackReceiver> > subs;

public:
    /*
    Subscribe to an event.

    Pass in the string of the event type, and a callback which gets called.

    Returns the unique id of this subscriber, required to unsubscribe from this event later.
    */
    static int Subscribe(std::string event, Callback callback, void* owner);

    /*
    Unsubscribe from an event based on the id of the subscriber.
    */
    static void UnSubscribe(std::string event, int id);

    /*
    Sends an event to all subscribed callbacks for that event type.
    The callback is fed the data from the event caller in the form of a map containing strings as keys
    for data value, and void* as the actual data. This data must be cast to what the expected data type is.
    */
    static void SendEvent(std::string event, std::map<std::string, void*> data);
};