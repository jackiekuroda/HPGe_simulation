#include "RunAction.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include "G4UImanager.hh"
#include "G4VModularPhysicsList.hh"

#include "G4RegionStore.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4LogicalVolumeStore.hh"

#include "G4EmParameters.hh"

#include <iomanip>

RunAction::RunAction(DetectorConstruction* detector, PrimaryGeneratorAction* primary)
  : fDetector(detector), fPrimary(primary)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->CreateH1("Edep", "Energy deposit", 8192, 0., 3.5 * MeV);

    analysisManager->CreateNtuple("Photons", "Photons");
    analysisManager->CreateNtupleIColumn("iEvent");
    analysisManager->CreateNtupleDColumn("fX");
    analysisManager->CreateNtupleDColumn("fY");
    analysisManager->CreateNtupleDColumn("fZ");
    analysisManager->CreateNtupleDColumn("fGlobalTime");
    analysisManager->CreateNtupleDColumn("fWlen");
    analysisManager->FinishNtuple(0);
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    analysisManager->OpenFile("output" + strRunID.str() + ".root");

    outFile.open("simulation_output.txt");

}

void RunAction::EndOfRunAction(const G4Run *run)
{
   G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

   analysisManager->Write();

   analysisManager->CloseFile();

   G4int runID = run->GetRunID();

   G4cout << "Finishing run " << runID << G4endl;


   outFile << "\n======= Run Summary =======\n";

   outFile << "\n--- Source ---\n";

//   G4String isotope = fPrimary->GetSoureName();
//   outFile << "Source present" << isotope << "\n";

   G4int totalEvents = run->GetNumberOfEvent();

   outFile << " Total events simulated: " << totalEvents << "\n";


   outFile << " Total gammas produced: "  << SteppingAction::fGammaCount << "\n";


   outFile << "\n--- Detector Parameters ---\n";

   G4double outerdeadlayer = fDetector->GetouterDeadLayerThick();
   G4double innerdeadlayer = fDetector->GetinnerDeadLayerThick();
   G4double crystalradius = fDetector->GetCrystalRadius();
   G4double crystallength = fDetector->GetCrystalHalfLength();
   G4double shellradius = fDetector->GetShellRadius();
   G4double shelllength = fDetector->GetShellLength();
   G4double shellthick = fDetector->GetShellThick();
   G4double holedepth = fDetector->GetHoleDepth();
   G4double holeradius = fDetector->GetHoleRadius();
   G4double holderlength = fDetector->GetholderLength();
   G4double holderthick = fDetector->GetholderThick();
   G4double holderthicktop = fDetector->GetholderTopThick();
   G4double holderthickbottom = fDetector->GetholderBottomThick();

   outFile << " Crystal radius: " << crystalradius <<" mm \n";
   outFile << " Crystal length: " << crystallength <<" mm \n";

   outFile << " Outer dead layer thickness: " << outerdeadlayer <<" mm \n";
   outFile << " Inner dead layer thickness: " << innerdeadlayer <<" mm \n";

   outFile << " Detector endcap outer radius: " << shellradius <<" mm \n";
   outFile << " Detector endcap length: " << shelllength <<" mm \n";
   outFile << " Detector endcap thickness: " << shellthick <<" mm \n";

   outFile << " Crystal holder outer radius: " << holderthick + crystalradius <<" mm \n";
   outFile << " Crystal holder length: " << holderlength <<" mm \n";
   outFile << " Crystal holder thickness: " << holderthick <<" mm \n";
   outFile << " Top of Crystal holder thickness: " << holderthicktop <<" mm \n";
   outFile << " Bottom of Crystal holder thickness: " << holderthickbottom <<" mm \n";

   outFile << " Bore hole depth: " << holedepth <<" mm \n";
   outFile << " Bore hole radius: " << holeradius <<" mm \n";

   outFile << "\n--- Shielding ---\n";

   if(fDetector->HasPbShield())
   {
   	outFile << "Lead Shielding was placed around the detector \n";
   }

   else
   {
   	outFile << "No shielding present \n";
   }

   outFile << "\n--- Materials ---\n";

   auto logStore = G4LogicalVolumeStore::GetInstance();

   G4Material* crystalMat = nullptr;
   G4Material* innerDeadLayerMat = nullptr;
   G4Material* outerDeadLayerMat = nullptr;
   G4Material* mylarMat = nullptr;
   G4Material* kaptonMat = nullptr;
   G4Material* endcapMat = nullptr;
   G4Material* holderMat = nullptr;

   for (auto log : *logStore)
   {
	if (log->GetName() == "fLogActiveCrystal")
	{
		crystalMat = log->GetMaterial();
		outFile << " Crystal material: " << crystalMat << "\n";
	}

	else if (log->GetName() == "logOuterDeadLayer")
	{
		outerDeadLayerMat = log->GetMaterial();
		outFile << " Outer dead layer material: " << outerDeadLayerMat << "\n";
	}

	else if (log->GetName() == "logInnerDeadLayer")
	{
		innerDeadLayerMat = log->GetMaterial();
		outFile << " Inner dead layer material: " << innerDeadLayerMat << "\n";
	}

	else if (log->GetName() == "logmylar")
		mylarMat = log->GetMaterial();

	else if (log->GetName() == "logkapton")
	{
		kaptonMat = log->GetMaterial();
		outFile << " IR window material: " << kaptonMat << "\n" << mylarMat << "\n";
	}

	else if (log->GetName() == "logShell")
	{
		endcapMat = log->GetMaterial();
		outFile << " Endcap material: " << endcapMat << "\n";
	}

	else if (log->GetName() == "logholder")
	{
		holderMat = log->GetMaterial();
		outFile << " Crystal holder material: " << holderMat << "\n";
	}

   }


   outFile << "\n--- Physics ---\n";
   auto phys = G4RunManager::GetRunManager()->GetUserPhysicsList();
   const auto modularphys =dynamic_cast<const G4VModularPhysicsList*>(phys);

   if (modularphys)
   {
	for (G4int i = 0;; ++i)
	{
		const G4VPhysicsConstructor* constructor = modularphys->GetPhysics(i);

		if(!constructor) break;

		outFile << " -  " << constructor->GetPhysicsName() << "\n";
   	}
   }

   outFile << "\n--- Production cuts per region ---\n";

   auto regionStore = G4RegionStore::GetInstance();

   for (const auto& region : *regionStore)
   {
	outFile << "\nRegion: " << region->GetName() << "\n";

	G4ProductionCuts* cuts = region->GetProductionCuts();

	if (cuts)
	{
		outFile << "   Gamma cut:   " << cuts->GetProductionCut("gamma")/mm << " mm\n";

		outFile << "   e- cut:      " << cuts->GetProductionCut("e-")/mm << " mm\n";

		outFile << "   e+ cut:      " << cuts->GetProductionCut("e+")/mm << " mm\n";

		outFile << "   Proton cut:  " << cuts->GetProductionCut("proton")/mm << " mm\n";
	}
   }


   outFile << "\n--- Electromagnetic parameters ---\n";

   auto emParams = G4EmParameters::Instance();

   outFile << "   Fluorescence enabled: " << (emParams->Fluo() ? "Yes" : "No") << "\n";
   outFile << "   Auger enabled: " << (emParams->Auger() ? "Yes" : "No") << "\n";
   outFile << "   PIXIE enabled: " << (emParams->Fluo() ? "Yes" : "No") << "\n";


   outFile.close();

}
