SimSCon
=======

An advanced simulator for dynamic server consolidation algorithms

Assumptions
-----------
* All numbering begins from 0, e.g. numbering of vms begins from 0 and goes till (vm_number -1)

Notations and Abbreviations
---------------------------
- pm = physical machine
- vm = virtual machine

Input File
----------
* number of virtual machines
* number of phases
* arrival rate for each pm
* service rate for each vm

See TODO file for examples.

Output
------
Prints the trace of the events and generates various graphs.

How to Run
----------
Current Working Dir: **simscon/**
```
make clean
make
./bin/sim < input
```
