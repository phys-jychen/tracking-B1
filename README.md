# Geant4 Example B1 for Tracking

## Description
This is a simple Geant4 program for particle tracking modified from Example B1 (basic), and is an assignment for the [Dark Photon Software Workshop](https://indico-tdli.sjtu.edu.cn/event/2140/) (19–21 January 2024).

For (possible) future data analysis, the hit information are stored, including position, energy deposition, and momentum, where the momentum is calculated in natural units ($c = 1$), using formula
$$
p = \frac{mv}{\sqrt{1 - v^2}}.
$$
For  hit information, the units are default: position in mm, time in ns, and momentum and energy in MeV.

## Geometry
The tracker consists of 7 layers of silicon, separated 30 centimetres apart along $z$ axis, each with size 200 × 100 × 0.1 mm<sup>3</sup>.