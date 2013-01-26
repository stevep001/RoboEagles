#include "RPMHoldingCommand.h"
#include "../LoggingPIDOutput.h"


RPMHoldingCommand::RPMHoldingCommand() {
	printf("RPMHoldingCommand constructor\n");

	Requires(prototypingsubsystem);
	rpmSource = new RPMSource();
	timer = new Timer();
	
	printf("RPMHoldingCommand constructor complete\n");
}

RPMHoldingCommand::~RPMHoldingCommand() {
	if (controller != NULL)
	{
		controller->Disable();
		delete controller;
		controller = NULL;
	}
}

// Called just before this Command runs the first time
void RPMHoldingCommand::Initialize() {
	printf("RPMHoldingCommand initialize\n");
	double gearReduction = 4.67;
	double motorRpmMax = 5000;
	rpmMaximum = motorRpmMax / gearReduction;
	
	sampleCount = 0;
	
	float pGain = .0021;
	float iGain = .0002;
	float dGain = 0;
	
	prototypingsubsystem->GetMotorEncoder()->SetPIDSourceParameter(Encoder::kDistance);
	controller = new PIDController(pGain, iGain, dGain, rpmSource, prototypingsubsystem->GetMotor());
	controller->SetInputRange(-rpmMaximum, rpmMaximum);
	controller->SetOutputRange(-1, 1);

	SmartDashboard *sd = oi->getSmartDashboard();
	sd->PutDouble("RPM Maximum", rpmMaximum);
	
	timer->Reset();
	timer->Start();
	lastTime = timer->Get();
	lastCount = prototypingsubsystem->GetMotorEncoder()->Get();
	
	controller->SetSetpoint(1000);
	controller->Enable(); // start calculating PIDOutput values
	printf("RPMHoldingCommand initialize complete\n");
}

// Called repeatedly when this Command is scheduled to run
void RPMHoldingCommand::Execute() {
	double countsPerRevolution = 360;

	double currentTime = timer->Get();
	double timeDifference = currentTime - lastTime;
	lastTime = currentTime;
	
	Encoder* motorEncoder = prototypingsubsystem->GetMotorEncoder();
	int currentCount = motorEncoder->Get();
	int countDifference = currentCount - lastCount;
	double rawRPM = countDifference * (60.0 / countsPerRevolution) / timeDifference;
	double rpm = GetRPM(rawRPM);
	printf("rawRPM %f rpm %f\n", rawRPM, rpm);
	rpmSource->inputRPM(rpm);
	//rpmSource->inputRPM(rpm);
	
	printf("setpoint %f RPM %f result %f error %f \n", controller->GetSetpoint(), rpm, controller->Get(), controller->GetError());
	
	SmartDashboard *sd = oi->getSmartDashboard();

	oi->DisplayEncoder(motorEncoder);
	oi->DisplayPIDController(controller);
	
	sd->PutDouble("Count Difference", countDifference);
	sd->PutDouble("Current count", currentCount);
	sd->PutDouble("Time difference", timeDifference);
	sd->PutDouble("Calculated RPM", rpm);
	sd->PutDouble("Motor speed", prototypingsubsystem->GetMotor()->Get());
	
	sd->PutDouble("Counts per revolution", countsPerRevolution);
	
	lastCount = currentCount;

}

double RPMHoldingCommand::GetRPM(double currentRPM)
{
	previousSamples[4] = previousSamples[3];
	previousSamples[3] = previousSamples[2];
	previousSamples[2] = previousSamples[1];
	previousSamples[1] = previousSamples[0];
	previousSamples[0] = currentRPM;
	
	if (sampleCount < 5) {
		sampleCount++;
		return currentRPM;
	} else {
		double totalRPM = 0;
		for (int i = 0; i < 5; i++)
		{
			totalRPM += previousSamples[i];
		}
		
		return totalRPM / 5;
	}
}
	

// Make this return true when this Command no longer needs to run execute()
bool RPMHoldingCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RPMHoldingCommand::End() {

	timer->Stop();
	if (controller != NULL)
	{
		controller->Disable();
		delete controller;
		controller = NULL;
	}
	printf("RPMHoldingCommand  end\n");}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RPMHoldingCommand::Interrupted() {
	timer->Stop();
	if (controller != NULL)
	{
		controller->Disable();
		delete controller;
		controller = NULL;
	}
	printf("RPMHoldingCommand  interrupted\n");}
