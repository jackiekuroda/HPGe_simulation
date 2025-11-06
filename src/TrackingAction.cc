#include "TrackingAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    auto* particle = track->GetDefinition();
    G4int parentID = track->GetParentID();

    if (particle->GetParticleName() == "gamma" && parentID > 0) {
        const G4VProcess* creator = track->GetCreatorProcess();

        G4String procName = "Unknown";
        if (creator) {
            procName = creator->GetProcessName();
        }
/*
        G4cout << "Decay gamma created: "
               << "trackID=" << track->GetTrackID()
               << " parentID=" << parentID
               << " E=" << track->GetKineticEnergy()/keV << " keV"
               << " by process=" << procName
               << G4endl;
*/
  }
}
