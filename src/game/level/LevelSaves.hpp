#ifndef BOMBERMAN_LEVELSAVES_H
#define BOMBERMAN_LEVELSAVES_H

#include <string>

/**
 * Class for manipulating with save and level files
 */
class LevelSaves {
public:
  // https://stackoverflow.com/questions/1563897/static-constant-string-class-member
  /**
   * Folder where levels are located
   */
  static const std::string LEVEL_FOLDER;
  /**
   * Folder where save files are located
   */
  static const std::string SAVE_FILE;

  /**
   * @return Number of level in save file
   */
  static int getSavedLevel();
  /**
   * Save level to save file
   * @param levelNumber number of level
   */
  static void saveLevel(int levelNumber);
  /**
   * @param levelNumber number of level to check
   * @return True if exists else false
   */
  static bool levelExist(int levelNumber);

  /**
   * Run tests
   */
  static void runTests();
};

#endif // BOMBERMAN_LEVELSAVES_H
