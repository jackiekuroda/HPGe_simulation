
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "BackgroundGeneratorAction.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"

class G4ParticleGun;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

  public:
    void GeneratePrimaries(G4Event* event) override;
    G4ParticleGun* GetParticleGun() { return fParticleGun; }
    G4GeneralParticleSource* GetGPS() { return fSource; }
  private:

	G4GeneralParticleSource* fSource = nullptr;
	G4ParticleGun* fParticleGun = nullptr;
   	Background* fBackground;

  	bool fAlternate;
  	G4int fPeriod;

};


#endif
