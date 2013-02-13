#ifndef PIZZABOXCONTROLCOMMAND_H
#define PIZZABOXCONTROLCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class PizzaBoxControlCommand: public CommandBase {
public:
	PizzaBoxControlCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
