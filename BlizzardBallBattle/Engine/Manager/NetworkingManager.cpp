#include "NetworkingManager.h"
#include "MessageManager.h"

NetworkingManager* NetworkingManager::instance;

NetworkingManager* NetworkingManager::GetInstance() {
    if (instance == NULL)
        instance = new NetworkingManager();
    return instance;
}

NetworkingManager::NetworkingManager() {
    SDLNet_Init();
    messageQueue = new ThreadQueue<std::string>();
}

bool NetworkingManager::CreateHost() {
    return Host();
}

bool NetworkingManager::CreateClient() {
    return Join();
}

bool NetworkingManager::IsConnected() {
    return socket != NULL;
}

bool NetworkingManager::IsHost() {
    return client != NULL;
}

bool NetworkingManager::Host() {
    // create a listening TCP socket on port 9999 (server)
    IPaddress ip;

    int startConnTime = SDL_GetTicks();
    int timeoutTime = SDL_GetTicks();
    const int TIMEOUT = 60000;

    if(SDLNet_ResolveHost(&ip,NULL,port)==-1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        return false;
    }

    socket=SDLNet_TCP_Open(&ip);
    if(!socket) {
      //  printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		std::string error = SDLNet_GetError();
        return false;
    }
    bool result = false;
    while(!(result = Accept()) && SDL_GetTicks() - startConnTime < TIMEOUT);
    if  (result) {
        std::cout << "Connection established." << std::endl;
        PollMessages();
        return true;
    } else {
        std::cout << "No peer found, destroying server." << std::endl;
        Close();
        return false;
    }
}

bool NetworkingManager::Join() {
    IPaddress ip;
    
    if(SDLNet_ResolveHost(&ip,IP,port)==-1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        return false;
    }
    
    socket=SDLNet_TCP_Open(&ip);
    if(!socket) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        Close();
        return false;
    }
    std::cout << "SDLNet_TCP_Open:A>A>A WE DID IT JOIN" << std::endl;
    PollMessages();
    return true;
}

bool NetworkingManager::Accept() {
    client=SDLNet_TCP_Accept(socket);
    if(!client) {
        return false;
    }
    // communicate over new_tcpsock
    std::cout << "SDLNet_TCP_Accept:A>A>A WE DID IT ACCETP" << std::endl;
    return true;
}

bool NetworkingManager::Close() {
    if (client != NULL) {
        SDLNet_TCP_Close(client);
        client = NULL;
    }
    if (socket != NULL) {
        SDLNet_TCP_Close(socket);
        socket = NULL;
    }
    return true;
}

//Host->Sending Messages->Client Exits->Host Crashes on line SDLNet_TCP_Send
void NetworkingManager::Send(std::string *msg) {
    // send a hello over sock
    //TCPsocket sock;
    int result,len;
    len = msg->length() + 1;

    if (client != NULL)
        result=SDLNet_TCP_Send(client, msg->c_str(), len);
    else if (socket != NULL)
        result=SDLNet_TCP_Send(socket, msg->c_str(), len);

    if(result<len) {
        //printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
    }
}

void NetworkingManager::PollMessages() {
    messagesToSend.clear();
    receiverThread = std::thread(&NetworkingManager::PollMessagesThread, this);
    receiverThread.detach();
}

void NetworkingManager::PollMessagesThread() {
    #define MAXLEN 1024
    int result;
    char msg[MAXLEN];

    while(socket != NULL) { //replace with on connection lost

    if (client != NULL)
        result=SDLNet_TCP_Recv(client, msg, MAXLEN);
    else if (socket != NULL)
        result=SDLNet_TCP_Recv(socket, msg, MAXLEN);
    if(result<=0) {
        Close();
        continue;
    }
    std::string newMsg = msg;
    messageQueue->Push(newMsg);
    }
    Close();
}

bool NetworkingManager::GetMessage(std::string &msg) {
    if (!messageQueue->IsEmpty()) {
        messageQueue->Pop(msg);
        return true;
    }
    return false;
}

void NetworkingManager::PrepareMessageForSending(std::string key, std::map<std::string, std::string> data) {
    Message message;
    message.key = key;
    message.data = data;
    messagesToSend.push_back(message);
}

//TODO: Do over time
void NetworkingManager::SendQueuedEvents() {
    std::string packet = "[";
    for(size_t i = 0; i < messagesToSend.size(); i++) {
        packet += SerializeMessage(messagesToSend[i]);
        packet += ",";
    }
    packet.pop_back();
    packet += "]";
    //Submit it
    messagesToSend.clear();

    //std::cout << "SENDING PACKET: " << packet << std::endl;
    Send(new std::string(packet));
}

void NetworkingManager::SendEventToReceiver(std::map<std::string, void*> data) {
    std::string* key = (std::string*)data["key"];
    std::string value = *key;
    MessageManager::SendEvent(value, data );
}

std::string NetworkingManager::SerializeMessage(Message message) {
    std::string result = "{";
    message.data["key"] = message.key.c_str();

    for (const auto tuple : message.data) {
        result += tuple.first + ":" + message.data[tuple.first] + ",";
    }
    result.pop_back();
    result += "}";
    return result;
}


void NetworkingManager::HandleParsingEvents(std::string packet) {
    std::vector<std::string> messages;
	if (packet.size() > 2) {
		packet.erase(0, 1);
		packet.pop_back();
		std::string currentMessage;
		bool reading = false;
		while (packet.size() > 0) {
			if (!reading) {
				if (packet[0] == '{') {
					reading = true;
					currentMessage += packet[0];
				}
			}
			else {
				currentMessage += packet[0];
				if (packet[0] == '}') {
					reading = false;
					messages.push_back(currentMessage);
					SendEventToReceiver(DeserializeMessage(currentMessage));
					currentMessage = "";
				}
			}

			packet.erase(0, 1);
		}
	}
}



//TODO: Deserialize this:
//Example: {key : Player|UPDATE,rotation : 37.000000,scale : 1.000000,x : 1.000000,y : 0.000000}

std::map<std::string, void*> NetworkingManager::DeserializeMessage(std::string message) {
    std::map<std::string, void*> data;
    std::string currentKey = "";
    std::string currentValue = "";
    bool readingKey;
    bool readingValue;
    while(message.size() > 0) {
        char curChar = message[0];
        message.erase(0, 1);
        
        if (curChar == ',' || curChar == '{') {
            //Start reading key
            readingKey = true;
            readingValue = false;
            if (curChar == ',') {
                data[currentKey] = (void*)new std::string(currentValue);
            }
            std::string newCurrentString = "";
            std::string newCurrentValue = "";
            currentKey = newCurrentString;
            currentValue = newCurrentValue;
            continue;
        } else if (curChar == ':') {
            //Start reading value
            readingValue = true;
            readingKey = false;
            continue;
        } else if (curChar == '}') {
            //End
            data[currentKey] = (void*)new std::string(currentValue);
            break;
        }
        if (!isspace(curChar)) {
            if (readingKey) {
                currentKey += curChar;
            } else if (readingValue) {
                currentValue += curChar;
            }
        }

    }
    return data;
}

void NetworkingManager::SetIP(char *ip, int p) {
    IP = ip;
    port = p;
}