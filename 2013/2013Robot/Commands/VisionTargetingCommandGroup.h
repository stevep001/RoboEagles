#ifndef VISIONTARGETINGCOMMANDGROUP_H
#define VISIONTARGETINGCOMMANDGROUP_H

#include "Commands/CommandGroup.h"
#include "ProcessVisionCommand.h"





/**
 *
 *
 * @author nowireless
 */
class VisionTargetingCommandGroup: public CommandGroup {
private:
	ProcessVisionCommand *processVision;
public:	
	VisionTargetingCommandGroup();
};

#endif
