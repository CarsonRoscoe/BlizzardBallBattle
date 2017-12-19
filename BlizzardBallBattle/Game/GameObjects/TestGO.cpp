#include "TestGO.h"
#include "Collider.h"

TestGo::TestGo() : GameObject(false) {
    AddComponent(new Collider(this, 4));
}

TestGo::~TestGo() {

}