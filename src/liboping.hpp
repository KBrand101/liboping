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
		AF,	   // Address Family
		COUNT
	};

	std::shared_ptr<pingobj> construct();
	void					 addHost(std::shared_ptr<pingobj> obj, const std::string &host);
	void					 removeHost(std::shared_ptr<pingobj> obj, const std::string &host);

	/**
	 * Set given option to given value
	 * 
	 * @param obj Pointer to current pingobj
	 * @param opt See enum Option
	 * @param value The value to set the option to
	 * @return 0 if everything is ok
	 * @return -1 if an error occurs (see oping::getError() for details)
	 */
	int setOption(std::shared_ptr<pingobj> obj, const Option &opt, const double &value);

	void getCount();
	int	 sendPing(std::shared_ptr<pingobj> obj);

	/**
	 * Get latest error message
	 * 
	 * @param obj Pointer to current pingobj
	 * @return the latest error message
	 */
	std::string getError(std::shared_ptr<pingobj> obj);

}	// namespace oping