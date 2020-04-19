// tests/tests.cpp
// (c) 2020 Korbinian Brandler. All rights reserved.

#define CATCH_CONFIG_MAIN
#include "../lib/Catch2/single_include/catch2/catch.hpp"

#include <netinet/ip.h>

#include "../src/liboping_internal.hpp"

TEST_CASE("check oping::internal::construct_ph()")
{
	std::shared_ptr<oping::pinghost> ph = oping::internal::construct_ph();
	REQUIRE(ph->addr == nullptr);
	REQUIRE(ph->addrlen == sizeof(sockaddr_storage));
	REQUIRE(ph->addrfamily == DEFAULT_AF);
}	// oping::internal::construct_ph

TEST_CASE("check oping::internal::setErrorMsg()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();

	oping::internal::setErrorMsg(obj, "foo", "msg");
	REQUIRE(obj->errmsg == "foo: msg");
}	// oping::internal::setErrorMsg

TEST_CASE("check oping::internal::openSocket()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();

	int fd_ip4 = oping::internal::openSocket(obj, AF_INET);
	INFO(obj->errmsg);
	REQUIRE(fd_ip4 == 3);

	int fd_ip6 = oping::internal::openSocket(obj, AF_INET6);
	INFO(obj->errmsg);
	REQUIRE(fd_ip6 == 4);
}	// oping::internal::openSocket

TEST_CASE("check oping::internal::setQos()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();

	int qos = oping::internal::setQos(obj, IPTOS_LOWDELAY);
	INFO(obj->errmsg);
	REQUIRE(obj->qos == IPTOS_LOWDELAY);
	REQUIRE(qos == 0);
}	// oping::internal::setQos

TEST_CASE("check oping::internal::setTimeout()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();

	int timeout_zero = oping::internal::setTimeout(obj, 0.0);
	INFO(obj->errmsg);
	REQUIRE(obj->timeout == 0.0);
	REQUIRE(timeout_zero == 0);

	int timeout_below_zero = oping::internal::setTimeout(obj, -1.0);
	INFO(obj->errmsg);
	REQUIRE(obj->timeout == DEFAULT_TIMEOUT);
	REQUIRE(timeout_below_zero == -1);
}	// oping::internal::setTimeout

TEST_CASE("check oping::internal::setTTL()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();

	int ttl_set = oping::internal::setTTL(obj, 50);
	INFO(obj->errmsg);
	REQUIRE(obj->ttl == 50);
	REQUIRE(ttl_set == 0);

	int ttl_min = oping::internal::setTTL(obj, 1);
	INFO(obj->errmsg);
	REQUIRE(ttl_min == 0);

	int ttl_max = oping::internal::setTTL(obj, 255);
	INFO(obj->errmsg);
	REQUIRE(ttl_min == 0);

	int ttl_to_small = oping::internal::setTTL(obj, 0);
	INFO(obj->errmsg);
	REQUIRE(ttl_to_small == -1);

	int ttl_to_big = oping::internal::setTTL(obj, 256);
	INFO(obj->errmsg);
	REQUIRE(ttl_to_big == -1);
}	// oping::internal::setTTL

TEST_CASE("check oping::internal::setAF()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();

	int result_af_unspec = oping::internal::setAF(obj, AF_UNSPEC);
	INFO(obj->errmsg);
	REQUIRE(result_af_unspec == 0);

	int result_af_ip4 = oping::internal::setAF(obj, AF_INET);
	INFO(obj->errmsg);
	REQUIRE(result_af_ip4 == 0);

	int result_af_ip6 = oping::internal::setAF(obj, AF_INET6);
	INFO(obj->errmsg);
	REQUIRE(result_af_ip6 == 0);

	int result_af_apple = oping::internal::setAF(obj, AF_APPLETALK);
	INFO(obj->errmsg);
	REQUIRE(result_af_apple == -1);
}	// oping::internal::setAF

TEST_CASE("check oping::construct()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();
	REQUIRE(obj->qos == -1);
	REQUIRE(obj->timeout == DEFAULT_TIMEOUT);
	REQUIRE(obj->ttl == DEFAULT_TTL);
	REQUIRE(obj->addrfamily == DEFAULT_AF);
	REQUIRE(obj->fd4 == -1);
	REQUIRE(obj->fd6 == -1);
	REQUIRE(obj->errmsg == "");
	REQUIRE(obj->table.empty());
}	// oping::construct

TEST_CASE("check oping::setOption()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();

	int opt_qos = oping::setOption(obj, oping::Option::QOS, IPTOS_LOWDELAY);
	REQUIRE(obj->qos == IPTOS_LOWDELAY);
	REQUIRE(opt_qos == 0);

	int opt_timeout = oping::setOption(obj, oping::Option::TIMEOUT, 1.0);
	REQUIRE(obj->timeout == 1.0);
	REQUIRE(opt_timeout == 0);

	int opt_ttl = oping::setOption(obj, oping::Option::TTL, 50);
	REQUIRE(obj->ttl == 50);
	REQUIRE(opt_ttl == 0);

	int opt_af_inet = oping::setOption(obj, oping::Option::AF, AF_INET);
	REQUIRE(obj->addrfamily == AF_INET);
	REQUIRE(opt_af_inet == 0);

	int opt_af_appletalk = oping::setOption(obj, oping::Option::AF, AF_APPLETALK);
	REQUIRE(obj->addrfamily == DEFAULT_AF);
	REQUIRE(opt_af_appletalk == -1);

	int opt_not_treated = oping::setOption(obj, oping::Option::COUNT, 0);
	REQUIRE(opt_not_treated == -2);
}	// oping::setOption

TEST_CASE("check oping::getError()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();

	oping::internal::setErrorMsg(obj, "foo", "msg");
	REQUIRE(oping::getError(obj) == "foo: msg");
}	// oping::getError