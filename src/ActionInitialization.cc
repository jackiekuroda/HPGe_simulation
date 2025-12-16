#include "ActionInitialization.hh"
#include "G4GenericIon.hh"
#include "PrimaryGeneratorAction.hh"
#include "BackgroundGeneratorAction.hh"
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
  G4GenericIon::Definition();

  PrimaryGeneratorAction* primary = new PrimaryGeneratorAction();
  SetUserAction(primary);

  RunAction* runAction = new RunAction(fDetector, primary);
  SetUserAction(runAction);
  SetUserAction(new TrackingAction());

}
