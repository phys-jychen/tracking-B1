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

#include <cassert>
#include "B1EventAction.hh"
#include "B1RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::B1EventAction(B1RunAction* runAction)
        : G4UserEventAction(),
          fRunAction(runAction),
          fX({}),
          fY({}),
          fZ({}),
          fTime({}),
          fp({}),
          fE({})
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event*)
{
    fX.clear();
    fY.clear();
    fZ.clear();
    fTime.clear();
    fp.clear();
    fE.clear();
    fRunAction->Hit_X.clear();
    fRunAction->Hit_Y.clear();
    fRunAction->Hit_Z.clear();
    fRunAction->Time_Diff.clear();
    fRunAction->Hit_p.clear();
    fRunAction->Hit_E.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event*)
{
    assert(fX.size() == fY.size());
    assert(fX.size() == fZ.size());
    assert(fX.size() == fTime.size());
    assert(fX.size() == fp.size());
    assert(fX.size() == fE.size());

    for (G4int i = 0; i < (G4int) fX.size(); i++)
        fRunAction->AddHit(fX.at(i), fY.at(i), fZ.at(i), fTime.at(i), fp.at(i), fE.at(i));

    assert(fRunAction->Hit_X.size() == fRunAction->Hit_Y.size());
    assert(fRunAction->Hit_X.size() == fRunAction->Hit_Z.size());
    assert(fRunAction->Hit_X.size() == fRunAction->Time_Diff.size());
    assert(fRunAction->Hit_X.size() == fRunAction->Hit_E.size());
    assert(fRunAction->Hit_X.size() == fRunAction->Hit_p.size());

    fRunAction->tree->Fill();

    // Printing hit information --- for debugging
    /*
    G4cout << "X [mm]: " << endl;
    for (G4double i : fX)
        G4cout << i << "  ";
    G4cout << G4endl;
    G4cout << "Y [mm]: " << endl;
    for (G4double i : fY)
        G4cout << i << "  ";
    G4cout << G4endl;
    G4cout << "Z [mm]: " << endl;
    for (G4double i : fZ)
        G4cout << i << "  ";
    G4cout << G4endl;
    G4cout << "Time difference [ns]: " << endl;
    for (G4double i : fTime)
        G4cout << i << "  ";
    G4cout << G4endl;
    G4cout << "Momentum [MeV]: " << endl;
    for (G4double i : fp)
        G4cout << i << "  ";
    G4cout << G4endl;
    G4cout << "Energy [MeV]: " << endl;
    for (G4double i : fE)
        G4cout << i << "  ";
    G4cout << G4endl << G4endl;
     */
}