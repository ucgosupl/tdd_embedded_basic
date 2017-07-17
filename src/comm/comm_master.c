#include <stdint.h>
#include <stddef.h>
#include <errno.h>
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
		return -EINVAL;
	}

	if ((0x0000 == addr) || (0xFFFF == addr))
	{
		return -EINVAL;
	}

	memcpy(&buf[0], &addr, sizeof(comm_addr_t));

	seq = comm_table_seq_get(addr);
	memcpy(&buf[2], &seq, sizeof(comm_seq_t));

	crc = comm_crc_get(buf, COMM_FRAME_NO_CRC_SIZE);
	memcpy(&buf[COMM_FRAME_NO_CRC_SIZE], &crc, COMM_FRAME_NO_CRC_SIZE);

	return 0;
}

int32_t comm_master_rx(uint8_t *buf)
{
	comm_addr_t addr;
	comm_seq_t seq_read;
	comm_seq_t seq_sent;
	comm_crc_t crc;

	if (NULL == buf)
	{
		return -EINVAL;
	}

	crc = comm_crc_get(buf, COMM_FRAME_SIZE);
	if (0 != crc)
	{
		return -EPERM;
	}

	memcpy(&addr, &buf[0], sizeof(comm_addr_t));
	seq_sent = comm_table_seq_get(addr);

	memcpy(&seq_read, &buf[2], sizeof(comm_seq_t));

	if (seq_sent + 1 != seq_read)
	{
		return -EPERM;
	}

	return 0;
}
