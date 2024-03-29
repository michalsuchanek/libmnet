mnet ver. 0.8.0
********************

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

* Windows Vista 64bit / Visual Studio 2010

* boost (1.41 at the time of this)


Install (Visual Studio)
----------------------------------------

0) Download and build Boost. For example, compiling Boost on VS2010:
   0.0) unpack boost sources
   0.1) bootstrap.bat
   0.2) (for x86) bjam --toolset=msvc-10.0 --stagedir=stage-x86 --build-type=complete stage
		(for x64) bjam --toolset=msvc-10.0 --stagedir=stage-x64 --build-type=complete architecture=x86 address-model=64

1) Just add mnet project to your solution, set your project as dependent on mnet

2) Make sure mnet/include is on include path

3) Build & run


Changes
--------

v0.8.0 (2014-04-02):
* added VS2012 projects

v0.7.0 (2012-03-21):
* simplified function naming

v0.6.0 (2011-04-14):
* simplified docs
* vs2010 support

v0.5.2 (2010-10-21):
* lib/vs2008 as output path

v0.5.1 (2010-10-05):
* Eliminated libs from the package

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
