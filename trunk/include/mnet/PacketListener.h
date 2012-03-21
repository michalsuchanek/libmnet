#pragma once

namespace mnet {

class Address;

/**
 * Receives notifications about received UDP data packets.
 * @ingroup asio
 */
class PacketListener
{
public:
	/**
	 * Called when UDP packet received.
	 * @param remote Source network address.
	 * @param data Packet data received. Buffer size is guaranteed to be at least 8 bytes long even if message length is 0.
	 * @param len Length of packet in bytes.
	 */
	virtual void onPacketReceived( const mnet::Address& remote, const char* data, size_t len ) = 0;
};


} // namespace mnet

// This file is part of mnet. Copyright (C) 2010-2012 Jani Kajala. All rights reserved.
