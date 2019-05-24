## Reproduction Scenario for NetCore Bug

#### Address "System.Net.Sockets.SocketException: Address already in use" on K8S/Linux

see https://github.com/dotnet/corefx/issues/37044


#### Overview

This solution contains

- Linux native C++ console application  

- NetCore console application  
with multi-targeting and 3 publishing targets:
  - netcore2.0
  - netcore2.2
  - netcore3.0


Instructions:

- Build Solution  
(The Linux project requires remote build setup)
- Execute all 3 publishing targets
- Copy them to a Linux machine
- Try to run all three on the Linux machine (end with CTRL-C)  
=> Should work fine
- Now run the native application
- Try to run all three netcore app versions again  
  - netcore2.0 => OK
  - netcore2.2 => SocketException (98): Address already in use
  - netcore3.0 => OK
