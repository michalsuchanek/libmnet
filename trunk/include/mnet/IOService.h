#pragma once

#include <mnet/mnet_pp.h>
#include <boost/asio.hpp>

namespace mnet {

/**
 * Provides support for asynchronous IO services.
 * @see UDPSocket
 * @ingroup asio
 */
class IOService
{
public:
	IOService();

	~IOService();

	/** 
	 * Polls and processes new IO events. Returns after no pending IO events. 
	 */
	void	poll();

	boost::asio::io_service&	impl()			{return m_impl;}

private:
	boost::asio::io_service		m_impl;
	boost::system::error_code	m_err;

	IOService( const IOService& );
	IOService& operator=( const IOService& );
};


} // namespace mnet

// This file is part of mnet. Copyright (C) 2010 Jani Kajala. All rights reserved.
