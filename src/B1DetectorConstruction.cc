//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
        : G4VUserDetectorConstruction(),
          fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();

    // Envelope parameters
    G4double env_sizeXY = 40.0 * cm, env_sizeZ = 2.0 * m;
    G4Material* env_mat = nist->FindOrBuildMaterial("G4_Galactic");

    // Option to switch on/off checking of volumes overlaps
    G4bool checkOverlaps = true;

    // World
    G4double world_sizeXY = 1.2 * env_sizeXY;
    G4double world_sizeZ  = 1.2 * env_sizeZ;
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

    G4Box* solidWorld = new G4Box("World",                                                        // Name
                                  0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);     // Size

    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,    // Solid
                                                      world_mat,     // Material
                                                      "World");      // Name

    G4VPhysicalVolume* physWorld = new G4PVPlacement(0,                  // No rotation
                                                     G4ThreeVector(),    // At (0,0,0)
                                                     logicWorld,         // Logical volume
                                                     "World",            // Name
                                                     0,                  // Mother volume
                                                     false,              // No boolean operation
                                                     0,                  // Copy number
                                                     checkOverlaps);     // Overlaps checking

    // Envelope
    G4Box* solidEnv = new G4Box("Envelope",                                              // Name
                                0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ);    // Size

    G4LogicalVolume* logicEnv = new G4LogicalVolume(solidEnv,       // Solid
                                                    env_mat,        // Material
                                                    "Envelope");    // Name

    new G4PVPlacement(0,                  // No rotation
                      G4ThreeVector(),    // At (0,0,0)
                      logicEnv,           // Logical volume
                      "Envelope",         // Name
                      logicWorld,         // Mother volume
                      false,              // No boolean operation
                      0,                  // Copy number
                      checkOverlaps);     // Overlaps checking

    // Silicon tracker
    G4Material* Si = nist->FindOrBuildMaterial("G4_Si");
    const G4double SiLength = 20.0 * cm;
    const G4double SiWidth = 10.0 * cm;
    const G4double SiThick = 0.1 * mm;
    const G4int nLayers = 7;
    const G4double gap = 30.0 * cm;
    G4Box* solidSi = new G4Box("Si",                                             // Name
                               0.5 * SiLength, 0.5 * SiWidth, 0.5 * SiThick);    // Size
    G4LogicalVolume* logicSi = new G4LogicalVolume(solidSi,    // Solid
                                                   Si,         // Material
                                                   "Si");      // Name
    for (G4int i = 0; i < nLayers; i++)
        new G4PVPlacement(0,                 // No rotation
                          G4ThreeVector(0, 0, (i - 3) * gap),
                          logicSi,           // Logical volume
                          "Si",              // Name
                          logicEnv,          // Mother volume
                          false,             // No boolean operation
                          i,                 // Copy number
                          checkOverlaps);    // Overlaps checking

    // Set silicon tracker as scoring volume
    fScoringVolume = logicSi;

    return physWorld;
}