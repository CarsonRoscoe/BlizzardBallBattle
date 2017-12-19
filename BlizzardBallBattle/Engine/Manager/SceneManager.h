#include <stack>
#include "Scene.h"

class SceneManager {
private:
    std::stack<Scene*> scenes;
    void InitializeScene();
    static SceneManager* instance;
    SceneManager();

public:
    static SceneManager* GetInstance();

    //Pushing a scene pause the top of the stack, call OnStart on the parameterized scene, and push it to the stack.
    void PushScene(Scene *scene);

    //Calling this will call OnEnd on top scene, remove it, and call OnResume for the scene underneath.
    bool PopScene();

    //Update the current scene on the stack.
    bool UpdateScene(int ticks);
    
    //Gets reference to current scene.
    Scene* GetCurrentScene();
    
    //Has at least one scene.
    bool HasScene();

};