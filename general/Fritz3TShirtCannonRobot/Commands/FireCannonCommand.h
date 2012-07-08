#ifndef FIRECANNONCOMMAND_H
#define FIRECANNONCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class FireCannonCommand: public CommandBase {
public:
	FireCannonCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
