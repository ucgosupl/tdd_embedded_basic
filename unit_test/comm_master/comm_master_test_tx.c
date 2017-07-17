#include "unity/fixture/unity_fixture.h"

#include <errno.h>
#include <stddef.h>
#include <string.h>

#include "comm/comm_master.h"

#include "mocks/comm_master_mocks.h"

#define ADDR			15
#define BUF_SIZE		32

uint8_t test_buf[BUF_SIZE];

TEST_GROUP(comm_master_tx);

TEST_SETUP(comm_master_tx)
{
   int32_t i;

   for (i = 0; i < BUF_SIZE; i++)
   {
	   test_buf[i] = 0xAA;
   }
}

TEST_TEAR_DOWN(comm_master_tx)
{
   /* Cleanup after every test */
}

TEST(comm_master_tx, arg_buf)
{
   TEST_ASSERT_EQUAL(-EINVAL, comm_master_tx(ADDR, NULL));
   TEST_ASSERT_EQUAL(0, comm_master_tx(ADDR, test_buf));
}

TEST(comm_master_tx, arg_addr)
{
	TEST_ASSERT_EQUAL(-EINVAL, comm_master_tx(0x0000, test_buf));
	TEST_ASSERT_EQUAL(0, comm_master_tx(0x0001, test_buf));
	TEST_ASSERT_EQUAL(0, comm_master_tx(0xFFFE, test_buf));
	TEST_ASSERT_EQUAL(-EINVAL, comm_master_tx(0xFFFF, test_buf));
}

TEST(comm_master_tx, addr)
{
	comm_addr_t addr_expected;
	comm_addr_t addr_actual;

	addr_expected = ADDR;

	comm_master_tx(addr_expected, test_buf);

	memcpy(&addr_actual, &test_buf[0], sizeof(comm_addr_t));
	TEST_ASSERT_EQUAL_HEX(addr_expected, addr_actual);
}

TEST(comm_master_tx, seq)
{
	comm_seq_t seq_expected;
	comm_seq_t seq_actual;

	seq_expected = 0xAA55;
	mock_comm_table_seq_init(seq_expected);

	comm_master_tx(ADDR, test_buf);

	memcpy(&seq_actual, &test_buf[2], sizeof(comm_seq_t));
	TEST_ASSERT_EQUAL_HEX(seq_expected, seq_actual);
	TEST_ASSERT_EQUAL(1, mock_comm_table_seq_cnt_get());
	TEST_ASSERT_EQUAL(ADDR, mock_comm_table_seq_arg_addr_get());
}

TEST(comm_master_tx, crc)
{
	comm_crc_t crc_expected;
	comm_crc_t crc_actual;

	crc_expected = 0x55AA;
	mock_comm_crc_init(crc_expected);

	comm_master_tx(ADDR, test_buf);

	memcpy(&crc_actual, &test_buf[COMM_FRAME_NO_CRC_SIZE], sizeof(comm_seq_t));
	TEST_ASSERT_EQUAL_HEX(crc_expected, crc_actual);
	TEST_ASSERT_EQUAL(1, mock_comm_crc_cnt_get());
	TEST_ASSERT_EQUAL_PTR(test_buf, mock_comm_crc_arg_buf_get());
	TEST_ASSERT_EQUAL(COMM_FRAME_NO_CRC_SIZE, mock_comm_crc_arg_len_get());
}
