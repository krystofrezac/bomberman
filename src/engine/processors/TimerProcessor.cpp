#include "TimerProcessor.hpp"

#include "../components/ScriptC.hpp"
#include "../components/TimerC.hpp"

void TimerProcessor::process(entt::registry &registry, Uint32 delta) {
  auto transformView = registry.view<TimerC, ScriptC>();
  for (auto &entity : transformView) {
    auto &timerC = registry.get<TimerC>(entity);

    timerC.tick(delta);
    if (!timerC.isDone())
      continue;

    std::shared_ptr<Script> script = registry.get<ScriptC>(entity).getScript();
    script->onTimer();
  }
}