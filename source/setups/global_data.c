#include <stdint.h>
#include <stdbool.h>

#include <xdc/runtime/System.h>

#include <setups/global_data.h>


struct EnvironmentData _environment_data;


void init_environment_data(void){
	_environment_data.index_temp = 0;
	_environment_data.index_light = 0;
	_environment_data.is_initialized = true;
}

bool _is_valid_environment_data(void){
	if (_environment_data.is_initialized){
		if((_environment_data.index_light >= STORAGE_SIZE) &&
		   ((_environment_data.index_temp >= STORAGE_SIZE))){
			_environment_data.index_light = 0;
			_environment_data.index_temp = 0;
		}
		return true;
	}
	return false;
}

void _error_message(void){
	System_printf("Произошла ошибка при работе с данными \n");
	System_flush();
}

void append_environment_data(uint32_t temp, uint32_t light){
	if(_is_valid_environment_data()){
		_environment_data.temp[_environment_data.index_temp] = temp;
		_environment_data.index_light++;

		_environment_data.light[_environment_data.index_light] = light;
		_environment_data.index_light++;
	} else {
		_error_message();
	}
}

uint32_t* get_environment_temps(void){
	return _environment_data.temp;
}

uint32_t* get_environment_lights(void){
	return _environment_data.light;
}
