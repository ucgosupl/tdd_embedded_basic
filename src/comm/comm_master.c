#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "comm_master.h"
#include "comm_table.h"
#include "comm_crc.h"

int32_t comm_master_tx(comm_addr_t addr, uint8_t *buf)
{
	comm_seq_t seq;
	comm_crc_t crc;

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

	crc = comm_crc_get(buf, COMM_FRAME_NO_CRC_SIZE);
	memcpy(&buf[COMM_FRAME_NO_CRC_SIZE], &crc, COMM_FRAME_NO_CRC_SIZE);

	return COMM_ERR_OK;
}

int32_t comm_master_rx(uint8_t *buf)
{
	if (NULL == buf)
	{
		return COMM_ERR_INVALID;
	}

	return COMM_ERR_OK;
}
