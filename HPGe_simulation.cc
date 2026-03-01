#include <iostream>
#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "G4RunManager.hh"
#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4Types.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "Randomize.hh"

#include "G4IonTable.hh"
#include "G4NuclideTable.hh"


int main(int argc, char** argv)
{
   G4double outerDeadLayerThick = 0; //to make the deadlayer an input to easily test many different deadlayers
   // detect interactive mode (if no arguments) and define UI session
   G4UIExecutive* ui = 0;
   if (argc == 1)
   {
	ui = new G4UIExecutive(argc, argv, "Qt");
//	outerdeadlayer = 0.5 *mm;
   }

   else if (argc >= 1)
   {
    	outerDeadLayerThick = std::stod(argv[1]) * mm;
   }
   // choose the Random engine
   G4Random::setTheEngine(new CLHEP::RanecuEngine);

   // use G4SteppingVerboseWithUnits
   G4int precision = 4;
   G4SteppingVerbose::UseBestUnit(precision);

   // construct the run manager

   auto* runManager = new G4RunManager();

   // set mandatory initialization classes
   DetectorConstruction* det = new DetectorConstruction(outerDeadLayerThick);
   runManager->SetUserInitialization(det);
   runManager->SetUserInitialization(new PhysicsList());
   runManager->SetUserInitialization(new ActionInitialization(det));
   //runManager->SetUserAction(new PrimaryGeneratorAction());
   runManager->Initialize();

   //initialize visualization
   G4VisManager* visManager = nullptr;

   //get the pointer to the User Interface manager
   G4UImanager* UImanager = G4UImanager::GetUIpointer();

   if (ui)
   {
    	// interactive mode
    	visManager = new G4VisExecutive;
	visManager->Initialize();
    	ui->SessionStart();
	delete ui;
   }
   else
   {
    	// batch mode
    	G4String command = "/control/execute ";
   	G4String fileName = argv[2];
    	UImanager->ApplyCommand(command + fileName);
   }

   // job termination
   delete visManager;
   delete runManager;
}

