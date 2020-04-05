// tests/tests.cpp
// (c) 2020 Korbinian Brandler. All rights reserved.

#define CATCH_CONFIG_MAIN
#include "../lib/Catch2/single_include/catch2/catch.hpp"

#include "../src/liboping_internal.hpp"

TEST_CASE("check oping::internal::setErrorMsg()")
{
	std::shared_ptr<oping::pingobj> obj = std::make_shared<oping::pingobj>(oping::pingobj{});

	oping::internal::setErrorMsg(obj, "foo", "msg");
	REQUIRE(obj->errmsg == "foo: msg");

	oping::internal::setErrorMsg(obj, "baz", "msg");
	REQUIRE(obj->errmsg == "baz: msg");
}