//
// Created by Lev on 20.01.2021.
//

#include "catch.hpp"
#include "../TernarySearchTree.h"
using namespace std;

TEST_CASE("Various functions test", "[Ternary Search Tree]") {

    string wordList[] = {"bonjour", "hello", "bonjourno", "gutten", "tag"};

    SECTION("Empty tree"){
        TernarySearchTree tst;
        REQUIRE(tst.size() == 0);
    }

    SECTION("Tree size"){
        TernarySearchTree tst;
        for(string s: wordList)
            tst.insert(s);
        REQUIRE(tst.size() == 5);
    }

    SECTION("insert and contains") {
        TernarySearchTree tst;
        for(string s: wordList)
            tst.insert(s);
        for(string s: wordList)
            REQUIRE(tst.contains(s));
    }

    SECTION("Tree balance"){
        TernarySearchTree tst;
        for(string s: wordList)
            tst.insert(s);
        REQUIRE(((tst.balance() >= -1) && (tst.balance() <= 1)));
    }

    SECTION("Tree balance with single insert"){
        TernarySearchTree tst;
        tst.insert("bonjour");
        REQUIRE(tst.balance() == 0);
    }

    SECTION("Tree balance with no insert"){
        TernarySearchTree tst;
        REQUIRE(tst.balance() == 0);
    }




}



