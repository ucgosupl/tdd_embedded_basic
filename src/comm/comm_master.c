#include <stdint.h>
#include <stddef.h>

#include "comm_master.h"

int32_t comm_master_tx(comm_addr_t addr, uint8_t *buf)
{
	(void) addr;

	if (NULL == buf)
	{
		return COMM_ERR_INVALID;
	}

	if ((0x0000 == addr) || (0xFFFF == addr))
	{
		return COMM_ERR_INVALID;
	}

	return COMM_ERR_OK;
}
