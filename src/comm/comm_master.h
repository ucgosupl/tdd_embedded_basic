#ifndef _COMM_MASTER_H_
#define _COMM_MASTER_H_

#define COMM_FRAME_SIZE			16
#define COMM_FRAME_NO_CRC_SIZE	(COMM_FRAME_SIZE - sizeof(comm_crc_t))

typedef uint16_t comm_addr_t;
typedef uint16_t comm_seq_t;
typedef uint16_t comm_crc_t;

enum
{
	COMM_ERR_OK = 0,
	COMM_ERR_INVALID = -1,
	COMM_ERR_CRC = -2,
};

int32_t comm_master_tx(comm_addr_t addr, uint8_t *buf);
int32_t comm_master_rx(uint8_t *buf);

#endif /* _COMM_MASTER_H_ */
