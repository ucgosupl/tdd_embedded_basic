#ifndef _COMM_MASTER_H_
#define _COMM_MASTER_H_

enum
{
	COMM_ERR_OK = 0,
	COMM_ERR_INVALID = -1,
};

int32_t comm_master_tx(uint16_t addr, uint8_t *buf);

#endif /* _COMM_MASTER_H_ */
