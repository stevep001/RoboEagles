#ifndef PANTILTUPCOMMAND_H
#define PANTILTUPCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class PanTiltUpCommand: public CommandBase {
public:
	PanTiltUpCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
