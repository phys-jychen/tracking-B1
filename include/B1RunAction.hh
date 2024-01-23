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
/// \file B1RunAction.hh
/// \brief Definition of the B1RunAction class

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include <vector>

#include "g4root.hh"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

using namespace std;

class G4Run;
class TFile;
class TTree;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class B1RunAction : public G4UserRunAction
{
public:
    B1RunAction();
    virtual ~B1RunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep);
    void AddHit(G4double x, G4double y, G4double z, G4double t, G4double p, G4double edep);
    void fill();

private:
    G4Accumulable<G4double> fEdep;
    G4Accumulable<G4double> fEdep2;
    vector<G4double> fX;
    vector<G4double> fY;
    vector<G4double> fZ;
    vector<G4double> fTime;
    vector<G4double> fp;
    vector<G4double> fE;

    TString filename = "";
    TFile* file = nullptr;
    TTree* tree = nullptr;
};

#endif

