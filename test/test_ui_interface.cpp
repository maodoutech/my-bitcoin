#define BOOST_TEST_MODULE BITCONID

#include "noui.h"

#include <boost/test/included/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(test_case_noui_connect) 
{
    noui_connect();
}
