#include "SingleLevelScene.hpp"

#include "LevelSaves.hpp"

void SingleLevelScene::onRender(Uint32 delta) {
  if (numberOfEnemies != 0)
    return;

  openResultMenu(SingleAfterMenu::State::WON);
}

std::string SingleLevelScene::getFileName(int levelNumber) {
  return LevelSaves::LEVEL_FOLDER + std::to_string(levelNumber) + ".lvl";
}
void SingleLevelScene::onPlayerDie(PlayerScript::ControlsType controlsType) {
  openResultMenu(SingleAfterMenu::State::LOST);
}

void SingleLevelScene::openResultMenu(SingleAfterMenu::State state) {
  std::shared_ptr<SingleAfterMenu> singleAfterMenu =
    std::make_shared<SingleAfterMenu>(
      getWindow(), getRenderer(), getSceneManager(), state);
  getSceneManager().setScene(singleAfterMenu);
}
