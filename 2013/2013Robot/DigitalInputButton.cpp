#include "WPILib.h"
#include "DigitalInputButton.h"

DigitalInputButton::DigitalInputButton(DigitalInput *input, bool invert)
{
	this->input = input;
	this->invert = invert;
}

bool DigitalInputButton::Get()
{
	if (invert)
	{
		return !this->input->Get();
	}
	else
	{
		return this->input->Get();
	}
}
