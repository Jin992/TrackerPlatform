#pragma once

#include "Config.h"
#include "RPMSerialInterface.h"
#include "PWMRange.h"
#include "Utils.h"
#include "Range.h"
#include "CustomException.h"

namespace TrackingPlatform {

	class TrackingPlatform {
	public:
		TrackingPlatform();
		~TrackingPlatform();

		bool	open(std::string com_port_name, unsigned int baudRate);

		bool	move_to_athimuth(float athimuth, float pwm_timeout);
		bool	 elevate_to(float elevation, float pwm_timeout);
		void	to_postion(float athim, float elev);

	private:
		bool	_init();
		float	_timer_mod(float pwm_distance);
		

	private:
		uint32_t				_maestro_id;	// Maestro board id
		PWMRange				_pan;			// Range of pan servo
		PWMRange				_tilt;			// Range of tilt servo
		RPM::SerialInterface*   _serial_port;	// Serial port object
		int32_t					_cur_pwm;		// Current pan pwm TODO remove
		int32_t					_pan_prev_pwm;	// Previous pan pwm position
		int32_t					_tilt_prev_pwm; // Previous tilt pwm position
	};
}