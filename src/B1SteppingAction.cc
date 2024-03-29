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
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction *eventAction)
        : G4UserSteppingAction(),
          fEventAction(eventAction),
          fScoringVolume(0) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step *step) {
    if (!fScoringVolume) {
        const B1DetectorConstruction *detectorConstruction
                = static_cast<const B1DetectorConstruction *>
                (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        fScoringVolume = detectorConstruction->GetScoringVolume();
    }

    // get volume of the current step
    G4LogicalVolume *volume
            = step->GetPreStepPoint()->GetTouchableHandle()
                    ->GetVolume()->GetLogicalVolume();

    // check if we are in scoring volume
    if (volume != fScoringVolume) return;

    // Collect hit information
    G4StepPoint* stepInfo = step->GetPostStepPoint();
    G4ThreeVector positionStep = stepInfo->GetPosition();
    G4double xStep = positionStep.getX();
    G4double yStep = positionStep.getY();
    G4double zStep = positionStep.getZ();
    G4double timeStep = step->GetDeltaTime();
    G4double edepStep = step->GetTotalEnergyDeposit();
//    G4double timeStep = stepInfo->GetGlobalTime();
    // Truth momentum:
//    G4double momentum = stepInfo->GetMomentum().mag();

    // Calculate momentum
    const G4double c = 299.792458 * mm / ns;
    const G4double mass = 938.272088 * MeV;

    G4double distanceStep = step->GetDeltaPosition().mag();
    G4double speed = distanceStep / timeStep / c;
    G4double momentum = mass * speed / TMath::Sqrt(1 - TMath::Power(speed, 2));
    fEventAction->AddHit(xStep, yStep, zStep, timeStep, momentum, edepStep);
}