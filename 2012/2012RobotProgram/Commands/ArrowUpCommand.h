#ifndef ARROWUPCOMMAND_H
#define ARROWUPCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class ArrowUpCommand: public CommandBase {
public:
	ArrowUpCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
