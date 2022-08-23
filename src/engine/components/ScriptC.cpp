#include "ScriptC.hpp"

// region ScriptC
ScriptC::ScriptC(const std::shared_ptr<Script> script) : script(script) {}

std::shared_ptr<Script> ScriptC::getScript() const { return script; }
// endregion

// region Script

// entity is replaced in ScriptProcessor.
Script::Script() {}

void Script::onConstruct() {}
void Script::onUpdate() {}
void Script::onEvent(const SDL_Event &event) {}
void Script::onTimer() {}
void Script::onCollision(const std::string &myColliderName,
                         const std::string &collidedWithName,
                         Entity collidedWith) {}

Entity Script::createEntity() { return Entity(registry); }
// endregion