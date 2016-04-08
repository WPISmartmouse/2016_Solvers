#pragma once

#include "CommanDuino.h"
#include "RealMouse.h"

class SetTuningParameter : public Command {
  public:
    SetTuningParameter(float dP);
    void initialize();
    void execute();
    bool isFinished();
    void end();

  private:
    float param;
    float dP;
    bool readyToExit;
    RealMouse *mouse;
};
