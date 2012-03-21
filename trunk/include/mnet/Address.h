#pragma once

#include <mnet/IOService.h>
#include <boost/asio.hpp>
#include <string>

namespace mnet {

/**
 * UDP network address.
 * @see UDPSocket
 * @ingroup asio
 */
class Address
{
public:
	/** Any net address. */
	Address();

	/** 
	 * Local host and port number. IPv4.
	 * @param port Port number
	 */
	explicit Address( int port );

	/** 
	 * Host and port/protocol. IPv4.
	 * @param host Host name, e.g. www.kajala.com or 127.0.0.1.
	 * @param port Port number, e.g. "13133", or protocol name, e.g. "http".
	 */
	Address( IOService& io, const std::string& host, const std::string& port );

	/** 
	 * Host and port/protocol. IPv4.
	 * @param host Host name, e.g. www.kajala.com or 127.0.0.1.
	 * @param port Port number, e.g. 13133, or protocol name, e.g. "http".
	 */
	Address( IOService& io, const std::string& host, int port );

	/** 
	 * Host and port/protocol. IPv4.
	 * @param hostport Host name and port number, e.g. 127.0.0.1:1233
	 */
	Address( IOService& io, const std::string& hostport );

	/** Copy by value. */
	Address( const mnet::Address& o );

	/** Releases address resources. */
	~Address();

	/** Copy by value. */
	Address&		operator=( const mnet::Address& o );

	/** Sets port associated with this end point. */
	void			setPort( int port );

	/** Compare, equal. */
	bool			operator==( const mnet::Address& o ) const;

	/** Compare, inequal. */
	bool			operator!=( const mnet::Address& o ) const;

	/** Compare, less than. */
	bool			operator<( const mnet::Address& o ) const;

	/** Returns string description of the address. */
	std::string		toString() const;

	/** Returns port associated with this end point. */
	int				port() const;

	boost::asio::ip::udp::endpoint&			impl()			{return m_impl;}

	const boost::asio::ip::udp::endpoint&	impl() const	{return m_impl;}

private:
	boost::asio::ip::udp::endpoint	m_impl;

	void			resolve( IOService& io, const std::string& host, const std::string& port );
};

} // namespace mnet

// This file is part of mnet. Copyright (C) 2010-2012 Jani Kajala. All rights reserved.
