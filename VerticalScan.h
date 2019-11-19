#pragma once
#include "Scan.h"

namespace TrackingPlatform {
	class VerticalScan : public Scan {
	public:
		VerticalScan(TrackingPlatform& tracker);
		VerticalScan(TrackingPlatform& tracker, Range pan, Range tilt, std::function<bool(float, float)> callback);
		void scan() override;
		void rscan() override;
	};
}