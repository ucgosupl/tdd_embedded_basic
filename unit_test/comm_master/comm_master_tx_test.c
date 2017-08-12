#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "unity/fixture/unity_fixture.h"

#include "comm/comm_master.h"
#include "mocks/comm_master_mocks.h"

#define TEST_BUF_SIZE	32
#define ADDR			15

uint8_t test_buf[TEST_BUF_SIZE];

TEST_GROUP(comm_master_tx);

TEST_SETUP(comm_master_tx)
{
   memset(test_buf, 0xAA, TEST_BUF_SIZE);
}

TEST_TEAR_DOWN(comm_master_tx)
{
   /* Cleanup after every test */
}

TEST(comm_master_tx, arg_buf)
{
	TEST_ASSERT_EQUAL(COMM_ERR_INVALID, comm_master_tx(ADDR, NULL));
	TEST_ASSERT_EQUAL(COMM_ERR_OK, comm_master_tx(ADDR, test_buf));
}

TEST(comm_master_tx, arg_addr)
{
	TEST_ASSERT_EQUAL(COMM_ERR_INVALID, comm_master_tx(0x0000, test_buf));
	TEST_ASSERT_EQUAL(COMM_ERR_OK, comm_master_tx(0x0001, test_buf));
	TEST_ASSERT_EQUAL(COMM_ERR_OK, comm_master_tx(0xFFFE, test_buf));
	TEST_ASSERT_EQUAL(COMM_ERR_INVALID, comm_master_tx(0xFFFF, test_buf));
}

TEST(comm_master_tx, frame_addr)
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

TEST(comm_master_tx, frame_seq)
{
	comm_seq_t seq_expected;
	comm_seq_t seq_actual;

	/* Given sequence number provided to conn table. */
	seq_expected = 0xAA55;
	mock_comm_table_seq_init(seq_expected);

	/* When tested function is called. */
	comm_master_tx(ADDR, test_buf);

	/* Then seq nr in frame buffer matches seq nr provided. */
	memcpy(&seq_actual, &test_buf[2], sizeof(comm_seq_t));
	TEST_ASSERT_EQUAL_HEX16(seq_expected, seq_actual);

	/* Check if conn table function was called with correct address as argument. */
	TEST_ASSERT_EQUAL(1, mock_comm_table_seq_cnt_get());
	TEST_ASSERT_EQUAL(ADDR, mock_comm_table_seq_arg_addr_get());
}

TEST(comm_master_tx, frame_crc)
{
	comm_crc_t crc_expected;
	comm_crc_t crc_actual;

	/* Given CRC provided to CRC module. */
	crc_expected = 0x55AA;
	mock_comm_crc_init(crc_expected);

	/* When tested function is called. */
	comm_master_tx(ADDR, test_buf);

	/* Then CRC in frame buffer matches CRC provided. */
	memcpy(&crc_actual, &test_buf[COMM_FRAME_NO_CRC_SIZE], sizeof(comm_crc_t));
	TEST_ASSERT_EQUAL_HEX16(crc_expected, crc_actual);

	/* Check if CRC function was called with correct arguments. */
	TEST_ASSERT_EQUAL(1, mock_comm_crc_cnt_get());
	TEST_ASSERT_EQUAL_PTR(test_buf, mock_comm_crc_arg_buf_get());
	TEST_ASSERT_EQUAL(COMM_FRAME_NO_CRC_SIZE, mock_comm_crc_arg_len_get());
}
