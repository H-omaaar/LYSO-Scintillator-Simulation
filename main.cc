#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4Version.hh"
#include "G4VisExecutive.hh"
#if G4VERSION_NUMBER >= 930
#include "G4UIExecutive.hh"
#else
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#endif
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "SensitiveDetector.hh"
#include "QGSP_BERT.hh"

int main(int argc, char** argv) {
    // Run manager
    G4RunManager* runManager = new G4RunManager();

    // Mandatory Initialization classes
    G4VUserDetectorConstruction* detector = new DetectorConstruction();
    runManager->SetUserInitialization(detector);

    G4VUserPhysicsList* physics = new PhysicsList();
    runManager->SetUserInitialization(physics);

    // Mandatory User Action classes
    G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction();
    runManager->SetUserAction(gen_action);
    // Set user action classes
    runManager->SetUserAction(new PrimaryGeneratorAction());
    RunAction* runAction = new RunAction();
    runManager->SetUserAction(runAction);
    runManager->SetUserAction(new EventAction());
    runManager->SetUserAction(new SteppingAction());

    // Initialize G4 kernel
    runManager->Initialize();

    // Initialize the visualization manager
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (argc != 1) { // batch mode
        // Command line contains the name of the macro to execute
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else { // interactive mode: define UI session

#if G4VERSION_NUMBER >= 930

        G4UIExecutive* ui = new G4UIExecutive(argc, argv);

        UImanager->ApplyCommand("/control/execute ../vis.mac");

        // Perform multiple runs
        G4int numberOfRuns = 10; // or any number of runs you want
        for (G4int i = 0; i < numberOfRuns; ++i) {
            runManager->BeamOn(1);
        }

        ui->SessionStart();
        delete ui;
#else
        // Older versions of G4: UI selected by user
#ifdef G4UI_USE_TCSH
        G4UIsession* ui = new G4UIterminal(new G4UItcsh);
#else
        G4UIsession* ui = new G4UIterminal();
#endif

        UImanager->ApplyCommand("/control/execute ../vis.mac");

        // Perform multiple runs
        G4int numberOfRuns = 10; // or any number of runs you want
        for (G4int i = 0; i < numberOfRuns; ++i) {
            runManager->BeamOn(1);
        }

        ui->SessionStart();
        delete ui;
#endif
    }

    delete runManager;

    return 0;
}
