#ifndef _COMM_MASTER_MOCKS_H_
#define _COMM_MASTER_MOCKS_H_

void mock_comm_table_seq_init(comm_seq_t req);
int32_t mock_comm_table_seq_cnt_get(void);
comm_addr_t mock_comm_table_seq_arg_addr_get(void);

#endif /* _COMM_MASTER_MOCKS_H_ */
