#include "MultiLevelScene.hpp"

#include "LevelSaves.hpp"

#include "../MultiAfterMenu.hpp"

std::string MultiLevelScene::getFileName(int levelNumber) {
  return LevelSaves::LEVEL_FOLDER + "m" + std::to_string(levelNumber) + ".lvl";
}
void MultiLevelScene::onPlayerDie(PlayerScript::ControlsType controlsType) {
  MultiAfterMenu::State state = MultiAfterMenu::PLAYER2;
  if (controlsType == PlayerScript::ARROWS)
    state = MultiAfterMenu::PLAYER1;

  std::shared_ptr<MultiAfterMenu> multiAfterMenu =
    std::make_shared<MultiAfterMenu>(
      getWindow(), getRenderer(), getSceneManager(), state);
  getSceneManager().setScene(multiAfterMenu);
}