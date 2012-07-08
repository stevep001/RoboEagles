#ifndef FILLCANNONCOMMAND_H
#define FILLCANNONCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class FillCannonCommand: public CommandBase {
public:
	FillCannonCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
