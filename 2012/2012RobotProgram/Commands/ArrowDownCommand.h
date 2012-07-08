#ifndef ARROWDOWNCOMMAND_H
#define ARROWDOWNCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class ArrowDownCommand: public CommandBase {
public:
	ArrowDownCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
