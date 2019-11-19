#include "PWMRange.h"


namespace TrackingPlatform {
	PWMRange::PWMRange(uint16_t channel_id, uint32_t begin, uint32_t center, uint32_t end, uint16_t range, uint32_t speed, uint32_t acceleration)
		: _pwm_begin(begin), _pwm_center(center), _pwm_end(end), _speed(speed), _acceleration(acceleration), _channel_id(channel_id) {
		_calculate_one_degree_pwm(range);
	}

	uint32_t PWMRange::begin() const {
		return _pwm_begin;
	}

	uint32_t PWMRange::center() const {
		return _pwm_center;
	}

	uint32_t PWMRange::end() const {
		return _pwm_end;
	}

	uint32_t PWMRange::speed() const {
		return _speed;
	}

	uint32_t PWMRange::acceleration() const {
		return _acceleration;
	}

	uint16_t PWMRange::channel_id() const {
		return _channel_id;
	}

	float	 PWMRange::one_degree_pos() const {
		return _one_degree_pos;
	}

	float	 PWMRange::one_degree_neg() const {
		return _one_degree_neg;
	}

	void PWMRange::_calculate_one_degree_pwm(uint16_t range) {
		_one_degree_pos = (_pwm_end - _pwm_begin) / range;
		_one_degree_neg = (_pwm_end - _pwm_begin) / range;
	}
}