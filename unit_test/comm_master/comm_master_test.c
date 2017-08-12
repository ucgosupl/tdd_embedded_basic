#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "unity/fixture/unity_fixture.h"

#include "comm/comm_master.h"

#define TEST_BUF_SIZE	32
#define ADDR			15

uint8_t test_buf[TEST_BUF_SIZE];

TEST_GROUP(comm_master);

TEST_SETUP(comm_master)
{
   memset(test_buf, 0xAA, TEST_BUF_SIZE);
}

TEST_TEAR_DOWN(comm_master)
{
   /* Cleanup after every test */
}

TEST(comm_master, arg_buf)
{
	TEST_ASSERT_EQUAL(COMM_ERR_INVALID, comm_master_tx(ADDR, NULL));
	TEST_ASSERT_EQUAL(COMM_ERR_OK, comm_master_tx(ADDR, test_buf));
}

TEST(comm_master, arg_addr)
{
	TEST_ASSERT_EQUAL(COMM_ERR_INVALID, comm_master_tx(0x0000, test_buf));
	TEST_ASSERT_EQUAL(COMM_ERR_OK, comm_master_tx(0x0001, test_buf));
	TEST_ASSERT_EQUAL(COMM_ERR_OK, comm_master_tx(0xFFFE, test_buf));
	TEST_ASSERT_EQUAL(COMM_ERR_INVALID, comm_master_tx(0xFFFF, test_buf));
}

TEST(comm_master, frame_addr)
{
   comm_addr_t addr_expected;
   comm_addr_t addr_actual;

   /* Given address provided. */
   addr_expected = ADDR;

   /* When tested function is called. */
   comm_master_tx(addr_expected, test_buf);

   /* Then address in frame buffer matches address provided. */
   memcpy(&addr_actual, &test_buf[0], sizeof(comm_addr_t));
   TEST_ASSERT_EQUAL_HEX16(addr_expected, addr_actual);
}
