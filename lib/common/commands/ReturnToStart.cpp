#include "ReturnToStart.h"
#include "Forward.h"
#include "Turn.h"

#ifdef EMBED
#include <Arduino.h>
#endif

ReturnToStart::ReturnToStart(Mouse *mouse) : CommandGroup("return"), mouse(mouse) {
  pathToStart = (char *)malloc(sizeof(char) * AbstractMaze::PATH_SIZE);
}

void ReturnToStart::initialize(){
  //plan path from center to origin
  mouse->maze->flood_fill_from_point(pathToStart, AbstractMaze::MAZE_SIZE/2, AbstractMaze::MAZE_SIZE/2, 0,0);
  index = 0;
}

bool ReturnToStart::isFinished(){
  bool groupFinished = CommandGroup::isFinished();

  if (groupFinished) {
    bool returned = mouse->getRow() == 0 && mouse->getCol() == 0;

    if (!returned){
      char nextDirection = pathToStart[index++];
      addSequential(new Turn(char_to_dir(nextDirection)));
      addSequential(new Forward());
    }
    else {
      return true;
    }

    return false;
  }

  return false;
}
