#include "Updateable.h"

class Game : public Updateable {   
public:
    void OnStart();
    void OnUpdate(int ticks);
    void OnEnd();
};