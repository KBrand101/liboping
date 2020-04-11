// src/liboping.cpp
// (c) 2020 Korbinian Brandler. All rights reserved.

#include "liboping_internal.hpp"

#include <cassert>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace oping
{
	namespace internal
	{
		void setErrorMsg(std::shared_ptr<pingobj> obj, const std::string &function, const std::string &msg)
		{
			assert(obj != nullptr);

			// ensure that strings are not empty
			assert(function.length() > 0);
			assert(msg.length() > 0);

			obj->errmsg = function + ": " + msg;
		}	// void setErrorMsg

		int openSocket(std::shared_ptr<pingobj> obj, const int &addrfam)
		{
			assert(obj != nullptr);
			assert(addrfam == AF_INET || addrfam == AF_INET6);

			int fd;	  // file descriptor for socket

			switch (addrfam)
			{
				case AF_INET:
					fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
					break;
				case AF_INET6:
					fd = socket(AF_INET6, SOCK_RAW, IPPROTO_ICMPV6);
					break;
				default:
					setErrorMsg(obj, "openSocket", "Unknown address family");
					return -1;
			}

			if (fd >= FD_SETSIZE)
			{
				setErrorMsg(obj, "openSocket", "socket(2) returned file descriptor " + std::to_string(fd) + ", which is above the file descriptor limit for select(2) (FD_SETSIZE = " + std::to_string(FD_SETSIZE) + ")");
				close(fd);
				return -1;
			}

			if (addrfam == AF_INET)
				setsockopt(fd, IPPROTO_IP, IP_RECVTTL, new int, sizeof(int));

			if (fd == -1)
				setErrorMsg(obj, "openSocket", "Failed to create socket");
			return fd;
		}	// int openSocket

		int setQos(std::shared_ptr<pingobj> obj, const uint8_t &qos)
		{
			assert(obj != nullptr);

			obj->qos = qos;

			if (obj->fd4 != -1)
			{
				if (setsockopt(obj->fd4, IPPROTO_IP, IP_TOS, &qos, sizeof(qos)))
				{
					setErrorMsg(obj, "setQos", "Failed to set Qos (" + std::to_string(qos) + " given)");
					return -1;
				}
			}

			if (obj->fd6 != -1)
			{
				if (setsockopt(obj->fd6, IPPROTO_IPV6, IPV6_TCLASS, &qos, sizeof(qos)))
				{
					setErrorMsg(obj, "setQos", "Failed to set Qos" + std::to_string(qos) + " given)");
					return -1;
				}
			}

			return 0;
		}	// int setQos

		int setTimeout(std::shared_ptr<pingobj> obj, const double &timeout)
		{
			assert(obj != nullptr);

			if (timeout < 0.0)
			{
				obj->timeout = DEFAULT_TIMEOUT;
				setErrorMsg(obj, "setTimeout", "Given timeout is below zero: " + std::to_string(timeout));
				return -1;
			}

			obj->timeout = timeout;
			return 0;
		}	// int setTimeout

		int setTTL(std::shared_ptr<pingobj> obj, const int &ttl)
		{
			assert(obj != nullptr);

			if (ttl < 1 || ttl > 255)
			{
				obj->ttl = DEFAULT_TTL;
				setErrorMsg(obj, "setTTL", "Given TTL is out of range");
				return -1;
			}

			obj->ttl = ttl;

			if (obj->fd4 != -1)
			{
				if (setsockopt(obj->fd4, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)))
				{
					setErrorMsg(obj, "setTTL", "Failed to set TTL (" + std::to_string(ttl) + " given)");
					return -1;
				}
			}

			if (obj->fd6 != -1)
			{
				if (setsockopt(obj->fd6, IPPROTO_IPV6, IPV6_UNICAST_HOPS, &ttl, sizeof(ttl)))
				{
					setErrorMsg(obj, "setTTL", "Failed to set TTL" + std::to_string(ttl) + " given)");
					return -1;
				}
			}

			return 0;
		}	// int setTTL

		int setAF(std::shared_ptr<pingobj> obj, const int &addrfam)
		{
			assert(obj != nullptr);

			if ((addrfam != AF_UNSPEC) && (addrfam != AF_INET) && (addrfam != AF_INET6))
			{
				obj->addrfamily = DEFAULT_AF;
				setErrorMsg(obj, "setAF", "Invalid address family" + addrfam);
				return -1;
			}

			obj->addrfamily = addrfam;
			return 0;
		}	// int setAF

	}	// namespace internal

	std::shared_ptr<pingobj> construct()
	{
		pingobj obj;
		obj.timeout	   = DEFAULT_TIMEOUT;
		obj.ttl		   = DEFAULT_TTL;
		obj.addrfamily = DEFAULT_AF;
		obj.fd4		   = -1;
		obj.fd6		   = -1;
		obj.errmsg	   = "";
		obj.table	   = std::vector<pinghost>(0);

		return std::make_shared<pingobj>(obj);
	}	// std::shared_ptr<pingobj> construct

	void addHost(std::shared_ptr<pingobj> obj, const std::string &host)
	{
		assert(obj != nullptr);

	}	// void addHost

	int setOption(std::shared_ptr<pingobj> obj, const Option &opt)
	{
		assert(obj != nullptr);

		switch (opt)
		{
			case QOS:
				break;
			case TIMEOUT:
				break;
			case TTL:
				break;
			case AF:
				break;
			default:
				internal::setErrorMsg(obj, "setOption", "Unknown option");
				return -1;
		}
	}	// void setOption

	std::string getError(std::shared_ptr<pingobj> obj)
	{
		assert(obj != nullptr);
		return obj->errmsg;
	}	// std::string getError

}	// namespace oping