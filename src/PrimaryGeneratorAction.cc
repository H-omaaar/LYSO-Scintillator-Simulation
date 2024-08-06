#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh" // Include the header for random number generation

PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "mu+";
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(4*GeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    // Randomize the starting position
    G4double xPos = (G4UniformRand() - 0.5) * 20 * cm; // Random position in a range, adjust as needed
    G4double yPos = (G4UniformRand() - 0.5) * 20 * cm; // Random position in a range, adjust as needed
    G4double zPos = -10 * cm; // Fixed z position, change if needed

    fParticleGun->SetParticlePosition(G4ThreeVector(xPos, yPos, zPos));

    // Randomize the direction
    G4double theta = G4UniformRand() * CLHEP::pi; // Random angle between 0 and pi
    G4double phi = G4UniformRand() * 2 * CLHEP::pi; // Random angle between 0 and 2pi

    G4double xDir = std::sin(theta) * std::cos(phi);
    G4double yDir = std::sin(theta) * std::sin(phi);
    G4double zDir = std::cos(theta);

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(xDir, yDir, zDir));
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
