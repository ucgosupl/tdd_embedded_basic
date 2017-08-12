#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "unity/fixture/unity_fixture.h"

#include "comm/comm_master.h"
#include "mocks/comm_master_mocks.h"

#define TEST_BUF_SIZE	32
#define ADDR			15
#define SEQ				0xAA55
#define CRC				0xCC33

uint8_t test_buf[TEST_BUF_SIZE];

static void prepare_buf(uint8_t *buf, comm_addr_t addr, comm_seq_t seq);

TEST_GROUP(comm_master_rx);

TEST_SETUP(comm_master_rx)
{
   memset(test_buf, 0xAA, TEST_BUF_SIZE);

   mock_comm_crc_init(0);
   mock_comm_table_seq_init(SEQ);
   prepare_buf(test_buf, ADDR, SEQ + 1);
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

TEST(comm_master_rx, frame_crc_args)
{
	comm_master_rx(test_buf);

	TEST_ASSERT_EQUAL(1, mock_comm_crc_cnt_get());
	TEST_ASSERT_EQUAL_PTR(test_buf, mock_comm_crc_arg_buf_get());
	TEST_ASSERT_EQUAL(COMM_FRAME_SIZE, mock_comm_crc_arg_len_get());
}

TEST(comm_master_rx, frame_addr)
{
	comm_addr_t addr;

	/* Given frame buffer content with specific addr value. */
	addr = ADDR;
	prepare_buf(test_buf, addr, SEQ);
	mock_comm_table_seq_init(0);

	/* When tested function is called. */
	comm_master_rx(test_buf);

	/* Address from frame buffer is passed to comm table function. */
	TEST_ASSERT_EQUAL(1, mock_comm_table_seq_cnt_get());
	TEST_ASSERT_EQUAL(addr, mock_comm_table_seq_arg_addr_get());
}

TEST(comm_master_rx, frame_seq)
{
	comm_seq_t seq_read;
	comm_seq_t seq_sent;

	seq_read = SEQ + 1;
	seq_sent = SEQ;
	mock_comm_table_seq_init(seq_sent);
	prepare_buf(test_buf, ADDR, seq_read);

	TEST_ASSERT_EQUAL(COMM_ERR_OK, comm_master_rx(test_buf));

	seq_read = SEQ;
	seq_sent = SEQ;
	mock_comm_table_seq_init(seq_sent);
	prepare_buf(test_buf, ADDR, seq_read);

	TEST_ASSERT_EQUAL(COMM_ERR_SEQ, comm_master_rx(test_buf));
}

TEST(comm_master_rx, frame_seq_overflow)
{
	comm_seq_t seq_read;
	comm_seq_t seq_sent;

	seq_read = 0;
	seq_sent = 0xFFFF;
	mock_comm_table_seq_init(seq_sent);
	prepare_buf(test_buf, ADDR, seq_read);

	TEST_ASSERT_EQUAL(COMM_ERR_OK, comm_master_rx(test_buf));
}

static void prepare_buf(uint8_t *buf, comm_addr_t addr, comm_seq_t seq)
{
	memcpy(&buf[0], &addr, sizeof(comm_addr_t));
	memcpy(&buf[2], &seq, sizeof(comm_seq_t));
}
