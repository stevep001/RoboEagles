#ifndef CAMERACONTROLCOMMAND_H
#define CAMERACONTROLCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class CameraControlCommand: public CommandBase {
public:
	CameraControlCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
