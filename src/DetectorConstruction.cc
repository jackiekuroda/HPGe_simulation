#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GeometryManager.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4RunManager.hh"
#include "G4UserLimits.hh"

#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Torus.hh"
#include "G4Cons.hh"

//parser headers
#include "G4GDMLParser.hh"

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction(),
      physiWorld(nullptr),
      stepLimit(nullptr),
      fCheckOverlaps(true)
{
    DefineMaterials();

    // Detector shell
    shellRadius = 0.5 * 101.70 *mm;
    shellLength = 148.1 *mm;
    shellThick = 1.5 * mm;
    endGap = 5.0 * mm;

   //holder
   holderLength =105.*mm;
   holderThick =0.76 *mm;
   holderTopThick =0.03 *mm;
   holderBottomThick =3.2 *mm;
   mylarThick =8.5 *um;
   kaptonThick = 102 *um;

    // Ge crystal
    crystalRadius = 0.5 * 68.2 *mm;
    crystalHalfLength = 0.5 * 70.2 * mm;
    crystalEndRadius = 8. * mm;
    holeDepth = 39.5 * mm;
    holeRadius = 0.5 * 8 * mm;
    outerDeadLayerThick = 0.5 * mm;
    innerDeadLayerThick = 0.3 * um;
 }


DetectorConstruction::~DetectorConstruction()
{
    delete stepLimit;
}

void DetectorConstruction::DefineMaterials()
{
    G4NistManager* nist = G4NistManager::Instance();
    GeCrystal = nist->FindOrBuildMaterial("G4_Ge");
    Shield_Air = nist->FindOrBuildMaterial("G4_AIR");  // used for world material
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    // Construct world
    G4double worldSize = 10.0 * m;
    G4Box* solidWorld = new G4Box("World", worldSize, worldSize, worldSize);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, Shield_Air, "LogicWorld");
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    physiWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "PhysiWorld", nullptr, false, 0, fCheckOverlaps);

    //to add detector components
    ConstructHPGeDetector(logicWorld);

   //to add the source
   //ConstructSource(logicWorld);

   //to add the shielding
   //ConstructPbShield(logicWorld);

   //to add the lead house used in the pnnl run
//   ConstructAustinLeadHouse(logicWorld);


   return physiWorld;
}

//creating the room so the background radiation can like comeout it
void  DetectorConstruction::ConstructRoom(G4LogicalVolume* motherLogicalVolume)
{
        G4Material* roomMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_CONCRETE");

        G4Box* outer = new G4Box("Outer", 10.*m,10.*m ,10.*m);
	G4Box* inner = new G4Box("Inner", 9.8*m,9.8*m ,9.8*m);
	G4SubtractionSolid* room = new G4SubtractionSolid("Room", outer, inner);
        G4LogicalVolume * logRoom = new G4LogicalVolume(room,roomMaterial,"Room_log",0,0,0);

        new G4PVPlacement(0,G4ThreeVector(),logRoom,"Room_phys", motherLogicalVolume,false,0,fCheckOverlaps);
}



//creating the Source
void  DetectorConstruction::ConstructSource(G4LogicalVolume* motherLogicalVolume)
{
	G4Material* SourceMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

	G4VSolid * SourceShape = new G4Tubs("SourceShape", 0.*cm,.5*cm ,.5*cm ,	0. *deg,360. *deg);
	G4LogicalVolume * logSource = new G4LogicalVolume(SourceShape,SourceMaterial,"Source_log",0,0,0);

	new G4PVPlacement(0,G4ThreeVector(0.,0.,20*cm ),logSource,"Source_phys", motherLogicalVolume,false,0,fCheckOverlaps);

	G4VisAttributes* visAttSource = new G4VisAttributes(G4Colour(0.3,0.2,1.0));
	visAttSource->G4VisAttributes::SetForceSolid(true);
	logSource->SetVisAttributes(visAttSource);
}


//creating the leadshelieding
void DetectorConstruction::ConstructPbShield(G4LogicalVolume* motherLogicalVolume)
{
        G4Material* lead = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");

 	G4VisAttributes* visAttlead = new G4VisAttributes(G4Colour(0,0.2,1.0,0.6));
        visAttlead->G4VisAttributes::SetForceSolid(true);

	//lead house i designed in CAD
	/*
	G4GDMLParser parser;
	parser.Read("leadhouse.gdml");
	G4LogicalVolume* loglead = parser.GetVolume("leadhouse");
	loglead->SetMaterial(lead);

	//cad file positioned wrong need to rotate it
	G4RotationMatrix* rot = new G4RotationMatrix();
	rot->rotateY(180* deg);

        new G4PVPlacement(rot, G4ThreeVector(0,20*mm,0.82* shellLength -23.050000000000011), loglead, "Lead_phys", motherLogicalVolume, false, 0, fCheckOverlaps);

 	G4VisAttributes* visAttlead = new G4VisAttributes(G4Colour(0,0.2,1.0,0.6));
        visAttlead->G4VisAttributes::SetForceSolid(true);
        loglead->SetVisAttributes(visAttlead);
	*/


	//copper to go around detector

	/*
	G4Material* cu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");

	G4double  sphi =   0.*deg;
        G4double  dphi = 360.*deg;

        G4Tubs* outer = new G4Tubs("Outer",  0.*mm, shellRadius+ 5*mm, 0.5*shellLength, sphi, dphi);
        G4Tubs* inner = new G4Tubs("Inner",  0.*mm, shellRadius+.5*mm, 0.5*shellLength, sphi, dphi);
        G4SubtractionSolid* copper = new G4SubtractionSolid("Copper", outer, inner);
        G4LogicalVolume* logCopper = new G4LogicalVolume(copper, lead,"Copper_log",0,0,0);
	new G4PVPlacement(0, G4ThreeVector(0,0, 0), logCopper, "Copper_phys", motherLogicalVolume, false, 0, fCheckOverlaps);

        G4VisAttributes* visAttcopper = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.3));
        visAttcopper->G4VisAttributes::SetForceSolid(true);
        logCopper->SetVisAttributes(visAttcopper);
	*/

}


void DetectorConstruction::ConstructAustinLeadHouse(G4LogicalVolume* motherLogicalVolume)
{
        G4Material* lead = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");

 	G4VisAttributes* visAttlead = new G4VisAttributes(G4Colour(0,0.2,1.0,0.6));
        visAttlead->G4VisAttributes::SetForceSolid(true);

	//lead house used in pnnl run
	G4GDMLParser parser;
	parser.Read("../gdml/leadhouse.gdml");

	G4LogicalVolume* loglead = parser.GetVolume("leadhouse_vol");
	loglead->SetMaterial(lead);
        new G4PVPlacement(0, G4ThreeVector(0,0,0), loglead, "Lead_phys", motherLogicalVolume, false, 0, fCheckOverlaps);
        loglead->SetVisAttributes(visAttlead);


}

//creating the detector
void   DetectorConstruction::ConstructHPGeDetector(G4LogicalVolume* motherLogicalVolume)
{
        //setting up materials to be used
        G4NistManager* nist = G4NistManager::Instance();
        G4Material* Al = nist->FindOrBuildMaterial("G4_Al");
	G4Material* mylar= nist->FindOrBuildMaterial("G4_MYLAR");
        G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

        G4VisAttributes* invisibleAttribs = new G4VisAttributes(false);

        G4double  sphi =   0.*deg;
        G4double  dphi = 360.*deg;

        //detector
        G4VSolid *HPGe = new G4Tubs("HPGe", 0.*mm, shellRadius, 0.5*shellLength, sphi, dphi);
        G4LogicalVolume * logHPGe = new G4LogicalVolume(HPGe,vacuum,"logHPGe",0,0,0);
        new G4PVPlacement(0,G4ThreeVector(0. ,0. ,0.),logHPGe,"physiHPGe", motherLogicalVolume,false,0,fCheckOverlaps);

	//IR window
	G4VSolid *mylarLayer = new G4Tubs("mylarLayer",0.*mm,holderThick+ crystalRadius,0.5*mylarThick,sphi,dphi);
	G4LogicalVolume * logmylar= new G4LogicalVolume(mylarLayer,mylar ,"logmylar",0,0,0);

        G4VSolid *kaptonLayer = new G4Tubs("kaptonLayer",0.*mm,holderThick+ crystalRadius,0.5*kaptonThick,sphi,dphi);
        G4LogicalVolume * logkapton= new G4LogicalVolume(kaptonLayer,mylar ,"logkapton",0,0,0);
	//holder
	G4VSolid* holderOuter = new G4Tubs("holderOuter",0.*mm,crystalRadius + holderThick,0.5*holderLength,sphi,dphi);
	G4VSolid* holderInner = new G4Tubs("holderInner",0.*mm,crystalRadius,0.5*(holderLength - holderBottomThick),sphi,dphi);
	G4SubtractionSolid* holder = new G4SubtractionSolid("holder",holderOuter,holderInner,0,G4ThreeVector(0., 0., 0.5*holderBottomThick));
	G4LogicalVolume* logholder = new G4LogicalVolume(holder, Al, "logholder", 0, 0, 0);

        //detector shell
        G4VSolid *shell1 = new G4Tubs("shell1",0.*mm, shellRadius, 0.5*shellLength, sphi, dphi);
        G4VSolid *shell2 = new G4Tubs("shell2", 0.*mm, shellRadius-shellThick, 0.5*shellLength - shellThick, sphi, dphi);
        G4VSolid * shell = new G4SubtractionSolid("shell", shell1 ,shell2 ,0,G4ThreeVector(0., 0.,0.0) );
        G4LogicalVolume *logShell = new G4LogicalVolume(shell,Al,"logShell",0,0,0);

        //crystal
        G4VSolid *crystal1 = new G4Tubs("cyl1", 0. *mm, crystalRadius - crystalEndRadius, crystalHalfLength, sphi, dphi);
        G4VSolid *crystal2 = new G4Tubs("cyl2", 0. *mm, crystalRadius, crystalHalfLength - 0.5 * crystalEndRadius, sphi, dphi);
        G4VSolid *tor1 = new G4Torus("tor1", 0. *mm, crystalEndRadius, crystalRadius - crystalEndRadius, sphi, dphi);
        G4VSolid *crystal3 = new G4UnionSolid("cry3", crystal1,crystal2,0,G4ThreeVector(0., 0., -0.5*(crystalEndRadius)));
        G4VSolid *crystal4 = new G4UnionSolid("cry4", crystal3,tor1,0,G4ThreeVector(0., 0., crystalHalfLength - crystalEndRadius));

        //making the active crystal shape
        G4double activeRadius = crystalRadius - outerDeadLayerThick;
        G4double activeHalfLength = crystalHalfLength - 0.5*outerDeadLayerThick;
        G4double activeEndRadius = crystalEndRadius -outerDeadLayerThick;
        G4VSolid *activeCrystal1 = new G4Tubs("acyl1", 0. *mm, activeRadius - activeEndRadius, activeHalfLength, sphi, dphi);
        G4VSolid *activeCrystal2 = new G4Tubs("acyl2", 0. *mm, activeRadius, activeHalfLength - 0.5 * activeEndRadius, sphi, dphi);
        G4VSolid *activeTor1 = new G4Torus("activeTor1", 0. *mm, activeEndRadius, activeRadius - activeEndRadius, sphi, dphi);
        G4VSolid *activeCrystal3 = new G4UnionSolid("cry3", activeCrystal1,activeCrystal2,0,G4ThreeVector(0., 0., -0.5*(activeEndRadius)));
        G4VSolid *activeCrystal4 = new G4UnionSolid("cry4", activeCrystal3,activeTor1,0,G4ThreeVector(0., 0., activeHalfLength - activeEndRadius));

        //making outer dead layer
        G4VSolid *outerDeadLayer = new G4SubtractionSolid("outerDeadLayer", crystal4 ,activeCrystal4 ,0,G4ThreeVector(0., 0., -0.5*outerDeadLayerThick));

        //making the hole
        G4VSolid *hole1 = new G4Tubs("hole1", 0.*mm, holeRadius, 0.5*(holeDepth- holeRadius), sphi, dphi);
        G4VSolid *hole2 = new G4Orb("hole2",holeRadius);
        G4VSolid *hole = new G4UnionSolid("hole", hole1, hole2, 0,  G4ThreeVector(0., 0.,0.5*(holeDepth- holeRadius) ) );

        //making the inner dead layer
        G4VSolid *innerDead1 = new G4Tubs("innerDead1", 0.*mm, holeRadius+ innerDeadLayerThick, 0.5*(holeDepth- holeRadius), sphi, dphi);
        G4VSolid *innerDead2 = new G4Orb("innerDead2",holeRadius +innerDeadLayerThick);
        G4VSolid *innerDead3 = new G4UnionSolid("innerDead3", innerDead1,innerDead2,0 ,  G4ThreeVector(0., 0.,0.5*(holeDepth- holeRadius) ) );
        G4VSolid *innerDeadLayer = new G4SubtractionSolid("innerDeadLayer", innerDead3,hole,0,G4ThreeVector(0., 0.,0.));

        //making final detector shape
        G4VSolid * activeCrystal = new G4SubtractionSolid("activeCrystal", activeCrystal4 ,innerDead3,0,G4ThreeVector(0., 0.,-activeHalfLength+ 0.5*(holeDepth - holeRadius) ) );
        G4LogicalVolume * logOuterDeadLayer = new G4LogicalVolume(outerDeadLayer,GeCrystal,"logOuterDeadLayer",0,0,0);
        G4LogicalVolume * logInnerDeadLayer = new G4LogicalVolume(innerDeadLayer,GeCrystal,"logInnerDeadLayer",0,0,0);

        //assigns as member variable
        fLogActiveCrystal = new G4LogicalVolume(activeCrystal, GeCrystal, "logActiveCrystal");

        //placing the detector shell in the detector volume
        new G4PVPlacement(0,G4ThreeVector(),logShell,"physiShell", logHPGe,false,0,fCheckOverlaps);
	//
	new G4PVPlacement(0,G4ThreeVector(0., 0.,0.5*(shellLength + mylarThick + 2*kaptonThick)-shellThick-endGap),logmylar,"physimylarLayer",logHPGe,false,0,fCheckOverlaps);
	//
	new G4PVPlacement(0,G4ThreeVector(0., 0.,0.5*(shellLength + kaptonThick)-shellThick-endGap),logkapton,"physikaptonLayer",logHPGe,false,0,fCheckOverlaps);
	//
	new G4PVPlacement(0,G4ThreeVector(0., 0.,0.5*(shellLength - holderLength)-shellThick-endGap),logholder,"physiholder",logHPGe,false,0,fCheckOverlaps);

        //placing the outer dead layer in the detector volume
        new G4PVPlacement(0, G4ThreeVector(0., 0.,0.5*shellLength - crystalHalfLength -shellThick-endGap ), logOuterDeadLayer,"physiOuterDeadLayer", logHPGe,false,0,fCheckOverlaps);
        //placing the active crystral in the detector volume
        new G4PVPlacement(0, G4ThreeVector(0., 0.,0.5*shellLength - activeHalfLength -shellThick-endGap-outerDeadLayerThick), fLogActiveCrystal,"physiActiveCrystal", logHPGe,false,0,fCheckOverlaps);
        //placing the inner dead layer in the detector volume
        new G4PVPlacement(0, G4ThreeVector(0., 0.,0.5*(shellLength - holeDepth+holeRadius)-shellThick-endGap-(2.*crystalHalfLength -holeDepth+holeRadius)), logInnerDeadLayer,"physiInnerDeadLayer", logHPGe,false,0,fCheckOverlaps);

        //Detector Visualization Attributes
        G4VisAttributes* HPGeVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.00));
        logHPGe->SetVisAttributes(HPGeVisAtt);

        G4VisAttributes* shellVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.00));
        logShell->SetVisAttributes(shellVisAtt);

        G4VisAttributes* outerDeadLayerVisAtt = new G4VisAttributes(G4Colour(0.9,1.0,0.0,0.80));
        outerDeadLayerVisAtt->G4VisAttributes::SetForceSolid(true);
        logOuterDeadLayer->SetVisAttributes(outerDeadLayerVisAtt);

        G4VisAttributes* activeCrystalVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.3));
        activeCrystalVisAtt->G4VisAttributes::SetForceSolid(true);
        fLogActiveCrystal->SetVisAttributes(activeCrystalVisAtt);


        G4VisAttributes* innerDeadLayerVisAtt = new G4VisAttributes(G4Colour(0.9,1.0,0.0,0.80));
        innerDeadLayerVisAtt->G4VisAttributes::SetForceSolid(true);
        logInnerDeadLayer->SetVisAttributes(innerDeadLayerVisAtt);

        G4VisAttributes* mylarVisAtt = new G4VisAttributes(G4Colour(0.9,1.0,0.0,0.80));
        mylarVisAtt->G4VisAttributes::SetForceSolid(true);
        logmylar->SetVisAttributes(mylarVisAtt);

	G4VisAttributes* kaptonVisAtt = new G4VisAttributes(G4Colour(0.98,1.0,0.0,0.80));
        kaptonVisAtt->G4VisAttributes::SetForceSolid(true);
        logkapton->SetVisAttributes(kaptonVisAtt);

}


void DetectorConstruction::ConstructSDandField()
{
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
    auto HPGeDetector = new SensitiveDetector("HPGe");
    G4SDManager::GetSDMpointer()->AddNewDetector(HPGeDetector);
    fLogActiveCrystal->SetSensitiveDetector(HPGeDetector);
}

