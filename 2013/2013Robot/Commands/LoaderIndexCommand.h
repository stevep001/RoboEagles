#ifndef LOADER_INDEX_COMMAND_H
#define LOADER_INDEX_COMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class LoaderIndexCommand: public CommandBase {
public:
	LoaderIndexCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
