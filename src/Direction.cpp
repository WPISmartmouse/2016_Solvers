#include "Direction.h"

Direction left_of_dir(Direction dir) {
  switch(dir){
    case Direction::N:
      return Direction::W;
    case Direction::E:
      return Direction::N;
    case Direction::S:
      return Direction::E;
    case Direction::W:
      return Direction::S;
    default:
      return Direction::INVALID;
  }
}

Direction operator++(Direction& dir, int) {
  switch(dir){
    case Direction::N:
      dir = Direction::E;
      break;
    case Direction::E:
      dir = Direction::S;
      break;
    case Direction::S:
      dir = Direction::W;
      break;
    case Direction::W:
      dir = Direction::Last;
      break;
    default:
      dir = Direction::INVALID;
  }
  return dir;
}

Direction opposite_direction(Direction d){
  switch(d){
    case Direction::N:
      return Direction::S;
    case Direction::E:
      return Direction::W;
    case Direction::S:
      return Direction::N;
    case Direction::W:
      return Direction::E;
    default:
      return Direction::INVALID;
  }
}

char dir_to_char(Direction dir){
  switch(dir){
    case Direction::N: return 'N';
    case Direction::S: return 'S';
    case Direction::E: return 'E';
    case Direction::W: return 'W';
    default: return '\0';
  }
}
