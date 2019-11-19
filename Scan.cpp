#include "Scan.h"


namespace TrackingPlatform {

	Scan::Scan(TrackingPlatform& tracker)
		:_tracker(tracker)
	{}

	Scan::Scan(TrackingPlatform& tracker, Range pan, Range tilt, std::function<bool(float, float)> callback)
		: _tracker(tracker), _pan(pan), _tilt(tilt), _callback(callback)
	{}

	void Scan::set_callback(std::function<bool(float, float)> func) {
		_callback = func;
	}
	void Scan::set_tilt(Range tilt) {
		_tilt = tilt;
	}
	void Scan::set_pan(Range pan) {
		_pan = pan;
	}

	TrackingPlatform& Scan::tracker() {
		return _tracker;
	}
	bool Scan::callback(float athim, float elev) {
		if (_callback)
			return _callback(athim, elev);
		return false;
	}

	Range& Scan::pan() {
		return _pan;
	}
	Range& Scan::tilt() {
		return _tilt;
	}
}