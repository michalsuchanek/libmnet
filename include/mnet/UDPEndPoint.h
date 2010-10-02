#pragma once

#include <mnet/mnet_pp.h>
#include <mnet/IOService.h>
#include <boost/asio.hpp>
#include <string>

namespace mnet {

/**
 * UDP network address.
 * @see UDPSocket
 * @ingroup asio
 */
class UDPEndPoint
{
public:
	/** Any net address. */
	UDPEndPoint();

	/** 
	 * Local host and port number. IPv4.
	 * @param port Port number
	 */
	explicit UDPEndPoint( int port );

	/** 
	 * Host and port/protocol. IPv4.
	 * @param host Host name, e.g. www.kajala.com or 127.0.0.1.
	 * @param port Port number, e.g. "13133", or protocol name, e.g. "http".
	 */
	UDPEndPoint( IOService* io, const std::string& host, const std::string& port );

	/** 
	 * Host and port/protocol. IPv4.
	 * @param hostport Host name and port number, e.g. 127.0.0.1:1233
	 */
	UDPEndPoint( IOService* io, const std::string& hostport );

	/** Copy by value. */
	UDPEndPoint( const mnet::UDPEndPoint& o );

	/** Releases address resources. */
	~UDPEndPoint();

	/** Copy by value. */
	UDPEndPoint&	operator=( const mnet::UDPEndPoint& o );

	/** Sets port associated with this end point. */
	void			setPort( int port );

	/** Compare, equal. */
	bool			operator==( const mnet::UDPEndPoint& o ) const;

	/** Compare, inequal. */
	bool			operator!=( const mnet::UDPEndPoint& o ) const;

	/** Compare, less than. */
	bool			operator<( const mnet::UDPEndPoint& o ) const;

	/** Returns string description of the address. */
	std::string		toString() const;

	/** Returns port associated with this end point. */
	int				port() const;

	boost::asio::ip::udp::endpoint&			impl()			{return m_impl;}

	const boost::asio::ip::udp::endpoint&	impl() const	{return m_impl;}

private:
	boost::asio::ip::udp::endpoint	m_impl;

	void			resolve( IOService* io, const std::string& host, const std::string& port );
};

} // namespace mnet

// This file is part of mnet. Copyright (C) 2010 Jani Kajala. All rights reserved.
