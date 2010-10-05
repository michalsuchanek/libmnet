#include <mnet/UDPSocket.h>
#include <boost/bind.hpp>
#include <algorithm>
#include <assert.h>

using namespace boost::asio;

namespace mnet {

UDPSocket::UDPSocket( IOService* io, const UDPEndPoint& bindaddr, size_t inbufsize ) :
	m_io( io ),
	m_impl( io->impl() )
{
	assert( inbufsize > 0 );
	
	m_inBuf.resize( (inbufsize+7)&~7 );
	m_impl.open( ip::udp::v4(), m_err );
	m_impl.bind( bindaddr.impl(), m_err );
	
	if ( !m_err )
		startReceive();
}

UDPSocket::~UDPSocket()
{
}

void UDPSocket::addPacketListener( UDPPacketListener* listener )
{
	assert( listener != 0 );

	if ( std::find(m_listeners.begin(),m_listeners.end(),listener) == m_listeners.end() )
		m_listeners.push_back( listener );
}

void UDPSocket::removePacketListener( UDPPacketListener* listener )
{
	assert( listener != 0 );

	ListenerVec_t::iterator it = std::find( m_listeners.begin(), m_listeners.end(), listener );
	if ( it != m_listeners.end() )
		m_listeners.erase( it );
}

void UDPSocket::sendToA( const UDPEndPoint& dest, const void* data, size_t len )
{
	PacketPtr_t packet = createPacket( data, len );

	m_impl.async_send_to( buffer(*packet), dest.impl(),
		boost::bind(&UDPSocket::handleSend, this, packet,
		placeholders::error,
		placeholders::bytes_transferred) );
}

void UDPSocket::sendToS( const UDPEndPoint& dest, const void* data, size_t len )
{
	m_impl.send_to( buffer(data,len), dest.impl(), 0, m_err );
}

void UDPSocket::startReceive()
{
	m_impl.async_receive_from(
		buffer(&m_inBuf[0],m_inBuf.size()), m_inAddr.impl(),
		boost::bind(&UDPSocket::handleReceive, this,
		placeholders::error,
		placeholders::bytes_transferred) );
}

void UDPSocket::handleReceive( const boost::system::error_code& err, std::size_t bytes_transferred )
{
	if ( !err && bytes_transferred >= 1 )
	{
		// prevent buffer overrun attacks by terminating buffer with zero just in case
		if ( m_inBuf.size() <= bytes_transferred )
			m_inBuf.resize( bytes_transferred+1 );
		m_inBuf[bytes_transferred] = 0;

		for ( ListenerVec_t::iterator it = m_listeners.begin() ; it != m_listeners.end() ; ++it )
		{
			UDPPacketListener* listener = *it;
			assert( m_inBuf.size() >= bytes_transferred );
			assert( bytes_transferred > 0 );
			listener->onPacketReceived( m_inAddr, &m_inBuf[0], bytes_transferred );
		}
	}
	else
	{
		// normal: 
		// 1) WSAECONNREFUSED: connection refused, no server running
		// 2) WSAECONNRESET: no client receiving
		m_err = err;
	}

	startReceive();
}

void UDPSocket::handleSend( boost::shared_ptr<ByteBuf_t> packet, const boost::system::error_code& err, std::size_t /*bytes_transferred*/ )
{
	if ( err )
		m_err = err;

	if ( packet != 0 )
		releasePacket( packet );
}

UDPSocket::PacketPtr_t UDPSocket::createPacket( const void* data, size_t len )
{
	PacketPtr_t p;
	if ( m_freePackets.size() > 0 )
	{
		p = m_freePackets.back();
		m_freePackets.pop_back();
	}
	else
	{
		p = PacketPtr_t( new ByteBuf_t(len) );
	}

	p->resize( len );
	memcpy( &(*p)[0], data, len );
	return p;
}

void UDPSocket::releasePacket( PacketPtr_t& packet )
{
	if ( packet != 0 )
	{
		packet->clear();
		m_freePackets.push_back( packet );
		packet = PacketPtr_t();
	}
}

void UDPSocket::clearError()
{
	m_err = boost::system::error_code();
}

int UDPSocket::error( std::string* msg ) const
{
	if ( msg )
		*msg = m_err.message();
	return m_err.value();
}

UDPEndPoint UDPSocket::localEndPoint() const
{
	UDPEndPoint ep;
	ep.impl() = m_impl.local_endpoint();
	return ep;
}

} // namespace mnet

// This file is part of mnet. Copyright (C) 2010 Jani Kajala. All rights reserved.
