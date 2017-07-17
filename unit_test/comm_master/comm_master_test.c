#include "unity/fixture/unity_fixture.h"

#include "comm/comm_master.h"

TEST_GROUP(comm_master);

TEST_SETUP(comm_master)
{
   /* Init before every test */
}

TEST_TEAR_DOWN(comm_master)
{
   /* Cleanup after every test */
}

TEST(comm_master, first)
{
   TEST_FAIL_MESSAGE("initial test setup");
}
