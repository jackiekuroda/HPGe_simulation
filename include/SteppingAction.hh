#ifndef SteppingAction_h
#define SteppingAction_h

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "G4VUserTrackInformation.hh"

#include <vector>

class MyTrackInfo : public G4VUserTrackInformation
{
   public:
	MyTrackInfo() : counted(false) {}
	virtual ~MyTrackInfo() {}

	G4bool counted;
};

class G4ParticleDefinition;

class SteppingAction : public G4UserSteppingAction
{
   public:
	SteppingAction();
	virtual ~SteppingAction();

	void UserSteppingAction(const G4Step*) override;

	static G4int fGammaCount;
 	static std::vector<G4double> fGammaEnergies;
};

#endif
