#ifndef FRONTPYRAMIDHIGHGOALCOMMANDGROUP_H
#define FRONTPYRAMIDHIGHGOALCOMMANDGROUP_H

#include "Commands/CommandGroup.h"

#define LEFT_DEGREES_TO_TURN (20)
#define RIGHT_DEGREES_TO_TURN (-20)

/**
 *
 *
 * @author nowireless
 */
class FrontPyramidHighGoalCommandGroup: public CommandGroup {
public:	
	enum Side {
		kRight,
		kLeft
	};
	FrontPyramidHighGoalCommandGroup(Side side);
};

#endif
