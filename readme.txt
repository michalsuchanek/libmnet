mnet ver. 0.5.0
********************'

Simple but robust networking library with UDP async sockets support.

Simple but robust networking library with UDP sockets support.
Underlying implementation uses Boost ASIO library in implementation.
Why would I use this and not use Boost ASIO directly?
Ease of use. mnet provides greatly simplified UDP async UDP sockets usage.

Licensing: mnet code is licensed under BSD/MIT, so as free/liberal as it gets.


Documentation
--------------

"documentation\mnet.chm" contains the HTML Help reference manual.


Compatibility
------------

Otherwise code is just standard C++, but Boost C++ install is required and there
must be BOOST environment variable pointing to the root of the Boost install.

Primary development environment:

* Windows Vista 64bit / Visual Studio 2008

* boost_1_44_0


Install (Visual Studio 2008)
----------------------------------------

0) Install Boost C++ and build it. Then define BOOST environment variable like this:
   (Windows: My Computer -> Properties -> Advanced -> Environment Variables)
   BOOST=C:\Users\Jani\Documents\boost_1_44_0

1) Install mnet library e.g. to "c:\mnet"

2) Define MNET environment variable to point to c:\mnet
   (Windows: My Computer -> Properties -> Advanced -> Environment Variables)
   Restart Visual Studio.

3) Start mnet\build\vs2008\mnet\mnet.sln and re-build all libraries
   (strictly you don't need to do this, but this is good practice since e.g. you might have different boost libs)

4) Add "$(MNET)\include\" directory to your #include path: 
  Can be done from menu Tools -> Projects and Solutions -> VC++ Directories -> 
  Show directories for -> Include files. Then add "$(MNET)\include\" to the list.


Usage in your project (Visual Studio 2008)
-------------------------------------------

0) See Install first

1) Add the mnet project file to your Solution, e.g. from "c:\mnet\build\vs2008\mnet\mnet.vcproj"

After that you can use the library, for example, by including in your code 
#include <mnet/UDPSocket.h>


Version Control (Subversion)
---------------------------

Hostname: ?????
Port: 443
Protocol: HTTPS
Repository Path: /svnroot/mnet


Changes
--------

v0.5.0 (2010-10-01):
* Initial public release


Contact
--------

Jani Kajala
kajala (at) gmail.com


License (MIT/BSD Compatible License)
-------------------------------------

Copyright (C) 2010 Jani Kajala

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation 
files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, 
publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
THE USE OR OTHER DEALINGS IN THE SOFTWARE.
