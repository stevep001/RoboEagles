#ifndef KILLVISIONTARGETINGCOMMANDGROUPCOMMAND_H
#define KILLVISIONTARGETINGCOMMANDGROUPCOMMAND_H

#include "../CommandBase.h"
#include "VisionTargetingCommandGroup.h"

/**
 *
 *
 * @author nowireless
 */
class KillVisionTargetingCommandGroupCommand: public CommandBase {
private:
	VisionTargetingCommandGroup *m_visionTargeting;
public:
	KillVisionTargetingCommandGroupCommand(VisionTargetingCommandGroup *visionTargeting);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
