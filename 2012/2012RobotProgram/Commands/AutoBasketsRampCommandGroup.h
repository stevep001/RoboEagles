#ifndef AUTOBASKETSRAMPCOMMANDGROUP_H
#define AUTOBASKETSRAMPCOMMANDGROUP_H

#include "Commands/CommandGroup.h"

/**
 *
 *
 * @author speterson
 */
class AutoBasketsRampCommandGroup: public CommandGroup {
public:	
	AutoBasketsRampCommandGroup(float initialDelay, float desiredAngleToTurn);
};

#endif
