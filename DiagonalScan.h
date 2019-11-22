#pragma once
#include "Scan.h"

namespace TrackingPlatform {
	class DiagonalScan : public Scan
	{
	public:
		DiagonalScan(TrackingPlatform& tracker);
		DiagonalScan(TrackingPlatform& tracker, Range pan, Range tilt, std::function<bool(float, float)> callback);
		void scan() override;
		void rscan() override;
	};

}