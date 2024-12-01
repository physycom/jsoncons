// Copyright 2013-2024 Daniel Parker
// Distributed under Boost license

#include <jsoncons/utility/uri.hpp>
#include <catch/catch.hpp>
#include <iostream>

TEST_CASE("uri tests (https://en.wikipedia.org/wiki/Uniform_Resource_Identifier)")
{
    SECTION("https://john.doe@www.example.com:123/forum/questions/?tag=networking&order=newest#top")
    {
        std::string s = "https://john.doe@www.example.com:123/forum/questions/?tag=networking&order=newest#top";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme() == jsoncons::string_view("https"));
        CHECK(uri.encoded_authority() == jsoncons::string_view("john.doe@www.example.com:123"));
        CHECK(uri.userinfo() == jsoncons::string_view("john.doe"));
        CHECK(uri.host() == jsoncons::string_view("www.example.com"));
        CHECK(uri.port() == jsoncons::string_view("123"));
        CHECK(uri.path() == jsoncons::string_view("/forum/questions/"));
        CHECK(uri.encoded_query() == jsoncons::string_view("tag=networking&order=newest"));
        CHECK(uri.encoded_fragment() == jsoncons::string_view("top"));
        CHECK(uri.base().string() == "https://john.doe@www.example.com:123/forum/questions/");
        CHECK(uri.is_absolute());
    }
    SECTION("ldap://[2001:db8::7]/c=GB?objectClass?one")
    {
        std::string s = "ldap://[2001:db8::7]/c=GB?objectClass?one";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme() == jsoncons::string_view("ldap"));
        CHECK(uri.encoded_authority() == jsoncons::string_view("2001:db8::7"));
        CHECK(uri.userinfo() == jsoncons::string_view(""));
        CHECK(uri.host() == jsoncons::string_view("2001:db8::7"));
        CHECK(uri.port() == jsoncons::string_view(""));
        CHECK(uri.encoded_path() == jsoncons::string_view("/c=GB"));
        CHECK(uri.encoded_query() == jsoncons::string_view("objectClass?one"));
        CHECK(uri.encoded_fragment() == jsoncons::string_view(""));
        CHECK(uri.is_absolute());
    }
    SECTION("mailto:John.Doe@example.com")
    {
        std::string s = "mailto:John.Doe@example.com";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme() == jsoncons::string_view("mailto"));
        CHECK(uri.encoded_authority() == jsoncons::string_view(""));
        CHECK(uri.userinfo() == jsoncons::string_view(""));
        CHECK(uri.host() == jsoncons::string_view(""));
        CHECK(uri.port() == jsoncons::string_view(""));
        CHECK(uri.encoded_path() == jsoncons::string_view("John.Doe@example.com"));
        CHECK(uri.encoded_query() == jsoncons::string_view(""));
        CHECK(uri.encoded_fragment() == jsoncons::string_view(""));
        CHECK(uri.is_absolute());
    }
    SECTION("news:comp.infosystems.www.servers.unix")
    {
        std::string s = "news:comp.infosystems.www.servers.unix";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme() == jsoncons::string_view("news"));
        CHECK(uri.encoded_authority() == jsoncons::string_view(""));
        CHECK(uri.userinfo() == jsoncons::string_view(""));
        CHECK(uri.host() == jsoncons::string_view(""));
        CHECK(uri.port() == jsoncons::string_view(""));
        CHECK(uri.encoded_path() == jsoncons::string_view("comp.infosystems.www.servers.unix"));
        CHECK(uri.encoded_query() == jsoncons::string_view(""));
        CHECK(uri.encoded_fragment() == jsoncons::string_view(""));
        CHECK(uri.is_absolute());
    }
    SECTION("tel:+1-816-555-1212")
    {
        std::string s = "tel:+1-816-555-1212";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme() == jsoncons::string_view("tel"));
        CHECK(uri.encoded_authority() == jsoncons::string_view(""));
        CHECK(uri.userinfo() == jsoncons::string_view(""));
        CHECK(uri.host() == jsoncons::string_view(""));
        CHECK(uri.port() == jsoncons::string_view(""));
        CHECK(uri.encoded_path() == jsoncons::string_view("+1-816-555-1212"));
        CHECK(uri.encoded_query() == jsoncons::string_view(""));
        CHECK(uri.encoded_fragment() == jsoncons::string_view(""));
        CHECK(uri.is_absolute());
    }
    SECTION("telnet://192.0.2.16:80/")
    {
        std::string s = "telnet://192.0.2.16:80/";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme() == jsoncons::string_view("telnet"));
        CHECK(uri.encoded_authority() == jsoncons::string_view("192.0.2.16:80"));
        CHECK(uri.userinfo() == jsoncons::string_view(""));
        CHECK(uri.host() == jsoncons::string_view("192.0.2.16"));
        CHECK(uri.port() == jsoncons::string_view("80"));
        CHECK(uri.encoded_path() == jsoncons::string_view("/"));
        CHECK(uri.encoded_query() == jsoncons::string_view(""));
        CHECK(uri.encoded_fragment() == jsoncons::string_view(""));
        CHECK(uri.is_absolute());
    }
    SECTION("urn:oasis:names:specification:docbook:dtd:xml:4.1.2")
    {
        std::string s = "urn:oasis:names:specification:docbook:dtd:xml:4.1.2";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme() == jsoncons::string_view("urn"));
        CHECK(uri.encoded_authority() == jsoncons::string_view(""));
        CHECK(uri.userinfo() == jsoncons::string_view(""));
        CHECK(uri.host() == jsoncons::string_view(""));
        CHECK(uri.port() == jsoncons::string_view(""));
        CHECK(uri.encoded_path() == jsoncons::string_view("oasis:names:specification:docbook:dtd:xml:4.1.2"));
        CHECK(uri.encoded_query() == jsoncons::string_view(""));
        CHECK(uri.encoded_fragment() == jsoncons::string_view(""));
        CHECK(uri.is_absolute());
    }
    SECTION("urn:example:foo-bar-baz-qux?+CCResolve:cc=uk")
    {
        std::string s = "urn:example:foo-bar-baz-qux?+CCResolve:cc=uk";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme() == jsoncons::string_view("urn"));
        CHECK(uri.encoded_authority() == jsoncons::string_view(""));
        CHECK(uri.userinfo() == jsoncons::string_view(""));
        CHECK(uri.host() == jsoncons::string_view(""));
        CHECK(uri.port() == jsoncons::string_view(""));
        CHECK(uri.encoded_path() == jsoncons::string_view("example:foo-bar-baz-qux"));
        CHECK(uri.encoded_query() == jsoncons::string_view("+CCResolve:cc=uk"));
        CHECK(uri.encoded_fragment() == jsoncons::string_view(""));
        CHECK(uri.is_absolute());

        jsoncons::uri relative("#/defs/bar");
        jsoncons::uri new_uri = relative.resolve(uri);
        //std::cout << "new_uri: " << new_uri.string() << "\n"; 
    }
}

TEST_CASE("uri fragment tests")
{
    SECTION("#/definitions/nonNegativeInteger")
    {
        std::string s = "#/definitions/nonNegativeInteger";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme().empty());
        CHECK(uri.encoded_authority().empty());
        CHECK(uri.userinfo().empty());
        CHECK(uri.host().empty());
        CHECK(uri.port().empty());
        CHECK(uri.encoded_path().empty());
        CHECK(uri.encoded_query().empty());
        CHECK(uri.encoded_fragment() == jsoncons::string_view("/definitions/nonNegativeInteger"));
        CHECK(!uri.is_absolute());
    }
}

TEST_CASE("uri base tests")
{
    SECTION("http://json-schema.org/draft-07/schema#")
    {
        std::string s = "http://json-schema.org/draft-07/schema#";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme() == jsoncons::string_view("http"));
        CHECK(uri.encoded_authority() == jsoncons::string_view("json-schema.org"));
        CHECK(uri.userinfo().empty());
        CHECK(uri.host() == jsoncons::string_view("json-schema.org"));
        CHECK(uri.port().empty());
        CHECK(uri.encoded_path() == jsoncons::string_view("/draft-07/schema"));
        CHECK(uri.encoded_query().empty());
        CHECK(uri.encoded_fragment().empty());
        CHECK(uri.is_absolute());
    }
    SECTION("folder/")
    {
        std::string s = "folder/";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme().empty());
        CHECK(uri.encoded_authority().empty());
        CHECK(uri.userinfo().empty());
        CHECK(uri.host().empty());
        CHECK(uri.port().empty());
        CHECK(uri.encoded_path() == jsoncons::string_view("folder/"));
        CHECK(uri.encoded_query().empty());
        CHECK(uri.encoded_fragment().empty());
        CHECK(!uri.is_absolute());
    }
    SECTION("name.json#/definitions/orNull")
    {
        std::string s = "name.json#/definitions/orNull";

        jsoncons::uri uri(s); 

        CHECK(uri.scheme().empty());
        CHECK(uri.encoded_authority().empty());
        CHECK(uri.userinfo().empty());
        CHECK(uri.host().empty());
        CHECK(uri.port().empty());
        CHECK(uri.encoded_path() == jsoncons::string_view("name.json"));
        CHECK(uri.encoded_query().empty());
        CHECK(uri.encoded_fragment() == jsoncons::string_view("/definitions/orNull"));
        CHECK(!uri.is_absolute());
    }
}

TEST_CASE("uri resolve tests")
{
    SECTION("empty base")
    {
        jsoncons::uri base{ "" };
        jsoncons::uri rel{"dir1/other.schema.json"};
        jsoncons::uri uri = rel.resolve(base);
        CHECK(uri.base().string() == "dir1/other.schema.json");
        CHECK(uri.path() == "dir1/other.schema.json");
    }

    SECTION("base has no authority and no path")
    {
        jsoncons::uri base{ "https" };
        jsoncons::uri rel{ "dir1/other.schema.json" };
        jsoncons::uri uri = rel.resolve(base);
        CHECK(uri.base().string() == "dir1/other.schema.json");
        CHECK(uri.path() == "dir1/other.schema.json");
    }

    SECTION("base has authority and path")
    {
        jsoncons::uri base{ "https://root" };
        jsoncons::uri rel{"dir1/other.schema.json"};
        jsoncons::uri uri = rel.resolve(base);
        CHECK(uri.base().string() == "https://root/dir1/other.schema.json");
        CHECK(uri.path() == "/dir1/other.schema.json");
    }
    
    SECTION("folder/")
    {
        jsoncons::uri base_uri("http://localhost:1234/scope_change_defs2.json"); 
        jsoncons::uri relative_uri("folder/");
        
        jsoncons::uri uri =  relative_uri.resolve(base_uri);

        CHECK(uri.scheme() == jsoncons::string_view("http"));
        CHECK(uri.encoded_authority() == jsoncons::string_view("localhost:1234"));
        CHECK(uri.userinfo().empty());
        CHECK(uri.host() == jsoncons::string_view("localhost"));
        CHECK(uri.port() == jsoncons::string_view("1234"));
        CHECK(uri.encoded_path() == jsoncons::string_view("/folder/"));
        CHECK(uri.encoded_query().empty());
        CHECK(uri.encoded_fragment().empty());
        CHECK(uri.is_absolute());
    }
    SECTION("folderInteger.json")
    {
        jsoncons::uri base_uri("http://localhost:1234/folder/"); 
        jsoncons::uri relative_uri("folderInteger.json");

        jsoncons::uri uri =  relative_uri.resolve(base_uri);

        CHECK(uri.scheme() == jsoncons::string_view("http"));
        CHECK(uri.encoded_authority() == jsoncons::string_view("localhost:1234"));
        CHECK(uri.userinfo().empty());
        CHECK(uri.host() == jsoncons::string_view("localhost"));
        CHECK(uri.port() == jsoncons::string_view("1234"));
        CHECK(uri.encoded_path() == jsoncons::string_view("/folder/folderInteger.json"));
        CHECK(uri.encoded_query().empty());
        CHECK(uri.encoded_fragment().empty());
        CHECK(uri.is_absolute());
    }
}

TEST_CASE("uri part decode tests")
{
    SECTION("test 1")
    {
        std::string raw = "%7e";
        std::string expected = "~";

        std::string decoded = jsoncons::uri::decode_part(raw);
        CHECK(decoded == expected);
    }
    SECTION("test 2")
    {
        std::string raw = "%25";
        std::string expected = "%";

        std::string decoded = jsoncons::uri::decode_part(raw);
        CHECK(decoded == expected);
    }
    SECTION("test 3")
    {
        std::string raw = "foo%25bar%7ebaz";
        std::string expected = "foo%bar~baz";

        std::string decoded = jsoncons::uri::decode_part(raw);
        CHECK(decoded == expected);
    }
}

TEST_CASE("uri part encode tests")
{
    SECTION("test 1")
    {
        std::string part = "/@_-!.~'()*azAZ09,;:$&+=%3F%ae";
        std::string expected = part;

        std::string encoded;
        jsoncons::uri::encode_path(part, encoded);
        CHECK(encoded == expected);
    }
    
    SECTION("test 2")
    {
        std::string part = "%?/[]@,;:$&+=";
        std::string expected = "%25%3F/%5B%5D@,;:$&+=";

        std::string encoded;
        jsoncons::uri::encode_path(part, encoded);
        CHECK(encoded == expected);
    }
}

TEST_CASE("uri part encode illegal characters tests")
{
    SECTION("test 1")
    {
        std::string part = "_-!.~'()*azAZ09?/[]@,;:$&+=%3F%ae";
        std::string expected = part;

        std::string encoded;
        jsoncons::uri::encode_illegal_characters(part, encoded);
        CHECK(encoded == expected);
    }
}

TEST_CASE("uri constructors")
{
    SECTION("test 1")
    {
        jsoncons::uri x{"http://localhost:4242/draft2019-09/recursiveRef6/base.json"};

        jsoncons::uri y{ x, jsoncons::utility::uri_fragment_part, "/anyOf" };

        jsoncons::uri expected{"http://localhost:4242/draft2019-09/recursiveRef6/base.json#/anyOf"};

        CHECK(expected == y);       
    }
}


TEST_CASE("uri parsing tests")
{
    SECTION("an invalid URI with spaces")
    {
        std::string str = "http://shouldfail.com";
        
        std::error_code ec;
        jsoncons::uri id = jsoncons::uri::parse(str, ec);
        
        /*std::cout << "authority: [" << id.encoded_authority() << "]\n";
        std::cout << "host: [" << id.encoded_host() << "]\n";
        std::cout << "port: [" << id.encoded_port() << "]\n";
        std::cout << "path: [" << id.encoded_path() << "]\n";
        */

        //CHECK(ec);       
    }
}

TEST_CASE("cpp-netlib uri tests")
{
    SECTION("test_empty_path")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("http://123.34.23.56", ec);
        REQUIRE_FALSE(ec);
        CHECK(uri.encoded_path().empty());
    }
    SECTION("test_empty_path_with_query")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("http://123.34.23.56?query", ec);
        REQUIRE_FALSE(ec);
        CHECK(uri.encoded_path().empty());
    }
    SECTION("test_empty_path_with_fragment")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("http://123.34.23.56#fragment", ec);
        REQUIRE_FALSE(ec);
        CHECK(uri.encoded_path().empty());
    }
    SECTION("test_single_slash")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("http://123.34.23.56/", ec);
        REQUIRE_FALSE(ec);
        CHECK("/" == uri.encoded_path());
    }
    SECTION("test_single_slash_with_query")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("http://123.34.23.56/?query", ec);
        REQUIRE_FALSE(ec);
        CHECK("/" == uri.encoded_path());
    }
    SECTION("test_single_slash_with_fragment")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("http://123.34.23.56/#fragment", ec);
        REQUIRE_FALSE(ec);
        CHECK("/" == uri.encoded_path());
    }
    SECTION("test_double_slash_empty_path_empty_everything")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("file://", ec);
        REQUIRE(ec == jsoncons::utility::uri_errc::invalid_uri);
        CHECK(uri.encoded_path().empty());
    }
    SECTION("test_triple_slash_empty_everything")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("file:///", ec);
        REQUIRE_FALSE(ec);
        CHECK("/" == uri.encoded_path());
    }
    SECTION("test_triple_slash_with_path_name")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("file:///path", ec);
        REQUIRE_FALSE(ec);
        CHECK("/path" == uri.encoded_path());
    }
    SECTION("test_rootless_1")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("mailto:john.doe@example.com", ec);
        REQUIRE_FALSE(ec);
        CHECK("john.doe@example.com" == uri.encoded_path());
    }
    SECTION("test_invalid_characters_in_path")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("mailto:jo%hn.doe@example.com", ec);
        REQUIRE(ec);
        REQUIRE(jsoncons::utility::uri_errc::invalid_characters_in_path == ec);
        //std::cout << ec.message() << "\n";
    }
    SECTION("test_invalid_percent_encoded_characters_in_path_1")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("mailto:john.doe@example%G0.com", ec);
        REQUIRE(ec);
        REQUIRE(jsoncons::utility::uri_errc::invalid_characters_in_path == ec);
        //std::cout << ec.message() << "\n";
    }
    SECTION("test_invalid_percent_encoded_characters_in_path_2")
    {
        std::error_code ec;
        jsoncons::utility::uri uri = jsoncons::utility::uri::parse("mailto:john.doe@example%0G.com", ec);
        REQUIRE(ec);
        REQUIRE(jsoncons::utility::uri_errc::invalid_characters_in_path == ec);
        //std::cout << ec.message() << "\n";
    }
}

TEST_CASE("test uri resolve")
{
    SECTION("empty base-1")
    {
        std::string str = "./other.schema.json";
        jsoncons::utility::uri uri{str};
        auto uri2 = uri.resolve(jsoncons::utility::uri{ "" });
        CHECK(str == uri2.string());
    }
    SECTION("empty base-2")
    {
        std::string str = "../../../../dir2/foo/bar/baz/main.schema.json";
        jsoncons::utility::uri uri{str};
        auto uri2 = uri.resolve(jsoncons::utility::uri{ "" });
        CHECK(str == uri2.string());
    }
}

