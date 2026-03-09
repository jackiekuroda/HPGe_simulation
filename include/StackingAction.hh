#ifndef StackingAction_h
#define StackingAction_h 1

#include "G4UserStackingAction.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "globals.hh"

class StackingAction : public G4UserStackingAction
{
   public:
   StackingAction();
   ~StackingAction() override;

   G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*) override;

   private:

};

#endif
