
#include <iostream>
#include "TrackingPlatform.h"
#include "HorizontalScan.h"
#include "VerticalScan.h"


int main(int /*argc*/, char** /*argv*/) {
	// Creating tracker object
	TrackingPlatform::TrackingPlatform tracker;
	// Trye to open
	if (!tracker.open("COM7", 57692)) // Serial name, baud rate
		return -1;
	// Move to athimuth
	//tracker.move_to_athimuth(0, 10.0);
	//tracker.move_to_athimuth(0.0, 15.0);
	//tracker.move_to_athimuth(180.0, 15.0);
	//tracker.move_to_athimuth(-180.0, 15.0);
	//tracker.move_to_athimuth(0.0, 15.0);
	//
	//
	//// Elevate angle
	//tracker.elevate_to(90, 15.0);
	//tracker.elevate_to(0.0, 15.0);
	//for (int i = 0; i < 90; i++) {
	//	tracker.elevate_to(i, 10);
	//}

	// Define pan, tilt rages
	TrackingPlatform::Range pan(-15.0, 15.0, 2.0, 15.0); // range start, range end, iteration step, step timeout
	TrackingPlatform::Range tilt(0.0, 45.0, 2.0, 10); // range start, range end, iteration step, step timeout

	// Create scan object 
	TrackingPlatform::HorizontalScan hScan(tracker, pan, tilt, [](float athimuth, float elevation)->bool { std::cout << "Athimuth : " << athimuth << " Elevation : " << elevation << std::endl; Utils::sleep(2000); return true; });
	TrackingPlatform::VerticalScan vScan(tracker, pan, tilt, [](float athimuth, float elevation)->bool { std::cout << "Athimuth : " << athimuth << " Elevation : " << elevation << std::endl;  return true; });
	// Start scan
	hScan.scan();
	hScan.rscan();
	vScan.scan();
	vScan.rscan();

	return 0;
}

