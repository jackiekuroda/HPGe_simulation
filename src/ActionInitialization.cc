#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "TrackingAction.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* detector) : fDetector(detector) {}


ActionInitialization::~ActionInitialization() {} 

void ActionInitialization::BuildForMaster() const
{
  RunAction* runAction = new RunAction(fDetector, nullptr);
  SetUserAction(runAction);
}


void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* primary = new PrimaryGeneratorAction();
  SetUserAction(primary);

  RunAction* runAction = new RunAction(fDetector, primary);
  SetUserAction(runAction);
  SetUserAction(new TrackingAction());

}
