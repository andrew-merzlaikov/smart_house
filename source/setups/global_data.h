#ifndef SETUPS_GLOBAL_H_
#define SETUPS_GLOBAL_H_

#include <stdint.h>
#include <stdbool.h>

#define STORAGE_SIZE 1024

struct EnvironmentData {
	uint32_t index_temp;
	uint32_t index_light;
	uint32_t temp[STORAGE_SIZE];
	uint32_t light[STORAGE_SIZE];
	bool is_initialized;
};


void init_environment_data(void);
void append_environment_data(uint32_t temp, uint32_t light);
uint32_t* get_environment_temps(void);
uint32_t* get_environment_lights(void);


#endif /* SETTINGS_SETUP_H_ */
