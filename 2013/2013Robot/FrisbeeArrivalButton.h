#ifndef FrisbeeArrivalButton_H
#define FrisbeeArrivalButton_H

#include "WPILib.h"

class FrisbeeArrivalButton : public Button
{
public:
	FrisbeeArrivalButton();
	virtual ~FrisbeeArrivalButton() {}

	virtual bool Get();
};

#endif
