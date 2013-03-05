#ifndef DRIVEWITHJOYSTICKCOMMAND_H
#define DRIVEWITHJOYSTICKCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class DriveWithJoystickCommand: public CommandBase {
public:
	DriveWithJoystickCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
