#include <mnet/Address.h>

#ifdef _MSC_VER
#pragma warning( disable : 4996 ) // sprintf
#endif

using boost::asio::ip::udp;

namespace mnet {

Address::Address() :
	m_impl( udp::v4(), 0 )
{
}

Address::Address( int port ) :
	m_impl( udp::v4(), (unsigned short)port )
{
	assert( port >= 0 && port < 65536 );
}

Address::Address( IOService& io, const std::string& host, const std::string& port )
{
	resolve( io, host, port );
}

Address::Address( IOService& io, const std::string& host, int port )
{
	char buf[32];
	sprintf( buf, "%d", port );
	resolve( io, host, buf );
}

Address::Address( IOService& io, const std::string& hostport )
{
	std::string port, host;
	size_t i = hostport.find(':');
	if ( i == std::string::npos )
	{
		host = hostport;
		port = "0";
	}
	else
	{
		host = hostport.substr(0,i);
		port = hostport.substr(i+1);
	}

	resolve( io, host, port );
}

Address::Address( const Address& o ) :
	m_impl( o.m_impl )
{
}

Address::~Address()
{
}

Address& Address::operator=( const Address& o )
{
	m_impl = o.m_impl;
	return *this;
}

std::string Address::toString() const
{
	char buf[256];
	sprintf_s( buf, sizeof(buf), "%s:%d", m_impl.address().to_string().c_str(), (int)m_impl.port() );
	return buf;
}

bool Address::operator==( const Address& o ) const
{
	return m_impl == o.m_impl;
}

bool Address::operator!=( const Address& o ) const
{
	return m_impl != o.m_impl;
}

bool Address::operator<( const Address& o ) const
{
	return m_impl < o.m_impl;
}

void Address::resolve( IOService& io, const std::string& host, const std::string& port )
{
    udp::resolver resolver( io.impl() );
    udp::resolver::query query( udp::v4(), host.c_str(), port.c_str() );
    m_impl = *resolver.resolve( query );
}

void Address::setPort( int port )
{
	assert( port >= 0 && port < 65536 );
	m_impl.port( (unsigned short)port );
}

int Address::port() const
{
	return m_impl.port();
}

} // namespace mnet

// This file is part of mnet. Copyright (C) 2010-2012 Jani Kajala. All rights reserved.
