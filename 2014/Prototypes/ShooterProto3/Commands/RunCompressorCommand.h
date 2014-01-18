#ifndef RUNCOMPRESSORCOMMAND_H
#define RUNCOMPRESSORCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class RunCompressorCommand: public CommandBase {
public:
	RunCompressorCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
