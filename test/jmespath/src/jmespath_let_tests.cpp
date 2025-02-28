// Copyright 2013-2025 Daniel Parker
// Distributed under Boost license

#if defined(_MSC_VER)
#include "windows.h" // test no inadvertant macro expansions
#endif

#include <jsoncons_ext/jmespath/jmespath.hpp>
#include <jsoncons/json.hpp>

#include <iostream>
#include <catch/catch.hpp>

namespace jmespath = jsoncons::jmespath;

TEST_CASE("jmespath let tests")
{
    SECTION("Test 1")
    {
        auto doc = jsoncons::json::parse(R"({"foo": "bar"})");
        auto expected = jsoncons::json::parse(R"("bar")");

        std::string query = R"(let $foo = foo in $foo)";
        auto expr = jmespath::make_expression<jsoncons::json>(query);

        jsoncons::json result = expr.evaluate(doc);
        CHECK(expected == result);
    }    
    SECTION("Test 2")
    {
        auto doc = jsoncons::json::parse(R"({"foo": {"bar": "baz"}})");
        auto expected = jsoncons::json::parse(R"("baz")");

        std::string query = R"(let $foo = foo.bar in $foo)";
        auto expr = jmespath::make_expression<jsoncons::json>(query);

        jsoncons::json result = expr.evaluate(doc);
        CHECK(expected == result);
    }    
    SECTION("Test 3")
    {
        auto doc = jsoncons::json::parse(R"({"foo": "bar"})");
        auto expected = jsoncons::json::parse(R"(["bar", "bar"])");

        std::string query = R"(let $foo = foo in [$foo, $foo])";
        auto expr = jmespath::make_expression<jsoncons::json>(query);

        jsoncons::json result = expr.evaluate(doc);
        CHECK(expected == result);
    }    
    SECTION("Nested bindings")
    {
        auto doc = jsoncons::json::parse(R"({"a": "topval", "b": [{"a": "inner1"}, {"a": "inner2"}]})");
        auto expected = jsoncons::json::parse(R"( [["inner1", "topval", "shadow"], ["inner2", "topval", "shadow"]])");

        std::string query = R"(let $a = a
  in
    b[*].[a, $a, let $a = 'shadow' in $a])";
        auto expr = jmespath::make_expression<jsoncons::json>(query);

        jsoncons::json result = expr.evaluate(doc);
        CHECK(expected == result);
    }
}

TEST_CASE("jmespath let as valid identifiers")
{
    auto doc = jsoncons::json::parse(R"(
{
    "let" : 
    {
        "let" : "let-val",
        "in" : "in-val"
    }
}
    )");

    SECTION("test 1")
{
        auto expected = jsoncons::json::parse(R"(
{
    "in": {
        "in": "in-val",
        "let": "let-val"
    },
    "let": {
        "in": "in-val",
        "let": "let-val"
    }
}
        )");

        std::string query = R"(let $let = let in {let: let, in: $let})";
        auto expr = jmespath::make_expression<jsoncons::json>(query);

        jsoncons::json result = expr.evaluate(doc);
        //std::cout << pretty_print(result) << "\n";
        CHECK(expected == result);
    }    

    SECTION("test 2")
{
        auto expected = jsoncons::json::parse(R"(
{
    "in": "let",
    "let": {
        "in": "in-val",
        "let": "let-val"
    }
}
        )");

        std::string query = R"(let $let = 'let' in { let: let, in: $let })";
        auto expr = jmespath::make_expression<jsoncons::json>(query);

        jsoncons::json result = expr.evaluate(doc);
        //std::cout << pretty_print(result) << "\n";
        CHECK(expected == result);
    }    

    SECTION("test 3")
    {
        auto expected = jsoncons::json::parse(R"(
{
    "in": "let",
    "let": "let"
}
        )");

        std::string query = R"(let $let = 'let' in { let: 'let', in: $let })";
        auto expr = jmespath::make_expression<jsoncons::json>(query);

        jsoncons::json result = expr.evaluate(doc);
        //std::cout << pretty_print(result) << "\n";
        CHECK(expected == result);
    }    
}

TEST_CASE("jmespath let projection stop")
{
    auto doc = jsoncons::json::parse(R"(
{"foo" : [[0, 1], [2, 3], [4, 5]]}
    )");

    SECTION("test 1")
{
        auto expected = jsoncons::json::parse(R"(
[0, 1]
        )");

        std::string query = R"(let $foo = foo[*] in $foo[0])";
        auto expr = jmespath::make_expression<jsoncons::json>(query);

        jsoncons::json result = expr.evaluate(doc);
        //std::cout << pretty_print(result) << "\n";
        CHECK(expected == result);
    }    
}

