/** @file */

#include <SDL2/SDL.h>

#include "engine/Renderer.hpp"
#include "engine/SceneManager.hpp"
#include "engine/Window.hpp"

#include "game/MainMenu.hpp"

// https://stackoverflow.com/questions/61225576/how-to-seperate-unit-testing-from-main-program-in-c
#if TEST

#include <iostream>

#include "game/level/LevelSaves.hpp"

/** Test entrypoint
 * @param argc \c
 * @param argv \c
 * @return status code
 */
int main(int argc, char **argv) {
  std::cout << "RUNNING TESTS" << std::endl;

  LevelSaves::runTests();

  std::cout << "TESTS WHERE SUCCESSFUL" << std::endl;

  return EXIT_SUCCESS;
}

#else

/** Program entrypoint
 * @param argc \c
 * @param argv \c
 * @return status code
 */
int main(int argc, char **argv) {
  //  std::cout << argc << std::string(argv[1]) << std::endl;
  //  if (argc == 2 && std::string(argv[1]) == "test") {
  //    std::cout << "ahoj" << std::endl;
  //  }

  SDL_Init(SDL_INIT_VIDEO);
  auto window = Window("Bomberman",
                       SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED,
                       1000,
                       1000,
                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  auto renderer = Renderer(window);

  SceneManager sceneManager;

  std::shared_ptr<MainMenu> scene =
    std::make_shared<MainMenu>(window, renderer, sceneManager);

  sceneManager.setScene(scene);
  sceneManager.start();

  SDL_Quit();
  return EXIT_SUCCESS;
}

#endif
