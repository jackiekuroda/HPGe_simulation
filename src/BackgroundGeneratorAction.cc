#include "BackgroundGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"

Background::Background()
{
   fBackgroundSource = new G4ParticleGun(1);
}

void Background::GeneratePrimaryVertex(G4Event* event)
{

   auto ion_source = [&](G4int Z, G4int A)
   {
	G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z, A, 0.0*keV);

	fBackgroundSource->SetParticleDefinition(ion);
	fBackgroundSource->SetParticleEnergy(0.0 *keV);

	G4double x = 0;
	G4double y = 0;
	G4double z = 0;


        fBackgroundSource->SetParticlePosition(G4ThreeVector(x, y, z));

 	fBackgroundSource->GeneratePrimaryVertex(event);

   };


   G4double r = G4UniformRand();

   if (r < 0.8)
   {
	ion_source(19, 40);
   }

   else if (r < 0.85)
   {
	ion_source(92, 235);
   }

   else if (r < 0.9)
   {
	ion_source(92, 238);
   }

   else
   {
	ion_source(90, 232);
   }
}

Background::~Background()
{
	delete fBackgroundSource;
}


