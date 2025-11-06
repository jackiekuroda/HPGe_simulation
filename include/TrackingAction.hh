#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class TrackingAction : public G4UserTrackingAction {
public:
    TrackingAction() = default;
    ~TrackingAction() override = default;

    void PreUserTrackingAction(const G4Track* track) override;
};
