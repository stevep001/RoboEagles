#ifndef FLAPV2COMMAND_H
#define FLAPV2COMMAND_H

#include "../CommandBase.h"


/**
 *
 *
 * @author speterson
 */
class FlapV2Command: public CommandBase {
private:
	bool moveDown;
	bool toggle;
public:
	FlapV2Command(bool down);
	FlapV2Command();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
