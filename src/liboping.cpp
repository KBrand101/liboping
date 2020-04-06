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
		}

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

			if (obj->srcaddr != nullptr)
			{
				assert(obj->srcaddrlen > 0);
				assert(obj->srcaddrlen <= sizeof(sockaddr_storage));

				if (bind(fd, obj->srcaddr.get(), obj->srcaddrlen) == -1)
				{
					setErrorMsg(obj, "openSocket", "Failed to bind socket");
					return -1;
				}
			}

			if (addrfam == AF_INET)
				setsockopt(fd, IPPROTO_IP, IP_RECVTTL, new int, sizeof(int));

			if (fd == -1)
				setErrorMsg(obj, "openSocket", "Failed to create socket");
			return fd;
		}
	}	// namespace internal

	void addHost(std::shared_ptr<pingobj> obj, const std::string &host)
	{
		assert(obj != nullptr);

	}	// void addHost

	std::string getError(std::shared_ptr<pingobj> obj)
	{
		assert(obj != nullptr);
		return obj->errmsg;
	}

}	// namespace oping