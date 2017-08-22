# Requirements
Frame format:
| ADDR - 2B | SEQ - 2B | PAYLOAD - 10B | CRC - 2B |

* Frame length is constant and is 16B
* Master could communicate with many Slaves independently
* Only Slaves have addresses, there is only one Master connected to them and it doesn't have any address
* Communication Master sends request and expects response from a Slave with a given address
* Request and response frames have the same format
* Master sends frame with a given SEQ and slave responds with SEQ + 1
* In next request Master sends SEQ + 2 etc.
* When frame has incorrect SEQ nr it is rejected.
* SEQ is counted separately for every Slave.
* Slave ADDR cannot be 0x0000 and 0xFFFF
* Tx frame payload is filled on upper layers of the application
* Rx frame payload is read on upper layers of the application
* CRC polynomial and implementation details are not known yet so it must be moved to the separate module

# Task
Implement Master tx and rx functions.

# Bug
After implementation bug is found - when request SEQ is 0xFFFF and response SEQ is 0x0000 frame is rejected but should be accepted.

# Requirements change
CRC size increased to 4B, payload decreased to 8B
