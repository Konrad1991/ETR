#define STANDALONE_ETR
#include "../include/etr.hpp"

#define CATCH_CONFIG_MAIN
#include "./catch/catch.hpp"

TEST_CASE("Creating vectors with integer inputs", "[vector]") {
    SECTION("Creating vector with integer size") {
        etr::Vec<double> vec1 = etr::vector(5);
        REQUIRE(vec1.size() == 5);
        int s = 5;
        etr::Vec<double> vec2 = etr::vector(s);
        REQUIRE(vec2.size() == 5);
    }
    SECTION("Creating vector with floating-point size") {
        etr::Vec<double> vec1 = etr::vector(5.0);
        REQUIRE(vec1.size() == 5);
        double s = 5.0;
        etr::Vec<double> vec2 = etr::vector(s);
        REQUIRE(vec2.size() == 5);
    }
    SECTION("Creating vector with vector-like size") {
        REQUIRE_THROWS_AS(etr::vector(etr::Vec<int>(etr::SI{1})), std::exception); // size has to be larger 0
        REQUIRE_THROWS_AS(etr::vector(etr::Vec<int>(etr::SI{5})), std::exception); // vector entry has to have only one element
        etr::Vec<double> size1 = etr::vector(1); size1[0] = 2;
        etr::Vec<double> vec1 = etr::vector(size1);
        REQUIRE(vec1.size() == 2);

        int si = 1;
        etr::Vec<double> size2 = etr::vector(si); size2[0] = 2;
        etr::Vec<double> vec2 = etr::vector(size2);
        REQUIRE(vec2.size() == 2);
    }
}

TEST_CASE("Creating vectors with floating-point inputs", "[vector]") {
    SECTION("Creating vector with floating-point size") {
        etr::Vec<int> vec1 = etr::vector(5.5);
        REQUIRE(vec1.size() == 5); 

        double s = 5.5;
        etr::Vec<int> vec2 = etr::vector(s);
        REQUIRE(vec2.size() == 5); 
    }
}

TEST_CASE("Edge Cases for Integer Inputs", "[vector]") {
    SECTION("Creating vector with size zero") {
        REQUIRE_THROWS_AS(etr::vector(0), std::exception); 
    }
    SECTION("Creating vector with negative size") {
        REQUIRE_THROWS_AS(etr::vector(-5), std::exception); 
    }
}

TEST_CASE("Edge Cases for Floating-Point Inputs", "[vector]") {
    SECTION("Creating vector with size zero") {
        REQUIRE_THROWS_AS(etr::vector(0.2), std::exception); 
    }
    SECTION("Creating vector with negative size") {
        REQUIRE_THROWS_AS(etr::vector(-5.0), std::exception); 
    }
}

TEST_CASE("Large Input Values", "[vector]") {
    SECTION("Creating vector with large size") {
        etr::Vec<double> vec1 = etr::vector(1e6); 
        REQUIRE(vec1.size() == static_cast<size_t>(1e6));
    }
}

