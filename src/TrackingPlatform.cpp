#include "TrackingPlatform.h"
#include "CustomException.h"
#include <iostream>

namespace TrackingPlatform {
	TrackingPlatform::TrackingPlatform()
		: _maestro_id(MAESTRO_ID),
		_pan(PAN_ID, PAN_PWM_BEGIN, PAN_PWM_CENTER, PAN_PWM_END, PAN_RANGE),
		_tilt(TILT_ID, TILT_PWM_BEGIN, TILT_PWM_CENTER, TILT_PWM_END, TILT_RANGE),
		_pan_prev_pwm(_pan.center()), _tilt_prev_pwm(_tilt.end())
	{}

	TrackingPlatform::~TrackingPlatform() {
		delete _serial_port;
	}

	bool TrackingPlatform::open(std::string com_port_name, unsigned int baudRate) {
		std::string error_msg;
		_serial_port = RPM::SerialInterface::createSerialInterface(com_port_name, baudRate, &error_msg);
		if (!_serial_port) {
			throw CustomException("TrackingPlatform::open : Failed to create serial interface.");
			return false;
		}
		_init();
		return true;
	}

	bool TrackingPlatform::_init() {
		bool ret = false;
		ret = _serial_port->setSpeedCP(_pan.channel_id(), _pan.speed());
		if (!ret)
			throw CustomException("TrackingPlatform::_init : Failet to set pan speed.");
		ret = _serial_port->setAccelerationCP(_pan.channel_id(), _pan.acceleration());
		if (!ret)
			throw CustomException("TrackingPlatform::_init : Failet to set pan acceleration.");

		ret = _serial_port->setSpeedCP(_tilt.channel_id(), _tilt.speed());
		if (!ret)
			throw CustomException("TrackingPlatform::_init : Failet to set tilt speed.");
		ret = _serial_port->setAccelerationCP(_tilt.channel_id(), _tilt.acceleration());
		if (!ret)
			throw CustomException("TrackingPlatform::_init : Failet to set tilt acceleration.");
		return true;
	}

	bool TrackingPlatform::move_to_athimuth(float athimuth, float pwm_timeout) {
		bool ret = false;
		// Calculate pwm value from degree
		int32_t move_pwm = abs(round(athimuth * (_pan.one_degree_pos() + 0.8)));
		if (athimuth >= 0) {
			_cur_pwm = _pan.center() - move_pwm;
			if (_cur_pwm < _pan.begin())
				return false;
		}
		else {
			_cur_pwm = _pan.center() + move_pwm;;
			if (_cur_pwm > _pan.end())
				return false;
		}
		float distance_to_move = abs(_pan_prev_pwm - _cur_pwm);
		int32_t timer = abs(distance_to_move * pwm_timeout) - _timer_mod(distance_to_move) * (pwm_timeout / 10) + 400;

		_pan_prev_pwm = _cur_pwm;
		ret = _serial_port->setTargetPP(_maestro_id, _pan.channel_id(), _cur_pwm);

		Utils::sleep(timer);
		return ret;
	}

	bool TrackingPlatform::elevate_to(float elevation, float pwm_timeout) {
		bool ret = false;
		//
		int32_t move_pwm = abs(round(elevation * (_tilt.one_degree_pos())));
		int32_t pwm = 0;
		if (elevation >= 0 && elevation <= 90) {
			pwm = _tilt.end() - move_pwm;
			//std::cout << "pwm " << pwm << " begin " << _tilt.begin() << " end " << _tilt.end() << std::endl;
			if (pwm < _tilt.begin() || pwm > _tilt.end())
				return false;
			int32_t timer = abs(abs((_tilt_prev_pwm - pwm) * pwm_timeout) - _timer_mod(abs(_tilt_prev_pwm - pwm) * (pwm_timeout / 8)));
			_tilt_prev_pwm = pwm;
			ret = _serial_port->setTargetPP(_maestro_id, _tilt.channel_id(), pwm);
			Utils::sleep(timer);
		}
		return ret;
	}

	float	TrackingPlatform::_timer_mod(float pwm_distance) {
		float timer_mod = 0.0;
		if (pwm_distance >= 216 && pwm_distance < 432)
			timer_mod = pwm_distance * PWM_DISTANCE_MOD_45;
		else if (pwm_distance >= 432 && pwm_distance < 648)
			timer_mod = pwm_distance * PWM_DISTANCE_MOD_90;
		else if (pwm_distance >= 648 && pwm_distance < 864)
			timer_mod = pwm_distance * PWM_DISTANCE_MOD_135;
		else if (pwm_distance >= 864 && pwm_distance < 1080)
			timer_mod = pwm_distance * PWM_DISTANCE_MOD_180;
		else if (pwm_distance >= 1080)
			timer_mod = pwm_distance * PWM_DISTANCE_MOD_360;
		return timer_mod;
	}
}