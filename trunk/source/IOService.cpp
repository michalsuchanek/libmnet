#include <mnet/IOService.h>

namespace mnet {

IOService::IOService()
{
}

IOService::~IOService()
{
}

void IOService::poll()
{
	m_impl.poll( m_err );
}

} // namespace mnet

// This file is part of mnet. Copyright (C) 2010-2012 Jani Kajala. All rights reserved.
