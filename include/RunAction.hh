#ifndef RunAction_h
#define RunAction_h

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include <fstream>

class RunAction : public G4UserRunAction
{
public:
    RunAction(DetectorConstruction* detector, PrimaryGeneratorAction* primary);
    ~RunAction();

    virtual void BeginOfRunAction(const G4Run *);
    virtual void EndOfRunAction(const G4Run *);

private:
    DetectorConstruction* fDetector = nullptr;
    PrimaryGeneratorAction* fPrimary = nullptr;
    std::ofstream outFile;

};

#endif
