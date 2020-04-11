// tests/tests.cpp
// (c) 2020 Korbinian Brandler. All rights reserved.

#define CATCH_CONFIG_MAIN
#include "../lib/Catch2/single_include/catch2/catch.hpp"

#include "../src/liboping_internal.hpp"

TEST_CASE("check oping::internal::setErrorMsg()")
{
	using namespace std;
	shared_ptr<oping::pingobj> obj = make_shared<oping::pingobj>(oping::pingobj{});

	oping::internal::setErrorMsg(obj, "foo", "msg");
	REQUIRE(obj->errmsg == "foo: msg");

	oping::internal::setErrorMsg(obj, "baz", "msg");
	REQUIRE(obj->errmsg == "baz: msg");
}

TEST_CASE("check oping::internal::openSocket()")
{
	using namespace std;
	shared_ptr<oping::pingobj> obj = make_shared<oping::pingobj>(oping::pingobj{});

	int fd_ip4 = oping::internal::openSocket(obj, AF_INET);
	INFO(obj->errmsg);
	REQUIRE(fd_ip4 == 3);

	int fd_ip6 = oping::internal::openSocket(obj, AF_INET6);
	INFO(obj->errmsg);
	REQUIRE(fd_ip6 == 4);
}

TEST_CASE("check oping::getError()")
{
	using namespace std;
	shared_ptr<oping::pingobj> obj = make_shared<oping::pingobj>(oping::pingobj{});

	oping::internal::setErrorMsg(obj, "foo", "msg");
	REQUIRE(oping::getError(obj) == "foo: msg");
}