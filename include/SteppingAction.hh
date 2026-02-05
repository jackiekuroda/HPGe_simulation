class SteppingAction : public G4UserSteppingAction
{
   public:
	SteppingAction();
	virtual ~SteppingAction();

	virtual void UserStepppingAction(const G4Step* step);

	static G4int fGammaCount;
}
