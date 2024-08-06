# LYSO-Scintillator-Simulation
Atmospheric Muon-LYSO scintillator Interaction Simulation using Geant4

This project simulates the interaction of atmospheric muons with a LYSO scintillator using the Geant4 toolkit. The primary objective is to measure the energy deposition of muons as they pass through the scintillator. The simulation is designed for educational and research purposes, particularly in particle physics and radiation detection.
Key Features:

    Randomized Muon Direction: The muons are directed towards the scintillator with varying angles and points of interaction, simulating a more realistic experimental setup.
    LYSO Scintillator: The scintillator material, LYSO, is used for its effectiveness in radiation detection and energy resolution.
    Energy Deposition Recording: The energy lost by the muons in the scintillator is recorded and outputted to a ROOT file, facilitating detailed analysis and visualization of the results.
    Automated Multi-Run Simulation: The setup allows for running multiple simulations in sequence, with each run generating data for further analysis.




CMake Configuration (CMakeLists.txt):

    Configures the build system.
    Finds GEANT4, sets directories, and creates the executable LYSOSimulation.

Main Program (main.cc):

    Initializes the run manager and sets up detector, physics, and primary generator actions.
    Configures visualization and UI, executing vis.mac for visualization.

Visualization Macro (vis.mac):

    Sets up visualization environment, viewpoint, zoom, and particle tracks.

Detector Construction (DetectorConstruction.cc/hh):

    Defines materials and geometry.
    Constructs world and cuboid scintillator volumes with visualization attributes.

Physics List (PhysicsList.cc/hh):

    Registers decay, electromagnetic, and optical physics processes.

Primary Generator Action (PrimaryGeneratorAction.cc/hh):

    Defines a particle gun generating muons with specific energy and direction.

Run Action (RunAction.cc/hh) & Event Action (EventAction.cc/hh):

    Placeholder functions for actions at the beginning and end of runs and events.

Stepping Action (SteppingAction.cc/hh):

    Placeholder for actions at each simulation step.

Sensitive Detector (SensitiveDetector.cc/hh):

    Processes hits, records energy deposition, and calculates scintillation photons.
