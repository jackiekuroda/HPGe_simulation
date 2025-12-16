#ifndef BACKGROUNDGENERATOR_HH
#define BACKGROUNDGENERATOR_HH

#include "G4VPrimaryGenerator.hh"
#include "G4ParticleGun.hh"

class Background : public G4VPrimaryGenerator
{
	public:
		Background();
		virtual ~Background();
         	void GeneratePrimaryVertex(G4Event* anEvent) override;

	private:
		G4ParticleGun* fBackgroundSource;
};

#endif
