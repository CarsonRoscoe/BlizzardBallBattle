#pragma once
#include "GLHeaders.h"
#include <iostream>
#include "ThreadQueue.h"
#include <thread>
#include <map>
#include <string>


struct Message {
    std::string key;
    std::map<std::string, std::string> data;
};

class NetworkingManager {
private:
    static NetworkingManager* instance;
    ThreadQueue<std::string> *messageQueue;
    std::thread receiverThread;
    std::vector<Message> messagesToSend;
    char *IP = "192.168.0.124";
    int port = 9999;

    TCPsocket socket = NULL;
    TCPsocket client = NULL;
    bool Accept();
    bool Host();
    bool Join();
    bool Close();
    void PollMessages();
    void PollMessagesThread();
    std::string SerializeMessage(Message message);
    std::map<std::string, void*> DeserializeMessage(std::string message);
    void SendEventToReceiver(std::map<std::string, void*> data);

public:
    NetworkingManager();
    static NetworkingManager* GetInstance();
    bool CreateHost();
    bool CreateClient();
    void Send(std::string *msg);
    bool GetMessage(std::string &msg);
    void PrepareMessageForSending(std::string key, std::map<std::string, std::string> data);
    void SendQueuedEvents();
    void HandleParsingEvents(std::string packet);
    bool IsConnected();
    bool IsHost();
    void SetIP(char *ip, int port = 5050);
};