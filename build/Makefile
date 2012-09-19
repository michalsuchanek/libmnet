INC=../include

mnet.a : ../source/Address.cpp ../source/IOService.cpp ../source/UDPSocket.cpp
	g++ -I $(INC) -c -o Address.o Address.cpp
	g++ -I $(INC) -c -o IOService.o IOService.cpp
	g++ -I $(INC) -c -o UDPSocket.o UDPSocket.cpp
	ar rcs mnet.a UDPSocket.o IOService.o IOService.o

	