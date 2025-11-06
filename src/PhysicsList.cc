#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmParameters.hh"
#include "G4EmStandardPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonINCLXXPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4NuclideTable.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4RadioactiveDecay.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"

#include "G4EmStandardPhysics_option4.hh"

#include "G4UAtomicDeexcitation.hh"
#include "G4LossTableManager.hh"

// particles
#include "G4BaryonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

PhysicsList::PhysicsList()
{
  G4int verb = 1;
  SetVerboseLevel(verb);

  // Mandatory for G4NuclideTable
  // Half-life threshold must be set small or many short-lived isomers
  // will not be assigned life times (default to 0)
  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1 * picosecond);
  G4NuclideTable::GetInstance()->SetLevelTolerance(1.0 * eV);

  // EM physics
  RegisterPhysics(new G4EmStandardPhysics_option4());

  RegisterPhysics(new G4DecayPhysics(verb));
  RegisterPhysics(new G4RadioactiveDecayPhysics(verb));

  // Hadron Elastic scattering
  RegisterPhysics(new G4HadronElasticPhysics());

  // Hadron Inelastic physics
  RegisterPhysics(new G4HadronPhysicsFTFP_BERT());

  // Ion Elastic scattering
  RegisterPhysics(new G4IonElasticPhysics());

  // Ion Inelastic physics
  RegisterPhysics(new G4IonPhysics());

  // Gamma-Nuclear Physics
  G4EmExtraPhysics* gnuc = new G4EmExtraPhysics();
  gnuc->ElectroNuclear(false);
  gnuc->MuonNuclear(false);
  RegisterPhysics(gnuc);
}


void PhysicsList::ConstructProcess()
{
  G4VModularPhysicsList::ConstructProcess();

  auto* de = new G4UAtomicDeexcitation();
  de->SetFluo(true);   // fluorescence X-rays
  de->SetAuger(true);  // Auger e⁻
  de->SetAugerCascade(true);
  de->SetPIXE(true);   // particle-induced X-ray emission
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);

//  auto theRadDecay = new G4RadioactiveDecay();
//  theRadDecay->SetARM(true);
//  theRadDecay->SetVerboseLevel(1);


}

void PhysicsList::ConstructParticle()
{
  G4BosonConstructor BosonConstructor;
  BosonConstructor.ConstructParticle();

  G4LeptonConstructor LeptonConstructor;
  LeptonConstructor.ConstructParticle();

  G4MesonConstructor MesonConstructor;
  MesonConstructor.ConstructParticle();

  G4BaryonConstructor BaryonConstructor;
  BaryonConstructor.ConstructParticle();

  G4IonConstructor IonConstructor;
  IonConstructor.ConstructParticle();

  G4ShortLivedConstructor ShortLivedConstructor;
  ShortLivedConstructor.ConstructParticle();
}

void PhysicsList::SetCuts()
{
  SetCutsWithDefault();
  SetCutValue(0.0001 * mm, "gamma");
  SetCutValue(0.0001 * mm, "e-");
  SetCutValue(0.0001 * mm, "e+");

}
