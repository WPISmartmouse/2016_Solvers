#include "WallFollow.h"
#include <string.h>
#include <stdio.h>
#ifndef EMBED
  #include <iostream>
#endif

WallFollow::WallFollow(Mouse *mouse): Solver(mouse) {}

void WallFollow::setup() {
  mouse->reset();
  mouse->maze->reset();
  mouse->maze->mark_origin_known();
	step=0;
}

char *WallFollow::solve(){
	//run till you find the goal
	while (!isFinished()){
    mouse->internalTurnToFace(planNextStep());
    mouse->internalForward();
	}
  teardown();
  return mouse->maze->fastest_route;
}

bool WallFollow::isFinished(){
  return mouse->atCenter();
}

void WallFollow::teardown() {
	mouse->maze->fastest_route[step]=0;
}

Direction WallFollow::planNextStep(){
  Direction dir = left_of_dir(mouse->getDir());
  Direction nextDir;

  if (!mouse->is_mouse_blocked(dir)){
    //if you can turn left you must
    nextDir = dir;
  }
  else if (mouse->is_mouse_blocked(mouse->getDir())) {
    if (!mouse->is_mouse_blocked(opposite_direction(dir))){
      //if you can't go left or forward try right
      nextDir = opposite_direction(dir);
    }
    else {
      //you must do a 180
      nextDir = opposite_direction(mouse->getDir());
    }
  }
  else {
    nextDir = mouse->getDir();
  }

  mouse->maze->fastest_route[step++] = dir_to_char(nextDir);
  mouse->mark_mouse_position_visited();

  return nextDir;
}
