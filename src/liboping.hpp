// src/liboping.hpp
// (c) 2020 Korbinian Brandler. All rights reserved.

#pragma once

#include <memory>
#include <netdb.h>
#include <string>
#include <vector>

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

		std::shared_ptr<sockaddr> srcaddr;
		socklen_t				  srcaddrlen;

		std::string			  errmsg;
		std::vector<pinghost> table;
	};	 // pingobj

	void		addHost(std::shared_ptr<pingobj> obj, const std::string &host);
	void		removeHost(std::shared_ptr<pingobj> obj, const std::string &host);
	void		setOption();
	void		getCount();
	void		sendPing(std::shared_ptr<pingobj> obj);
	std::string getError(std::shared_ptr<pingobj> obj);

}	// namespace oping