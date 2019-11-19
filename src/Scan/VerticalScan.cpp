#include "VerticalScan.h"


namespace TrackingPlatform {
	VerticalScan::VerticalScan(TrackingPlatform& tracker)
		: Scan(tracker)
	{}

	VerticalScan::VerticalScan(TrackingPlatform& tracker, Range pan, Range tilt, std::function<bool(float, float)> callback)
		: Scan(tracker, pan, tilt, callback)
	{}

	void VerticalScan::scan() {
		for (float i = pan().begin(); i <= pan().end(); i += pan().step()) {
			tracker().move_to_athimuth(i, pan().pwm_timeout());
			for (float j = tilt().begin(); j <= tilt().end(); j += tilt().step()) {
				tracker().elevate_to(j, tilt().pwm_timeout());
				if (!callback(j, i)) // invoke callback
					break;
			}


			i += pan().step();
			tracker().move_to_athimuth(i, pan().pwm_timeout());

			for (float j = tilt().end(); j >= tilt().begin(); j -= tilt().step()) {
				tracker().elevate_to(j, tilt().pwm_timeout());
				if (!callback(j, i)) // invoke callback
					break;
			}
		}
	}

	void VerticalScan::rscan() {
		for (float i = pan().begin(); i <= pan().end(); i += pan().step()) {
			tracker().move_to_athimuth(i, pan().pwm_timeout());

			for (float j = tilt().end(); j >= tilt().begin(); j -= tilt().step()) {
				tracker().elevate_to(j, tilt().pwm_timeout());
				if (!callback(j, i)) // invoke callback
					break;
			}

			i += pan().step();
			tracker().move_to_athimuth(i, pan().pwm_timeout());

			for (float j = tilt().begin(); j <= tilt().end(); j += tilt().step()) {
				tracker().elevate_to(j, tilt().pwm_timeout());
				if (!callback(j, i)) // invoke callback
					break;
			}
		}
	}
}