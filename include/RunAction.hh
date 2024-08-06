#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Run.hh"

class RunAction : public G4UserRunAction {
public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void SetNumberOfRuns(G4int runs) { fNumberOfRuns = runs; }

private:
    G4int fNumberOfRuns;
};
