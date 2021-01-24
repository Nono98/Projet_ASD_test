#include "catch.hpp"
#include "../HashMapWrapper.h"
#include "../Chaining.cpp"

using namespace std;

TEST_CASE("various dummy tests", "[hashmap]") {

    HashMapWrapper<int> hashMapWrapper;

    SECTION("Empty hashMap") {
        REQUIRE(hashMapWrapper.size() == 0);
    }

    SECTION("insert and contains") {
        for (int i : {2, 4, 6, 8, 10}) {
            hashMapWrapper.insert(i);
        }

        for (int i : {2, 4, 6, 8, 10}) {
            REQUIRE(hashMapWrapper.contains(i));
        }

        REQUIRE(hashMapWrapper.size() == 5);
        REQUIRE(!hashMapWrapper.contains(1));
    }
}


TEST_CASE("various dummy tests_string", "[hashmap]") {

    Chaining<string> chaining(100);

    SECTION("Empty hashMap") {
        REQUIRE(chaining.size() == 0);
    }

    SECTION("insert and contains") {
        for (string i : {"2", "4", "6", "8", "10"}) {
            chaining.insert(i);
        }

        for (string i : {"2", "4", "6", "8", "10"}) {
            REQUIRE(chaining.contains(i));
        }

        REQUIRE(chaining.size() == 5);
        REQUIRE(!chaining.contains("1"));

        chaining.erase("4");
        REQUIRE(!chaining.contains("4"));
        REQUIRE(chaining.size() == 4);

    }
}


TEST_CASE("various dummy tests_size_t", "[hashmap]") {

    Chaining<size_t> chaining(1);

    SECTION("Empty hashMap") {
        REQUIRE(chaining.size() == 0);
    }

    SECTION("insert and contains") {
        for (size_t i : {2, 4, 6, 8, 10}) {
            chaining.insert(i);
        }

        for (size_t i : {2, 4, 6, 8, 10}) {
            REQUIRE(chaining.contains(i));
        }

        REQUIRE(chaining.size() == 5);
        REQUIRE(!chaining.contains(1));

        chaining.erase(4);
        REQUIRE(!chaining.contains(4));
        REQUIRE(chaining.size() == 4);
    }
}
