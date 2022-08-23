#include "ScriptProcessor.hpp"

#include "../components/ScriptC.hpp"

// region public methods
void ScriptProcessor::observeScriptComponentConstruct(
  entt::registry &registry) {
  registry.on_construct<ScriptC>()
    .connect<ScriptProcessor::onScriptComponentConstruct>();
}
void ScriptProcessor::propagateEvent(entt::registry &registry,
                                     const SDL_Event &event) {
  auto view = registry.view<ScriptC>();
  for (auto entity : view) {
    std::shared_ptr<Script> script = registry.get<ScriptC>(entity).getScript();
    script->onEvent(event);
  }
}
void ScriptProcessor::update(entt::registry &registry) {
  auto view = registry.view<ScriptC>();
  for (auto entity : view) {
    std::shared_ptr<Script> script = registry.get<ScriptC>(entity).getScript();
    script->onUpdate();
  }
}
// endregion

// region private methods
void ScriptProcessor::onScriptComponentConstruct(entt::registry &registry,
                                                 entt::entity entity) {
  std::shared_ptr<Script> script = registry.get<ScriptC>(entity).getScript();
  script->registry = &registry;
  script->entity = std::make_shared<Entity>(&registry, entity);
  script->onConstruct();
}
// endregion