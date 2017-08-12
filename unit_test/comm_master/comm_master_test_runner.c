#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(comm_master)
{
   RUN_TEST_CASE(comm_master, arg_buf);
   RUN_TEST_CASE(comm_master, arg_addr);

   RUN_TEST_CASE(comm_master, frame_addr);
   RUN_TEST_CASE(comm_master, frame_seq);
}
