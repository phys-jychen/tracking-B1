# Geant4 Example B1 for Tracking

## Description
This is a simple Geant4 program for particle tracking modified from Example B1 (basic) provided by Geant4 toolkit.

For (possible) future data analysis, the momentum of the incident particle is stored in the output ROOT file, where the momentum value is directly obtained from `G4Step`.

## Geometry
The tracker consists of 7 layers of silicon, separated 30 centimetres apart along $z$ axis, each with size 200 × 100 × 0.1 mm<sup>3</sup>.