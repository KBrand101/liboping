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
		sockaddr_storage *addr;
		socklen_t		  addrlen;
		int				  addrfamily;
		timeval			  timer;
	};	 // pinghost

	struct pingobj
	{
		uint8_t qos;
		double	timeout;
		int		ttl;
		int		addrfamily;

		int fd4;   // socket file descriptor for ipv4
		int fd6;   // socket file descriptor for ipv6

		std::string			  errmsg;
		std::vector<pinghost> table;
	};	 // pingobj

	namespace internal
	{
		std::shared_ptr<pinghost> construct_ph();

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

		/**
		 * Set qos of pingobj to given qos
		 * 
		 * @param obj Pointer to current pingobj
		 * @param qos The qos to set. See netinet/ip.h for details/values
		 * @return 0 if everything is ok
		 * @return -1 if an error occurs (see oping::getError() for details)
		 */
		int setQos(std::shared_ptr<pingobj> obj, const uint8_t &qos);

		/**
		 * Set timeout of pingobj to given timeout
		 * 
		 * @param obj Pointer to current pingobj
		 * @param timeout The timeout to set.
		 * @return 0 if everything is ok
		 * @return -1 if an error occurs (see oping::getError() for details)
		 */
		int setTimeout(std::shared_ptr<pingobj> obj, const double &timeout);

		/**
		 * Set ttl of pingobj to given ttl
		 * 
		 * @param obj Pointer to current pingobj
		 * @param ttl The ttl to set
		 * @return 0 if everything is ok
		 * @return -1 if an error occurs (see oping::getError() for details)
		 */
		int setTTL(std::shared_ptr<pingobj> obj, const int &ttl);

		/**
		 * Set addrfamily of pingobj to given addrfam
		 * 
		 * @param obj Pointer to current pingobj
		 * @param addrfam The ip address family to use (e.g. unspecified, ipv4 or ipv6)
		 * @return 0 if everything is ok
		 * @return -1 if addrfam is not AF_UNSPEC, AF_INET or AF_INET6
		 */
		int setAF(std::shared_ptr<pingobj> obj, const int &addrfam);

		int sendTo(std::shared_ptr<pingobj> obj, std::shared_ptr<pinghost> ph, const void *buf, const size_t &buflen, const int &fd);

	}	// namespace internal

}	// namespace oping