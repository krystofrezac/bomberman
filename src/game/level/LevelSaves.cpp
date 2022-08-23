#include "LevelSaves.hpp"

#include <cassert>
#include <fstream>
#include <stdexcept>

const std::string LevelSaves::LEVEL_FOLDER = "src/game/level/levels/";
const std::string LevelSaves::SAVE_FILE = "examples/singlePlayerSave";

int LevelSaves::getSavedLevel() {
  std::string levelFilename = "0";

  std::ifstream levelFile(SAVE_FILE);
  if (levelFile) {
    if (!(levelFile >> levelFilename)) {
      throw std::invalid_argument("Save file has invalid format!");
    }
  }
  levelFile.close();

  return std::stoi(levelFilename);
}
void LevelSaves::saveLevel(int levelNumber) {
  std::ofstream writeLevelFile(SAVE_FILE, std::ios::trunc);
  if (!(writeLevelFile << levelNumber)) {
    throw std::invalid_argument("Could not write to save file!");
  }

  writeLevelFile.close();
}
bool LevelSaves::levelExist(int levelNumber) {
  std::ifstream levelFile(LEVEL_FOLDER + std::to_string(levelNumber) + ".lvl");
  if (!levelFile)
    return false;
  return true;
}

void LevelSaves::runTests() {
  assert(levelExist(0));
  assert(!levelExist(1000));

  int originalSave = getSavedLevel();

  saveLevel(0);
  assert(getSavedLevel() == 0);
  saveLevel(5);
  assert(getSavedLevel() == 5);

  saveLevel(originalSave);
}