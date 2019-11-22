
#include <iostream>
#include "TrackingPlatform.h"
#include "HorizontalScan.h"
#include "VerticalScan.h"
#include "DiagonalScan.h"


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
	TrackingPlatform::Range pan(-90.0, 90.0, 5.0, 15.0); // range start, range end, iteration step, step timeout
	TrackingPlatform::Range tilt(0.0, 45.0, 5.0, 50); // range start, range end, iteration step, step timeout
	auto pp = pan.get_range();
	auto tt = tilt.get_range();

	std::cout << pp.first << " " << pp.second << std::endl;
	std::cout << tt.first << " " << tt.second << std::endl;
	// Create scan object 
	TrackingPlatform::HorizontalScan hScan(tracker, pan, tilt, [](float athimuth, float elevation)->bool { std::cout << "Athimuth : " << athimuth << " Elevation : " << elevation << std::endl; Utils::sleep(2000); return true; });
	TrackingPlatform::VerticalScan vScan(tracker, pan, tilt, [](float athimuth, float elevation)->bool { std::cout << "Athimuth : " << athimuth << " Elevation : " << elevation << std::endl;  return true; });
	TrackingPlatform::DiagonalScan dScan(tracker, pan, tilt, [](float athimuth, float elevation)->bool { std::cout << "Athimuth : " << athimuth << " Elevation : " << elevation << std::endl;  return true; });
	// Start scan
	tracker.elevate_to(1, 70);
	//tracker.elevate_to(4000, 70);
	//Sleep(20000);
	dScan.scan();
	//hScan.scan();
	//vScan.scan();
	//vScan.rscan();
	/*tracker.move_to_athimuth(-90, 10);
	
	tracker.to_postion(-90, 0);
	Sleep(2000);
	tracker.to_postion(90, 5);
	Sleep(2000);
	tracker.to_postion(-90, 10);
	Sleep(2000); 
	tracker.to_postion(90, 15);
	Sleep(2000); 
	tracker.to_postion(-90, 20);
	Sleep(2000); 
	tracker.to_postion(90, 25);
	Sleep(2000); 
	tracker.to_postion(-90, 30);
	Sleep(2000); 
	tracker.to_postion(90, 40);
	Sleep(2000);*/






	//tracker.move_to_athimuth(90,10);
	//tracker.elevate_to(5, 10);
	//tracker.move_to_athimuth(-90, 10);
	//tracker.move_to_athimuth(90, 10);
	//tracker.elevate_to(10, 10);
	//tracker.move_to_athimuth(-90, 10);
	//tracker.move_to_athimuth(90, 10);
	//tracker.elevate_to(15, 10);
	//tracker.move_to_athimuth(-90, 10);
	//tracker.move_to_athimuth(90, 10);
	//tracker.elevate_to(20, 10);
	//tracker.move_to_athimuth(-90, 10);

	return 0;
}

