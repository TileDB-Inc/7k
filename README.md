[![Teledyne Logo](images/TeledyneLogo.png)](teledynemarine.com)


# 7k
Teledyne Marine 7k protocol for marine sensor interfacing.

The protocol is described in the [DFD](DATA%20FORMAT%20DEFINITION%20-%20%207k%20Data%20Format.pdf).

## Example

C++ source code in a Microsoft Visual Studio project.

The included example is a command line application that connects as a TCP client to the sonar.
It subscribes to a couple of records, and prints out some items from the ping data.

## 7kRTT

The 7k Record Test Tool is a Windows application for testing the 7k protocol.
Connect to a system, send commands, and display records.
Read and examine .s7k log files.

# License
Copyright 2021 Teledyne RESON A/S
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.