#include <stdint.h>

#include "unity/fixture/unity_fixture.h"

#include "comm/comm_master.h"

#define TEST_BUF_SIZE	32

uint8_t test_buf[TEST_BUF_SIZE];

TEST_GROUP(comm_master);

TEST_SETUP(comm_master)
{
   /* Init before every test */
}

TEST_TEAR_DOWN(comm_master)
{
   /* Cleanup after every test */
}

TEST(comm_master, arg_buf)
{
	TEST_ASSERT_EQUAL(-1, comm_master_tx(15, NULL));
	TEST_ASSERT_EQUAL(0, comm_master_tx(15, test_buf));
}
