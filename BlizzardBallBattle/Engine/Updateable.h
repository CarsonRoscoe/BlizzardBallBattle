#pragma once

/*
Base class for all objects that want to have update methods and follow an 
OnStart()
OnUpdate()
OnEnd() 
pattern.
*/
class Updateable {
public:
    virtual void OnStart() = 0;
    virtual void OnUpdate(int ticks) = 0;
    virtual void OnEnd() = 0;
};