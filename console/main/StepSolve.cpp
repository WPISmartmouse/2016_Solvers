#ifdef CONSOLE

#include <fstream>
#include <iostream>

#include "CommanDuino.h"
#include "StepSolveCommand.h"
#include "ConsoleMaze.h"
#include "ConsoleMouse.h"
#include "ConsoleTimer.h"
#include "Mouse.h"
#include "Flood.h"
#include "WallFollow.h"

int main(int argc, char* argv[]){

  std::string maze_file;
  if (argc < 2) {
    maze_file = "../mazes/16x16.mz";
  }
  else {
    maze_file = std::string(argv[1]);
  }

  std::fstream fs;
  fs.open(maze_file, std::fstream::in);

  if (fs.good()){
    ConsoleMaze maze(fs);
    ConsoleMouse::inst()->seedMaze(&maze);
    ConsoleTimer timer;
    Command::setTimerImplementation(&timer);
    Scheduler scheduler(new StepSolveCommand(new Flood(ConsoleMouse::inst())));

    while (true) {
      scheduler.run();
    }

    fs.close();
    return EXIT_SUCCESS;
  }
  else {
		printf("error opening maze file!\n");
    fs.close();
    return EXIT_FAILURE;
  }
}
#endif
