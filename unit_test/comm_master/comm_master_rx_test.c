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

   mock_comm_crc_init(0);
}

TEST_TEAR_DOWN(comm_master_rx)
{
   /* Cleanup after every test */
}

TEST(comm_master_rx, arg_buf)
{
	TEST_ASSERT_EQUAL(COMM_ERR_INVALID, comm_master_rx(NULL));
	TEST_ASSERT_EQUAL(COMM_ERR_OK, comm_master_rx(test_buf));
}

TEST(comm_master_rx, frame_crc_ret)
{
	mock_comm_crc_init(0);

	TEST_ASSERT_EQUAL(COMM_ERR_OK, comm_master_rx(test_buf));

	mock_comm_crc_init(0xFFFF);

	TEST_ASSERT_EQUAL(COMM_ERR_CRC, comm_master_rx(test_buf));
}
