#include "unity/fixture/unity_fixture.h"

#include <stdio.h>

static void run_all_tests(void);

int main(int argc, const char **argv)
{
   UnityMain(argc, argv, run_all_tests);

   return 0;
}

static void run_all_tests(void)
{
	printf("Tx tests:\n");
	RUN_TEST_GROUP(comm_master_tx);
	printf("\nRx tests:\n");
	RUN_TEST_GROUP(comm_master_rx);
}
