#ifndef LCDUPDATECOMMAND_H
#define LCDUPDATECOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class LCDUpdateCommand: public CommandBase {
public:
	LCDUpdateCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
