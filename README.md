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
* revenue for each vm
* penalty for each pm
* arrival rate in each phase for each pm
* service rate for each vm

See TODO file for examples.

Output
------
Prints the trace of the events and generates various graphs.

Documentation
-------------------------
- [Presentation](https://docs.google.com/presentation/d/1L_KD6rvMNvUa_kO9ImEZfsS1mIJ2mFQC5sRhV7p4ZGs)
- [Results](https://docs.google.com/spreadsheet/ccc?key=0Aoq3-tdSgQ83dDNmSFplZ1VON3IxSzJWTS1Wclh1VUE)

How to Run
----------
Modify `Makefile` appropriately to link to policy class. You can use http://github.com/mangalaman93/simcon
Current Working Dir: **simscon/**
```
make clean
make
./bin/sim < input
```
