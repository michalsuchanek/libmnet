#pragma once

/**
 * @defgroup mnet Simple but robust networking library with UDP sockets support.
 * 
 * Simple but robust networking library with UDP sockets support.
 * Underlying implementation uses Boost ASIO library in implementation.
 * Why would I use this and not use Boost ASIO directly?
 * Ease of use. mnet provides greatly simplified UDP async UDP sockets usage.
 *
 * Author: Jani Kajala (kajala@gmail.com)
 */

#include <mnet/mnet_pp.h>
#include <mnet/IOService.h>
#include <mnet/Address.h>
#include <mnet/PacketListener.h>
#include <mnet/UDPSocket.h>

// This file is part of 'mnet' C++ library. Copyright (C) 2010-2012 Jani Kajala (kajala@gmail.com).
