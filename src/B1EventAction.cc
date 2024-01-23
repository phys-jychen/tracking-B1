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
    fp.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event*)
{
    // TODO: Modify data storage --- do not merge the vectors
    assert(fX.size() == fY.size());
    assert(fX.size() == fZ.size());
    assert(fX.size() == fTime.size());
    assert(fX.size() == fp.size());

    fRunAction->AddEdep(fEdep);
    for (G4int i = 0; i < (G4int) fX.size(); i++)
        fRunAction->AddPositionTimeMomentum(fX.at(i), fY.at(i), fZ.at(i), fTime.at(i), fp.at(i));

    fRunAction->fill();

    /*
    G4cout << "X [mm]: " << endl;
    for (G4int i = 0; i < (G4int) fX.size(); i++)
        G4cout << fX.at(i) << "  ";
    G4cout << G4endl;
    G4cout << "Y [mm]: " << endl;
    for (G4int i = 0; i < (G4int) fY.size(); i++)
        G4cout << fY.at(i) << "  ";
    G4cout << G4endl;
    G4cout << "Z [mm]: " << endl;
    for (G4int i = 0; i < (G4int) fZ.size(); i++)
        G4cout << fZ.at(i) << "  ";
    G4cout << G4endl;
    G4cout << "Global time [ns]: " << endl;
    for (G4int i = 0; i < (G4int) fTime.size(); i++)
        G4cout << fTime.at(i) << "  ";
    G4cout << G4endl;
    G4cout << "Momentum [MeV]: " << endl;
    for (G4int i = 0; i < (G4int) fp.size(); i++)
        G4cout << fp.at(i) << "  ";
    G4cout << G4endl << G4endl;
     */
}