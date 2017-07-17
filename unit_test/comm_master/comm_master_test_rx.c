#include "unity/fixture/unity_fixture.h"

#include <errno.h>
#include <stddef.h>
#include <string.h>

#include "comm/comm_master.h"

#include "mocks/comm_master_mocks.h"

#define ADDR			15
#define SEQ				0xAA55
#define CRC				0xCC33

#define BUF_SIZE		32

uint8_t test_buf[BUF_SIZE];

static void prepare_buf(uint8_t *buf, comm_addr_t addr, comm_seq_t seq, comm_crc_t crc);

TEST_GROUP(comm_master_rx);

TEST_SETUP(comm_master_rx)
{
	int32_t i;

	for (i = 0; i < BUF_SIZE; i++)
	{
	   test_buf[i] = 0xAA;
	}

	mock_comm_crc_init(0);
	mock_comm_table_seq_init(SEQ);
	prepare_buf(test_buf, ADDR, SEQ + 1, CRC);
}

TEST_TEAR_DOWN(comm_master_rx)
{
   /* Cleanup after every test */
}

TEST(comm_master_rx, arg_buf)
{
   TEST_ASSERT_EQUAL(-EINVAL, comm_master_rx(NULL));
   TEST_ASSERT_EQUAL(0, comm_master_rx(test_buf));
}

TEST(comm_master_rx, crc_ret)
{
	mock_comm_crc_init(0);

	TEST_ASSERT_EQUAL(0, comm_master_rx(test_buf));

	mock_comm_crc_init(0xFFFF);

	TEST_ASSERT_EQUAL(-EPERM, comm_master_rx(test_buf));
}

TEST(comm_master_rx, crc_args)
{
	comm_master_rx(test_buf);

	TEST_ASSERT_EQUAL(1, mock_comm_crc_cnt_get());
	TEST_ASSERT_EQUAL_PTR(test_buf, mock_comm_crc_arg_buf_get());
	TEST_ASSERT_EQUAL(COMM_FRAME_SIZE, mock_comm_crc_arg_len_get());
}

TEST(comm_master_rx, addr)
{
	comm_addr_t addr;

	addr = ADDR;
	mock_comm_table_seq_init(0);
	prepare_buf(test_buf, addr, SEQ, CRC);

	comm_master_rx(test_buf);

	TEST_ASSERT_EQUAL(1, mock_comm_table_seq_cnt_get());
	TEST_ASSERT_EQUAL(addr, mock_comm_table_seq_arg_addr_get());
}

TEST(comm_master_rx, seq)
{
	comm_seq_t seq_read;
	comm_seq_t seq_sent;

	seq_read = SEQ + 1;
	seq_sent = SEQ;
	mock_comm_table_seq_init(seq_sent);
	prepare_buf(test_buf, ADDR, seq_read, CRC);

	TEST_ASSERT_EQUAL(0, comm_master_rx(test_buf));

	seq_read = SEQ;
	seq_sent = SEQ;
	mock_comm_table_seq_init(seq_sent);
	prepare_buf(test_buf, ADDR, seq_read, CRC);

	TEST_ASSERT_EQUAL(-EPERM, comm_master_rx(test_buf));
}

static void prepare_buf(uint8_t *buf, comm_addr_t addr, comm_seq_t seq, comm_crc_t crc)
{
	memcpy(&buf[0], &addr, sizeof(comm_addr_t));
	memcpy(&buf[2], &seq, sizeof(comm_seq_t));
	memcpy(&buf[COMM_FRAME_NO_CRC_SIZE], &crc, sizeof(comm_crc_t));
}
