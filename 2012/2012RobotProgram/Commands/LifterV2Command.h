#ifndef LIFTERV2COMMAND_H
#define LIFTERV2COMMAND_H

#include "../CommandBase.h"

enum lifter_mode {UP, DOWN, STOP};
/**
 *
 *
 * @author speterson
 */
class LifterV2Command: public CommandBase {
private:
	lifter_mode desiredMode;
public:
	LifterV2Command(lifter_mode mode);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
