#include <stdint.h>
#include <stddef.h>

#include "comm_master.h"

int32_t comm_master_tx(uint16_t addr, uint8_t *buf)
{
	(void) addr;

	if (NULL == buf)
	{
		return COMM_ERR_INVALID;
	}

	return COMM_ERR_OK;
}
