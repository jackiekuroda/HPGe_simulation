#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

SensitiveDetector::SensitiveDetector(G4String name) 
: G4VSensitiveDetector(name), fTotalEnergyDeposited(0.)
{}

SensitiveDetector::~SensitiveDetector() {}

void SensitiveDetector::Initialize(G4HCofThisEvent *)
{
    fTotalEnergyDeposited = 0.0; // reset for each event
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    fTotalEnergyDeposited += edep;
    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
    auto analysisManager = G4AnalysisManager::Instance();
    if (fTotalEnergyDeposited > 2 * keV)
    {	G4double a =0.00222277*MeV;
        G4double b = 0.0000129192381*MeV;
	G4double c = .00000108356979*MeV;
        G4double FWHM = std::sqrt(c*fTotalEnergyDeposited*fTotalEnergyDeposited+b*fTotalEnergyDeposited+a*a);

        G4double smear = G4RandGauss::shoot(fTotalEnergyDeposited, FWHM/2.35);

        analysisManager->FillH1(0,  smear);
   }
}


