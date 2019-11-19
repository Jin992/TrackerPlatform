#pragma once
#include <cstdint>

namespace TrackingPlatform {
	class PWMRange {
	public:
		PWMRange(uint16_t channel_id, uint32_t begin, uint32_t center, uint32_t end, uint16_t range, uint32_t speed = 0, uint32_t acceleration = 0);
		uint32_t begin() const;
		uint32_t center() const;
		uint32_t end() const;
		uint32_t speed() const;
		uint32_t acceleration() const;
		uint16_t channel_id() const;
		float	 one_degree_pos() const;
		float	 one_degree_neg() const;

	private:
		void _calculate_one_degree_pwm(uint16_t range);

	private:
		uint32_t _pwm_begin;
		uint32_t _pwm_center;
		uint32_t _pwm_end;
		uint32_t _speed;
		uint32_t _acceleration;
		uint16_t _channel_id;
		float	 _one_degree_pos;
		float	 _one_degree_neg;
	};
}