#include "PrimaryGeneratorAction.hh"
#include "G4EmParameters.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4Gamma.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: fAlternate(true)
{
  // Create particle gun with 1 particle
  fParticleGun = new G4ParticleGun(1);
  fParticleGun->SetParticleEnergy(0.0 * eV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 108.68*mm));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 0.));

  // Initialize background source
  fBackground = new Background();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fBackground;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  auto eventID = anEvent->GetEventID();
  bool doSource = true;

  if (fAlternate)
  {
    doSource == true;
  }

  if (doSource)
  {
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }

  else
  {
    // Use background generator
    fBackground->GeneratePrimaryVertex(anEvent);
  }
}
