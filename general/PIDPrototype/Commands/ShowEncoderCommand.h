#ifndef SHOWENCODERCOMMAND_H
#define SHOWENCODERCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class ShowEncoderCommand: public CommandBase {
public:
	ShowEncoderCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
