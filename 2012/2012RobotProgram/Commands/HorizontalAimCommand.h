#ifndef HORIZONTALAIMCOMMAND_H
#define HORIZONTALAIMCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class HorizontalAimCommand: public CommandBase {
public:
	HorizontalAimCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
