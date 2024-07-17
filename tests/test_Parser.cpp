#include "doctest.h"
#include "Parser.h"

TEST_CASE("Parser tests")
{
    Parser parser;

    std::string sampleData = "$GPRMC,060100.000,A,0144.4683,S,03648.0835,E,2.5,45.0,080724,,A*6C";
    Parser::Data result = parser.parseSentence(sampleData);
    CHECK(result.timestamp == "Mon, 08 Jul 2024 06:01:00 UTC");
    CHECK(result.speed == "2.5");
    CHECK(result.course == "45");
}

// TODO: Additional tests for edge cases and error handling
TEST_CASE("Parser error handling tests")
{
}
