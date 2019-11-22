#pragma once
#include "Scan.h"

namespace TrackingPlatform {
	class HorizontalScan : public Scan {
	public:
		HorizontalScan(TrackingPlatform& tracker);
		HorizontalScan(TrackingPlatform& tracker, Range pan, Range tilt, std::function<bool(float, float)> callback);
		void scan() override;
		void rscan() override;
	};
}