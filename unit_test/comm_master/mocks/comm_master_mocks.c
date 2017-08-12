#include <stdint.h>

#include "comm/comm_master.h"
#include "comm/comm_table.h"

#include "comm_master_mocks.h"

struct mock_params
{
	int32_t comm_table_seq_cnt;
	comm_addr_t comm_table_seq_arg_addr;
	comm_seq_t comm_table_seq_ret;
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
