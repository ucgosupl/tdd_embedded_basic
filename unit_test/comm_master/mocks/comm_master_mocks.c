#include <stdint.h>
#include <stddef.h>

#include "comm/comm_master.h"
#include "comm/comm_table.h"

#include "comm_master_mocks.h"

struct mock_params
{
	int32_t comm_table_seq_cnt;
	comm_addr_t comm_table_seq_arg_addr;
	comm_seq_t comm_table_seq_ret;

	int32_t comm_crc_cnt;
	uint8_t *comm_crc_arg_buf;
	int32_t comm_crc_arg_len;
	comm_crc_t comm_crc_ret;
};

static struct mock_params mock_data;

void mock_comm_table_seq_init(comm_seq_t req)
{
	mock_data.comm_table_seq_cnt = 0;

	mock_data.comm_table_seq_arg_addr = 0;

	mock_data.comm_table_seq_ret = req;
}

int32_t mock_comm_table_seq_cnt_get(void)
{
	return mock_data.comm_table_seq_cnt;
}

comm_addr_t mock_comm_table_seq_arg_addr_get(void)
{
	return mock_data.comm_table_seq_arg_addr;
}

comm_seq_t comm_table_seq_get(comm_addr_t addr)
{
	mock_data.comm_table_seq_cnt++;

	mock_data.comm_table_seq_arg_addr = addr;

	return mock_data.comm_table_seq_ret;
}

void mock_comm_crc_init(comm_crc_t ret)
{
	mock_data.comm_crc_cnt = 0;

	mock_data.comm_crc_arg_buf = NULL;
	mock_data.comm_crc_arg_len = -1;

	mock_data.comm_crc_ret = ret;
}

int32_t mock_comm_crc_cnt_get(void)
{
	return mock_data.comm_crc_cnt;
}

uint8_t * mock_comm_crc_arg_buf_get(void)
{
	return mock_data.comm_crc_arg_buf;
}

int32_t mock_comm_crc_arg_len_get(void)
{
	return mock_data.comm_crc_arg_len;
}

comm_crc_t comm_crc_get(uint8_t *buf, int32_t len)
{
	mock_data.comm_crc_cnt++;

	mock_data.comm_crc_arg_buf = buf;
	mock_data.comm_crc_arg_len = len;

	return mock_data.comm_crc_ret;
}
