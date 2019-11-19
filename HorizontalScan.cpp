#include "HorizontalScan.h"

namespace TrackingPlatform {
	HorizontalScan::HorizontalScan(TrackingPlatform& tracker)
		: Scan(tracker)
	{}

	HorizontalScan::HorizontalScan(TrackingPlatform& tracker, Range pan, Range tilt, std::function<bool(float, float)> callback)
		: Scan(tracker, pan, tilt, callback)
	{}

	void HorizontalScan::scan() {
		// Move by y axis
		for (float i = tilt().begin(); i <= tilt().end(); i += tilt().step()) {
			// Elevate by step y position
			tracker().elevate_to(i, tilt().pwm_timeout());
			// Move x axis from begin of range to end 
			for (float j = pan().begin(); j != pan().end(); j += pan().step()) {
				tracker().move_to_athimuth(j, pan().pwm_timeout());
				// if callback return false break the loop
				if (!callback(j, i)) // invoke callback
					break;
			}
			// Elevate by step value y axis
			i += tilt().step();
			tracker().elevate_to(i, tilt().pwm_timeout());
			// Move x axis from end of range to begin
			for (float j = pan().end(); j >= pan().begin(); j -= tilt().step()) {
				tracker().move_to_athimuth(j, pan().pwm_timeout());
				// if callback return false break the loop
				if (!callback(j, i)) // invoke callback
					break;
			}
		}
	}

	void HorizontalScan::rscan() {
		// Move by y axis
		for (float i = tilt().begin(); i <= tilt().end(); i += tilt().step()) {
			// Elevate by step y position
			tracker().elevate_to(i, tilt().pwm_timeout());
			// Move x axis from end of range to begin
			for (float j = pan().end(); j >= pan().begin(); j -= tilt().step()) {
				tracker().move_to_athimuth(j, pan().pwm_timeout());
				// if callback return false break the loop
				if (!callback(j, i)) // invoke callback
					break;
			}
			// Elevate by step value y axis
			i += tilt().step();
			tracker().elevate_to(i, tilt().pwm_timeout());
			// Move x axis from begin of range to end 
			for (float j = pan().begin(); j != pan().end(); j += pan().step()) {
				tracker().move_to_athimuth(j, pan().pwm_timeout());
				// if callback return false break the loop
				if (!callback(j, i)) // invoke callback
					break;
			}
		}
	}
}