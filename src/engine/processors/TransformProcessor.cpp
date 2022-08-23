#include "TransformProcessor.hpp"

#include "../components/TransformC.hpp"

void TransformProcessor::process(entt::registry &registry, Uint32 delta) {
  auto transformView = registry.view<TransformC>();
  for (auto entity : transformView) {
    TransformC &transformC = registry.get<TransformC>(entity);

    transformC.updatePosition(delta);
  }
}