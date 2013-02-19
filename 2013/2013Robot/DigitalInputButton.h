#ifndef DIGITALINPUTBUTTON_H
#define DIGITALINPUTBUTTON_H

#include "WPILib.h"

class DigitalInputButton : public Button
{
public:
	DigitalInputButton(DigitalInput *input, bool invert);
	virtual ~DigitalInputButton() {}

	virtual bool Get();
private:
	DigitalInput *input;
	bool invert;
};

#endif
