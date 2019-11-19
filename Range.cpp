#include "Range.h"
#include "CustomException.h"


namespace TrackingPlatform {
	Range::Range() : _begin(0), _end(90), _step(1), _pwm_timeout(10)
	{}

	Range::Range(float begin, float end, float step, float pwm_timeout) {
		set_begin(begin);
		set_end(end);
		set_step(step);
		set_pwm_timeout(pwm_timeout);
	}

	void Range::set_begin(float begin) {
		if (begin < -360 || begin > 360)
			throw CustomException("Range::set_begin : bad range");
		_begin = begin;
	}

	void Range::set_end(float end) {
		if (end < -360 || end > 360)
			throw CustomException("Range::set_end : bad range");
		_end = end;
	}

	void Range::set_step(float step) {
		if (step <= 0 || step > 360)
			throw CustomException("Range::set_step : bad step size");
		_step = step;
	}

	void Range::set_pwm_timeout(float timeout) {
		if (timeout <= 0)
			throw CustomException("Range::set_pwm_timeout : bad timeout");
		_pwm_timeout = timeout;
	}

	float Range::begin() {
		return _begin;
	}

	float Range::end() {
		return _end;
	}

	float Range::step() {
		return _step;
	}

	float Range::pwm_timeout() {
		return _pwm_timeout;
	}
}