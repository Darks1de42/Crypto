//
// Created by dragonfire on 21.07.19.
//

#define BOOST_TEST_MODULE LoginTest

#include <boost/test/unit_test.hpp>
#include <random>
#include "../Header/CryptoClass.h"

BOOST_AUTO_TEST_SUITE(CryptoTest)


    BOOST_AUTO_TEST_CASE(LoginTest) {
        CryptoClass cry;
        srand(time(nullptr));
        std::string testPassword = std::to_string(rand());

        BOOST_TEST_MESSAGE("Hi " + testPassword);
        cry.newPassword(testPassword);

        for (size_t i = 0; i < 20; ++i) {
            BOOST_REQUIRE(cry.login(testPassword));
        }

    }

    BOOST_AUTO_TEST_CASE(Verschluesselung) {
        boost::unit_test::unit_test_log.set_threshold_level(boost::unit_test::log_test_units);

        CryptoClass cry;
        cry.encrypt("Test");
        cry.decrypt("Test");
        std::ifstream klartext("../datei.txt", std::fstream::in);
        std::ifstream entschluesselt("../entschluesselt.txt", std::fstream::in);
        while (klartext.peek() != EOF) {
            BOOST_REQUIRE_EQUAL(klartext.get(), entschluesselt.get());
        }

    }

BOOST_AUTO_TEST_SUITE_END()
