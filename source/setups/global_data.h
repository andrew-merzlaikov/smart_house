#ifndef SETUPS_GLOBAL_H_
#define SETUPS_GLOBAL_H_

#include <stdint.h>

#define STORAGE_SIZE 1024

struct Environment_Data {
	uint32_t temp[STORAGE_SIZE];
	uint32_t light[STORAGE_SIZE];
};


void hardware_init(void);

#endif /* SETTINGS_SETUP_H_ */
