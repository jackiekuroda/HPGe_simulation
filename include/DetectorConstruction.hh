#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4UserLimits.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"


class DetectorMessenger;
class G4GlobalMagFieldMessenger;

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    G4LogicalVolume* GetLogicDetector() const { return fLogActiveCrystal; }

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();


    // Material and geometry construction helpers
    void SetSource(G4bool value);

    void SetOutDeadLayerThickness(double value);
    void SetCoverThick(G4double value);
    void SetShellRadius(G4double value);
    void SetShellLength(G4double value);
    void SetShellThick(G4double value);
    void SetEndGap(G4double value);
    void SetholderLength(G4double value);
    void SetholderThick(G4double value);
    void SetholderTopThick(G4double value);
    void SetholderBottomThick(G4double value);
    void SetmylarThick (G4double value);
    void SetkaptonThick (G4double value);
    void SetCrystalRadius (G4double value);
    void SetCrystalHalfLength (G4double value);
    void SetCrystalEndRadius (G4double value);
    void SetHoleDepth(G4double value);
    void SetHoleRadius(G4double value);
    void SetOuterDeadLayerThick(G4double value);
    void SetInnerDeadLayerThick(G4double value);
    void UpdateGeometry();
    void SetSourceMove(G4double value);

   void SetDetectorLength(G4double length);
   void SetDetectorThickness(G4double thickness);
   void SetDetectorMaterial(const G4String& name);

private:

    void DefineMaterials();
    G4VPhysicalVolume* ConstructWorld();

    void ConstructHPGeDetector(G4LogicalVolume* );
    void ConstructSource(G4LogicalVolume* motherLogicalVolume);
    void ConstructPbShield(G4LogicalVolume* motherLogicalVolume);
    void ConstructAustinLeadHouse(G4LogicalVolume* motherLogicalVolume);
    void ConstructRoom(G4LogicalVolume* motherLogicalVolume);
    G4LogicalVolume* logicDetector = nullptr;
    // Core geometry
    G4VPhysicalVolume* physiWorld;

    // Detector dimensions
    G4double coverThick;
    G4double shellRadius;
    G4double shellLength;
    G4double shellThick;
    G4double endGap;
    G4double detectorMove;

    G4double crystalRadius;
    G4double crystalHalfLength;
    G4double crystalEndRadius;
    G4double holeDepth;
    G4double holeRadius;
    G4double outerDeadLayerThick;
    G4double innerDeadLayerThick;

    //holder
    G4double holderLength;
    G4double holderThick ;
    G4double holderTopThick ;
    G4double holderBottomThick ;
    G4double mylarThick;
    G4double kaptonThick;
    G4double SourceMove;

    // Flags
    G4bool fCheckOverlaps;

    // Materials
    G4Material* GeCrystal;
    G4Material* Shield_Air;
    G4LogicalVolume* fLogActiveCrystal;

    // Optional
    G4UserLimits* stepLimit;
};

#endif

