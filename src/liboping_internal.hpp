// src/liboping_internal.cpp
// (c) 2020 Korbinian Brandler. All rights reserved.

#pragma once

#include "liboping.hpp"

#define DEFAULT_TIMEOUT 1.0
#define DEFAULT_TTL 255
#define DEFAULT_AF AF_UNSPEC

namespace oping
{
	struct pinghost
	{
	};	 // pinghost

	struct pingobj
	{
		double timeout;
		int	   ttl;
		int	   addrfamily;

		std::string			  errmsg;
		std::vector<pinghost> table;
	};	 // pingobj

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

		int setQos(std::shared_ptr<pingobj> obj);

		int setTimeout(std::shared_ptr<pingobj> obj);

		int setTTL(std::shared_ptr<pingobj> obj);

		int setAF(std::shared_ptr<pingobj> obj);

	}	// namespace internal

}	// namespace oping