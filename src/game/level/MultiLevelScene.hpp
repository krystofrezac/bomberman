#ifndef BOMBERMAN_MULTILEVELSCENE_H
#define BOMBERMAN_MULTILEVELSCENE_H

#include "LevelScene.hpp"

/**
 * Level scene for multi player
 *
 */
class MultiLevelScene : public LevelScene {
private:
  std::string getFileName(int levelNumber) override;
  void onPlayerDie(PlayerScript::ControlsType controlsType) override;

public:
  using LevelScene::LevelScene;
};

#endif // BOMBERMAN_MULTILEVELSCENE_H
