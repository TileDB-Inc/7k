# 7k
Teledyne Marine 7k protocol for marine sensor interfacing.

The protocol is described in the [DFD](DATA%20FORMAT%20DEFINITION%20-%20%207k%20Data%20Format.pdf).

## Example ##

C++ source code in a Microsoft Visual Studio project.

The included example is a command line application that connects as a TCP client to the sonar.
It subscribes to a couple of records, and prints out some items from the ping data.
