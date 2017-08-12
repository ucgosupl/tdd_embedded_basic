#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "comm_master.h"
#include "comm_table.h"

int32_t comm_master_tx(comm_addr_t addr, uint8_t *buf)
{
	comm_seq_t seq;

	if (NULL == buf)
	{
		return COMM_ERR_INVALID;
	}

	if ((0x0000 == addr) || (0xFFFF == addr))
	{
		return COMM_ERR_INVALID;
	}

	memcpy(&buf[0], &addr, sizeof(comm_addr_t));

	seq = comm_table_seq_get(addr);
	/* What if address provided is not in conn table and seq is invalid? */
	memcpy(&buf[2], &seq, sizeof(comm_seq_t));

	return COMM_ERR_OK;
}
