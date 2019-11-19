#pragma once
#include "TrackingPlatform.h"
#include <functional>


namespace TrackingPlatform {

	class Scan {
	public:
		Scan(TrackingPlatform& tracker);
		Scan(TrackingPlatform& tracker, Range pan, Range tilt, std::function<bool(float, float)> callback);
		virtual ~Scan() = default;

		// Pure virtual methods 
		virtual void		  scan() = 0;
		virtual void		  rscan() = 0;

		// Set methods
		void				  set_callback(std::function<bool(float, float)> func);
		void				  set_tilt(Range tilt);
		void				  set_pan(Range pan);

		// Get methods
		TrackingPlatform& tracker();
		Range& pan();
		Range& tilt();

		// Callback invocation
		bool callback(float athim, float elev);

	private:
		TrackingPlatform& _tracker;  // Reference to Tracker object
		Range								_pan;	   // Pan range config object
		Range								_tilt;     // Tilt range config object
		std::function<bool(float, float)>	_callback; // Callback function
	};
}