// run: "client-server -server" (for server) and client-server for client
#include <mnet/mnet.h>

const char SERVER_ADDR[] = "localhost:12000";

using namespace mnet;

class Ping : public PacketListener
{
public:
	IOService ios;
	UDPSocket socket;

	Ping( bool is_server ) :
		socket( ios, is_server ? Address(ios,SERVER_ADDR) : Address() )
	{
		if (is_server)
		{
			socket.addPacketListener( this );
			for (;;)
				ios.poll();
		}
		else
		{
			char msg[128] = "Hello";
			socket.send( Address(ios,SERVER_ADDR), msg, strlen(msg)+1 );
		}
	}

	void onPacketReceived( const Address& remote, const char* data, size_t len )
	{
		printf( "Received: %s\n", data );
	}
};

int main( int argc, char* argv[] )
{
	Ping app( argc > 1 && !strcmp(argv[1],"-server") );
	return 0;
}
