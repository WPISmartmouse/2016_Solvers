#pragma once

#include "Mouse.h"
#include "SensorReading.h"

class ConsoleMouse : public Mouse {
  public:

    virtual SensorReading checkWalls() override;

    static ConsoleMouse *inst();

    void seedMaze(AbstractMaze *maze);

  private:

    static ConsoleMouse *instance;

    ConsoleMouse();
    ConsoleMouse(int starting_row, int starting_col);
};
