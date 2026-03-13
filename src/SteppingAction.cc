#include "SteppingAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Neutron.hh"
#include "G4Proton.hh"
#include "G4Gamma.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

SteppingAction::SteppingAction(){}
SteppingAction::~SteppingAction(){}

G4int SteppingAction::fGammaCount = 0;


void SteppingAction::UserSteppingAction(const G4Step *step)
{
   G4Track *track = step->GetTrack();
   if (!track) return;

   if (track ->GetCurrentStepNumber() != 1) return;
   if (track ->GetDefinition() != G4Gamma::Gamma()) return;
   if (track->GetKineticEnergy() <= 0) return;

   G4String process = "process";
   if (track ->GetCreatorProcess())
	process = track->GetCreatorProcess()->GetProcessName();

   if (process == "Radioactivation")
   {
//	G4cout << "Gamma created by "
//	       << process
//	       << track->GetKineticEnergy()
//	       << G4endl;

	fGammaCount++;
   }
}

