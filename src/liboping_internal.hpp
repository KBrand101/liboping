// src/liboping_internal.cpp
// (c) 2020 Korbinian Brandler. All rights reserved.

#pragma once

#include "liboping.hpp"

namespace oping
{
	namespace internal
	{
		/**
		 * Set errmsg of pingobj to respective message
		 * 
		 * @param obj Pointer to current pingobj
		 * @param function The function in which the error occured
		 * @param msg The error message to print
		 */
		void setErrorMsg(std::shared_ptr<pingobj> obj, const std::string &function, const std::string &msg);

		/**
		 * Open a new Linux/Unix socket
		 * 
		 * @param obj Pointer to current pingobj
		 * @param addrfam The ip address family to use (ipv4 or ipv6)
		 * @return file descriptor for new socket
		 */
		int openSocket(std::shared_ptr<pingobj> obj, const int &addrfam);

	}	// namespace internal

}	// namespace oping