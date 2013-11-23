#include "ProcessVisionCommand.h"

ProcessVisionCommand::ProcessVisionCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	printf("[ProcessVisionCommand] Constructing\n");
	Requires(visionSubsystemV2);
	printf("[ProcessVisionCommand] Constructed\n");
}

// Called just before this Command runs the first time
void ProcessVisionCommand::Initialize() {
	timer = new Timer();

	distance = 0;
	azimuth = 0;
	shooterTiltAngle = 0.0;

	visionSubsystemV2->ProcessCameraImage();
	timer->Reset();
	timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void ProcessVisionCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ProcessVisionCommand::IsFinished() {
	return visionSubsystemV2->IsImageProcessed();
}

// Called once after isFinished returns true
void ProcessVisionCommand::End() {
	timer->Stop();
	printf("[ProcessVisionCommand] It took %f seconds to process\n",
			timer->Get());
	if (visionSubsystemV2->IsHighTargetVisable()
			|| visionSubsystemV2->IsMiddleTargetVisable()
			|| visionSubsystemV2->IsSecondMiddleTargetVisable()) {
		targetsVisable = true;
	} else {
		targetsVisable = false;
	}

	if (visionSubsystemV2->IsHighTargetVisable()) {
		distance = visionSubsystemV2->GetHighTargetDistance();
		azimuth = visionSubsystemV2->GetHighTargetAzimuth();
		shooterTiltAngle = computeTiltAngle(distance, High);
	} else if (visionSubsystemV2->IsMiddleTargetVisable()) {
		distance = visionSubsystemV2->GetMiddleTargetDistance();
		azimuth = visionSubsystemV2->GetMiddleTargetAzimuth();
		shooterTiltAngle = computeTiltAngle(distance, Middle);
	} else if (visionSubsystemV2->IsSecondMiddleTargetVisable()) {
		distance = visionSubsystemV2->GetSecondMiddleTargetDistance();
		azimuth = visionSubsystemV2->GetSecondMiddleTargetAzimuth();
		shooterTiltAngle = computeTiltAngle(distance, Middle);
	}
	printf("[ProcessVisionCommand] Target Distance:%f Azimuth:%f, Shooter Angle %f\n",this->distance, this->azimuth, this->shooterTiltAngle);
	printf("[ProcessVisionCommand] Ending\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ProcessVisionCommand::Interrupted() {
	printf("[ProcessVisionCommand] Interrupted\n");
}

float ProcessVisionCommand::GetDistance() {
	return distance;
}

float ProcessVisionCommand::GetAzimuth() {
	return azimuth;
}

float ProcessVisionCommand::computeTiltAngle(float distance, Target target) {
	/*
	 * High
	 * Angle 18 High: 34ft	Middle: 30
	 * Angle 20 High: 28ft	Middle: 25
	 * Angle 22 High: 21ft	Middle: 19
	 * Angle 24 High: 19ft	Middle: 17
	 * Angle 26 High: 13ft	Middle: 12
	 * Angle 28 High: 12ft	Middle: 10.5
	 * Angle 30 High: 10ft	Middle: 9.5
	 * Angle 32 High: 9.8ft	Middle: 8.8
	 * Angle 34 High: 9.5ft	Middle: 8.4
	 * Angle 36 High: 9ft	Middle: 8		
	 * Angle 38 High: 8ft	Middle: 7.5		
	 * Out Of range
	 * 
	 */

	if (target == High) {
		/*
		 * 38:8-9
		 * 36:9-9.5
		 * 34:9.5-9.8
		 * 32:9.8-10
		 * 30:10-12
		 * 28:12-13
		 * 26:13-19
		 * 24:19-21
		 * 22:21-28
		 * 20:28-34
		 * 18:34-38
		 */
		if ((distance <= 8) && (distance >= 9)) {
			return 38;
		} else if ((distance <= 9) && (distance >= 9.5)) {
			return 36;
		}
		if ((distance <= 9.5) && (distance >= 9.8)) {
			return 34;
		}
		if ((distance <= 9.8) && (distance >= 10)) {
			return 32;
		}
		if ((distance <= 10) && (distance >= 12)) {
			return 30;
		}
		if ((distance <= 12) && (distance >= 13)) {
			return 28;
		}
		if ((distance <= 13) && (distance >= 19)) {
			return 26;
		}
		if ((distance <= 19) && (distance >= 21)) {
			return 24;
		}
		if ((distance <= 21) && (distance >= 28)) {
			return 22;
		}
		if ((distance <= 28) && (distance >= 34)) {
			return 20;
		}
		if ((distance <= 34) && (distance >= 38)) {
			return 18;
		} else {
			return 0;
		}

	} else if (target == Middle) {
		/*
		 * 38: 7.5-8
		 * 36: 8-8.4
		 * 34: 8.4-8.8
		 * 32: 8.8-9.5
		 * 30: 9.5-10
		 * 28: 10-12
		 * 26: 12-17
		 * 24: 17-19
		 * 22: 19-25
		 * 20: 25-30
		 * 18: 30-35
		 */
		if ((distance <= 7.5) && (distance >= 8)) {
			return 38;
		} else if ((distance <= 8) && (distance >= 8.4)) {
			return 36;
		}
		if ((distance <= 8.4) && (distance >= 8.8)) {
			return 34;
		}
		if ((distance <= 8.8) && (distance >= 9.5)) {
			return 32;
		}
		if ((distance <= 9.5) && (distance >= 10)) {
			return 30;
		}
		if ((distance <= 10) && (distance >= 12)) {
			return 28;
		}
		if ((distance <= 12) && (distance >= 17)) {
			return 26;
		}
		if ((distance <= 17) && (distance >= 19)) {
			return 24;
		}
		if ((distance <= 19) && (distance >= 25)) {
			return 22;
		}
		if ((distance <= 25) && (distance >= 30)) {
			return 20;
		}
		if ((distance <= 30) && (distance >= 35)) {
			return 18;
		} else {
			return 0;
		}
	}
	return 0;
}

bool ProcessVisionCommand::AreTargetsVisable() {
	return targetsVisable;
}

float ProcessVisionCommand::GetTiltAngle() {
	return shooterTiltAngle;
}
