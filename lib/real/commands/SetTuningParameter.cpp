#include "SetTuningParameter.h"

SetTuningParameter::SetTuningParameter(float dP) :  Command("SetTuningParameter"), mouse(RealMouse::inst()), param(0), dP(dP) {}

void SetTuningParameter::initialize(){
  mouse->display.setTextSize(1);
  mouse->display.setTextColor(WHITE);
  mouse->display.clearDisplay();
  mouse->display.setCursor(0,0);
  mouse->display.println("Tuning Parameter");
  mouse->display.display();
}

void SetTuningParameter::execute(){
  if (mouse->bButton.fell()){
    param += dP;
  }

  if (mouse->aButton.fell()){
    param -= dP;
  }

  mouse->display.setTextSize(1);
  mouse->display.setTextColor(WHITE);
  mouse->display.clearDisplay();
  mouse->display.setCursor(0,0);
  mouse->display.println("Tuning Parameter");
  mouse->display.setTextSize(3);
  mouse->display.println(param);
  mouse->display.display();

  mouse->setTuningParameter(param);

}

bool SetTuningParameter::isFinished(){
  return mouse->goButton.fell();
}

void SetTuningParameter::end(){

}
