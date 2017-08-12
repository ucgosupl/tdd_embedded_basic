#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(comm_master_tx)
{
   RUN_TEST_CASE(comm_master_tx, arg_buf);
   RUN_TEST_CASE(comm_master_tx, arg_addr);

   RUN_TEST_CASE(comm_master_tx, frame_addr);
   RUN_TEST_CASE(comm_master_tx, frame_seq);
   RUN_TEST_CASE(comm_master_tx, frame_crc);
}

TEST_GROUP_RUNNER(comm_master_rx)
{
   RUN_TEST_CASE(comm_master_rx, arg_buf);

   RUN_TEST_CASE(comm_master_rx, frame_crc_ret);
}
