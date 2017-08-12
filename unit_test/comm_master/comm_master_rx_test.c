#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "unity/fixture/unity_fixture.h"

#include "comm/comm_master.h"
#include "mocks/comm_master_mocks.h"

#define TEST_BUF_SIZE	32
#define ADDR			15

uint8_t test_buf[TEST_BUF_SIZE];

TEST_GROUP(comm_master_rx);

TEST_SETUP(comm_master_rx)
{
   memset(test_buf, 0xAA, TEST_BUF_SIZE);
}

TEST_TEAR_DOWN(comm_master_rx)
{
   /* Cleanup after every test */
}

TEST(comm_master_rx, first_test)
{
   TEST_FAIL_MESSAGE("Implement test!");
}
