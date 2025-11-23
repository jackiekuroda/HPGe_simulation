#include "BackgroundGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4Gamma.hh"
#include "G4IonTable.hh"
#include "G4ParticleTable.hh"


Background::Background()
{
   fBackgroundSource = new G4GeneralParticleSource();

   fBackgroundSource->ClearAll();

   G4int id =1;
   //creating background radiation

   auto addSource = [this](G4int element, G4int A_number, G4int Z_number,G4double intensity, G4int sourceId)
   {
	   G4double ionCharge = 0.0 * eplus;
	   G4double excitation = 0 * keV;
	   G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z_number, A_number, excitation)

           fBackgroundSource->AddaSource(intensity);
           fBackgroundSource->GetCurrentSource();

           auto src = fBackgroundSource->GetCurrentSource();

	   src->SetParticleDefinition(ion);
	   src->SetParticleCharge(ionCharge);

           auto pos = src->GetPosDist();
           pos->SetPosDisType("Surface");
           pos->SetPosDisShape("Para");
           pos->SetHalfX(.5 *m);
           pos->SetHalfY(.5 *m);
           pos->SetHalfZ(.5 *m);

           auto ang = src->GetAngDist();
           ang->SetAngDistType("planar");
           ang->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));


   };
   addSource(K,40,19,0,.8,id++);
   addSource(U,235,92,0,.05,id++);
   addSource(U,238,92,0,.05,id++);
   addSource(Th,232,90,0,.1,id++);

}

Background::~Background()
{
	delete fBackgroundSource;
}

void Background::GeneratePrimaryVertex(G4Event* anEvent)
{
	fBackgroundSource->GeneratePrimaryVertex(anEvent);
}
