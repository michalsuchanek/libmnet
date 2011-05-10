#include <mnet/IOService.h>
#include <mnet/UDPSocket.h>
#include <mnet/UDPEndPoint.h>

using namespace mnet;

class App : public UDPPacketListener
{
public:
	std::map<std::string,int> player_ids;

	App( UDPSocket* socket ) :
		m_socket( socket )
	{
	}

	/**
	 * Called when UDP packet received.
	 * @param remote Source network address/port.
	 * @param data Packet data received. Buffer size is guaranteed to be at least 8 bytes long even if message length is 0.
	 * @param len Length of packet in bytes.
	 */
	void onPacketReceived( const mnet::UDPEndPoint& remote, const char* data, size_t len )
	{
		printf( "Recv from %s: %s\n", remote.toString().c_str(), data );
		if ( !strcmp(data,"Hello") )
		{
			const char reply[] = "World";
			m_socket->sendToA( remote, reply, sizeof(reply) );
			printf( "Sent to %s: %s\n", remote.toString().c_str(), reply );
		}
	}

private:
	UDPSocket* m_socket;
};

int main( int argc, char* argv[] )
{
	if ( argc != 3 )
	{
		printf( "usage: <client/server> <server ip>" );
		return 1;
	}
	bool is_server = !strcmp("server",argv[1]);
	std::string server_host = argv[2];
	unsigned short port = is_server ? 8001 : 0;
	const std::string server_port = "8001";


	IOService ios;
	UDPEndPoint local_ep( port );
	UDPSocket socket( &ios, local_ep );
	printf( "Started %s at %s\n", argv[1], local_ep.toString().c_str() );

	UDPEndPoint server_ep;
	if ( !is_server )
		server_ep = UDPEndPoint( &ios, server_host, server_port );

	App app( &socket );
	socket.addPacketListener( &app );

	clock_t t0 = clock();
	for (;;)
	{
		ios.poll();

		std::string err;
		if ( socket.error(&err) )
		{
			socket.clearError();
			printf( "Error: %s\n", err.c_str() );
			Sleep( 2000 );
		}

		// client sends msg to server every second
		clock_t t1 = clock();
		if ( !is_server && t1-t0 > CLOCKS_PER_SEC )
		{
			char msg[128] = "Hello";
			socket.sendToA( server_ep, msg, sizeof(msg) );
			printf( "Sent to %s: %s\n", server_ep.toString().c_str(), msg );
			t0 = t1;
		}
	}
	return 0;
}
