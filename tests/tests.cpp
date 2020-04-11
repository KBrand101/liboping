// tests/tests.cpp
// (c) 2020 Korbinian Brandler. All rights reserved.

#define CATCH_CONFIG_MAIN
#include "../lib/Catch2/single_include/catch2/catch.hpp"

#include "../src/liboping_internal.hpp"

TEST_CASE("check oping::internal::setErrorMsg()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();

	oping::internal::setErrorMsg(obj, "foo", "msg");
	REQUIRE(obj->errmsg == "foo: msg");
}

TEST_CASE("check oping::internal::openSocket()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();

	int fd_ip4 = oping::internal::openSocket(obj, AF_INET);
	INFO(obj->errmsg);
	REQUIRE(fd_ip4 == 3);

	int fd_ip6 = oping::internal::openSocket(obj, AF_INET6);
	INFO(obj->errmsg);
	REQUIRE(fd_ip6 == 4);
}

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
}

TEST_CASE("check oping::construct()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();
	REQUIRE(obj->timeout == DEFAULT_TIMEOUT);
	REQUIRE(obj->ttl == DEFAULT_TTL);
	REQUIRE(obj->addrfamily == DEFAULT_AF);
	REQUIRE(obj->fd4 == -1);
	REQUIRE(obj->fd6 == -1);
	REQUIRE(obj->errmsg == "");
	REQUIRE(obj->table.empty());
}

TEST_CASE("check oping::getError()")
{
	std::shared_ptr<oping::pingobj> obj = oping::construct();

	oping::internal::setErrorMsg(obj, "foo", "msg");
	REQUIRE(oping::getError(obj) == "foo: msg");
}