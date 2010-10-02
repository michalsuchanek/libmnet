#pragma once

#include <mnet/mnet_pp.h>
#include <mnet/IOService.h>
#include <mnet/UDPEndPoint.h>
#include <mnet/UDPPacketListener.h>
#include <boost/asio.hpp>
#include <vector>

namespace mnet {

/**
 * Datagram network socket.
 * @ingroup asio
 */
class UDPSocket
{
public:
	/**
	 * Creates UDP socket bound to specified network address.
	 * @param io Async io service provider.
	 * @param binaddr Address to bind socket to.
	 * @param inbufsize Input buffer size.
	 */
	UDPSocket( IOService* io, const mnet::UDPEndPoint& bindaddr, size_t inbufsize=32768 );

	/** Releases socket resources. */
	~UDPSocket();

	/**
	 * Adds a listener to this socket.
	 * A listener will receive notification when a packet is received to this socket.
	 */
	void	addPacketListener( mnet::UDPPacketListener* listener );

	/**
	 * Removes a listener from this socket.
	 * @see addPacketListener
	 */
	void	removePacketListener( mnet::UDPPacketListener* listener );

	/**
	 * Asyncronous send to specified address.
	 * @param dest Destination network address.
	 * @param data Packet data to send.
	 * @param len Length of packet in bytes.
	 */
	void	sendToA( const mnet::UDPEndPoint& dest, const void* data, size_t len );

	/**
	 * Syncronous send to specified address.
	 * @param dest Destination network address.
	 * @param data Packet data to send.
	 * @param len Length of packet in bytes.
	 */
	void	sendToS( const mnet::UDPEndPoint& dest, const void* data, size_t len );

	/**
	 * Clears/resets error code state.
	 */
	void	clearError();

	/** 
	 * Error code from the last operation. 0 if no error. 
	 * See BSD Sockets or Winsock API documentation for the error codes.
	 * @param msg Description of error code
	 */
	int		error( std::string* msg=0 ) const;

	/**
	 * Returns local end point of the socket.
	 */
	mnet::UDPEndPoint	localEndPoint() const;

private:
	typedef std::vector<char>					ByteBuf_t;
	typedef std::vector<UDPPacketListener*>		ListenerVec_t;
	typedef boost::shared_ptr<ByteBuf_t>		PacketPtr_t;

	IOService*							m_io;
	boost::asio::ip::udp::socket		m_impl;
	ListenerVec_t						m_listeners;
	ByteBuf_t							m_inBuf;
	UDPEndPoint							m_inAddr;
	std::vector<PacketPtr_t>			m_freePackets;
	boost::system::error_code			m_err;

	void		startReceive();
	void		handleReceive( const boost::system::error_code& error, std::size_t bytes_transferred );
	void		handleSend( boost::shared_ptr<ByteBuf_t> packet, const boost::system::error_code& error, std::size_t bytes_transferred );
	PacketPtr_t	createPacket( const void* data, size_t len );
	void		releasePacket( PacketPtr_t& packet );

	UDPSocket( const UDPSocket& );
	UDPSocket& operator=( const UDPSocket& );
};


} // namespace mnet

// This file is part of mnet. Copyright (C) 2010 Jani Kajala. All rights reserved.
