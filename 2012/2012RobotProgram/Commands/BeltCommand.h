#ifndef BELTCOMMAND_H
#define BELTCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class BeltCommand: public CommandBase {
private:
	bool on;
	bool finished;
public:
	BeltCommand(bool on);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
