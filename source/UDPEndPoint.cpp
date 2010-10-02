#include <mnet/UDPEndPoint.h>

using boost::asio::ip::udp;

namespace mnet {

UDPEndPoint::UDPEndPoint() :
	m_impl( udp::v4(), 0 )
{
}

UDPEndPoint::UDPEndPoint( int port ) :
	m_impl( udp::v4(), (unsigned short)port )
{
	assert( port >= 0 && port < 65536 );
}

UDPEndPoint::UDPEndPoint( IOService* io, const std::string& host, const std::string& port )
{
	resolve( io, host, port );
}

UDPEndPoint::UDPEndPoint( IOService* io, const std::string& hostport )
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

UDPEndPoint::UDPEndPoint( const UDPEndPoint& o ) :
	m_impl( o.m_impl )
{
}

UDPEndPoint::~UDPEndPoint()
{
}

UDPEndPoint& UDPEndPoint::operator=( const UDPEndPoint& o )
{
	m_impl = o.m_impl;
	return *this;
}

std::string UDPEndPoint::toString() const
{
	char buf[256];
	sprintf_s( buf, sizeof(buf), "%s:%d", m_impl.address().to_string().c_str(), (int)m_impl.port() );
	return buf;
}

bool UDPEndPoint::operator==( const UDPEndPoint& o ) const
{
	return m_impl == o.m_impl;
}

bool UDPEndPoint::operator!=( const UDPEndPoint& o ) const
{
	return m_impl != o.m_impl;
}

bool UDPEndPoint::operator<( const UDPEndPoint& o ) const
{
	return m_impl < o.m_impl;
}

void UDPEndPoint::resolve( IOService* io, const std::string& host, const std::string& port )
{
    udp::resolver resolver( io->impl() );
    udp::resolver::query query( udp::v4(), host.c_str(), port.c_str() );
    m_impl = *resolver.resolve( query );
}

void UDPEndPoint::setPort( int port )
{
	assert( port >= 0 && port < 65536 );
	m_impl.port( (unsigned short)port );
}

int UDPEndPoint::port() const
{
	return m_impl.port();
}

} // namespace mnet

// This file is part of mnet. Copyright (C) 2010 Jani Kajala. All rights reserved.
