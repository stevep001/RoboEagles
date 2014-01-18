#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *stick;
	Button *throwerOpenButon;
	Button *throwerCloseButton;
public:
	OI();
};

#endif
