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
/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include "B1EventAction.hh"
#include "B1RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::B1EventAction(B1RunAction* runAction)
        : G4UserEventAction(),
          fRunAction(runAction),
          fEdep(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
    fX.clear();
    fY.clear();
    fZ.clear();
    fTime.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event*)
{
    const G4double c = 299.792458 * mm / ns;
    const G4double mass = 938.272088 * MeV;
    // accumulate statistics in run action
    fRunAction->AddEdep(fEdep);
    vector<G4double> p = {};
    for (G4int i = 0; i < (G4int) fX.size(); i++)
    {
        G4double speed = TMath::Sqrt(TMath::Power(fX.at(i), 2) + TMath::Power(fY.at(i), 2) + TMath::Power(fZ.at(i), 2)) / fTime.at(i) / c;
        G4double momentum = mass * speed / TMath::Sqrt(1 - TMath::Power(speed, 2));
        p.emplace_back(momentum);
    }

    G4cout << "X: " << endl;
    for (G4int i = 0; i < (G4int) fX.size(); i++)
        G4cout << fX.at(i) << "  ";
    G4cout << G4endl;
    G4cout << "Y: " << endl;
    for (G4int i = 0; i < (G4int) fY.size(); i++)
        G4cout << fY.at(i) << "  ";
    G4cout << G4endl;
    G4cout << "Z: " << endl;
    for (G4int i = 0; i < (G4int) fZ.size(); i++)
        G4cout << fZ.at(i) << "  ";
    G4cout << G4endl;
    G4cout << "Time: " << endl;
    for (G4int i = 0; i < (G4int) fTime.size(); i++)
        G4cout << fTime.at(i) << "  ";
    G4cout << G4endl;
    G4cout << "Momentum: " << endl;
    for (G4int i = 0; i < (G4int) p.size(); i++)
        G4cout << p.at(i) << "  ";
    G4cout << G4endl;
}