#ifndef BOMBERMAN_SINGLELEVELSCENE_H
#define BOMBERMAN_SINGLELEVELSCENE_H

#include "LevelScene.hpp"

/**
 * Level scene for single player
 */
class SingleLevelScene : public LevelScene {
private:
  void onRender(Uint32 delta) override;

  std::string getFileName(int levelNumber) override;
  void onPlayerDie(PlayerScript::ControlsType controlsType) override;

  void openResultMenu(SingleAfterMenu::State state);

public:
  using LevelScene::LevelScene;
};

#endif // BOMBERMAN_SINGLELEVELSCENE_H
