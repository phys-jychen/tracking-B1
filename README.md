# Geant4 Example B1 for Tracking

## Description
This is a simple Geant4 program for particle tracking modified from Example B1 (basic), and is an assignment for the [Dark Photon Software Workshop](https://indico-tdli.sjtu.edu.cn/event/2140/) (19–21 January 2024).

For (possible) future data analysis, the hit information are stored, including position, energy deposition, and momentum, where the momentum is calculated in natural units ($c = 1$), using formula

$$
p = \frac{mv}{\sqrt{1 - v^2}}.
$$

For hit information, the units are default: position in mm, time in ns, and momentum and energy in MeV.

## Geometry
The tracker consists of 7 layers of silicon, separated 30 centimetres apart along $z$ axis, each with size 200 × 100 × 0.1 mm<sup>3</sup>.

## Environment Set-up
This project requires CMake version >= 2.6. If you are working on the cluster of INPAC, IHEP, etc., the environment can be easily set up by executing
```shell
source /cvmfs/sft.cern.ch/lcg/views/LCG_97rc4python3/x86_64-centos7-gcc9-opt/setup.sh
```

Then, the environment with CMake 3.14.3, Geant4-10.06-patch-01, and ROOT 6.20/00 is configured. As long as no compilation errors are raised and the CMake version requirement is met, other versions on the LCG are also acceptable (mind your version of Geant4!). :stuck_out_tongue:

## Installation & Compilation
Having set up the environment, this project can be cloned from GitHub and compiled normally:
```shell
git clone git@github.com:phys-jychen/tracking-B1.git
cd tracking-B1
mkdir build
cd build
cmake ..
make -j100    # Just do it!
source setup.sh
```

## Usage
In command line, and in the `build` directory, running
```shell
./exampleB1
```
leads you to the UI, where the default particle is 100-MeV proton. The particle source can also be easily set through the UI.

It is also recommended to prepare a `.mac` macro (e.g. `run.mac`) and execute through
```shell
./exampleB1 run.mac
```
if you need to generate more MC samples and save data for future analysis.

Have fun! :relaxed: