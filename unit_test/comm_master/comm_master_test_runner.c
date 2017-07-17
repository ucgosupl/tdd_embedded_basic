#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(comm_master_tx)
{
   RUN_TEST_CASE(comm_master_tx, arg_buf);
   RUN_TEST_CASE(comm_master_tx, arg_addr);

   RUN_TEST_CASE(comm_master_tx, addr);
   RUN_TEST_CASE(comm_master_tx, seq);
   RUN_TEST_CASE(comm_master_tx, crc);
}

TEST_GROUP_RUNNER(comm_master_rx)
{
   RUN_TEST_CASE(comm_master_rx, arg_buf);

   RUN_TEST_CASE(comm_master_rx, crc_ret);
   RUN_TEST_CASE(comm_master_rx, crc_args);

   RUN_TEST_CASE(comm_master_rx, addr);
   RUN_TEST_CASE(comm_master_rx, seq);
}
