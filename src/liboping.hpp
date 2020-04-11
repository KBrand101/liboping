// src/liboping.hpp
// (c) 2020 Korbinian Brandler. All rights reserved.

#pragma once

#include <memory>
#include <netdb.h>
#include <string>
#include <vector>

namespace oping
{
	struct pinghost;
	struct pingobj;

	enum Option
	{
		QOS,   // Qualtiy of Service
		TIMEOUT,
		TTL,   // Time to Live
		AF	   // Address Family
	};

	std::shared_ptr<pingobj> construct();
	void					 addHost(std::shared_ptr<pingobj> obj, const std::string &host);
	void					 removeHost(std::shared_ptr<pingobj> obj, const std::string &host);
	int						 setOption(std::shared_ptr<pingobj> obj, const Option &opt);
	void					 getCount();
	void					 sendPing(std::shared_ptr<pingobj> obj);
	std::string				 getError(std::shared_ptr<pingobj> obj);

}	// namespace oping