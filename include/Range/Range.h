#pragma once



namespace TrackingPlatform {

	class Range {
	public:
		Range();
		Range(float begin, float end, float step, float pwm_timeout);

		// Set methods
		void set_begin(float begin);
		void set_end(float end);
		void set_step(float step);
		void set_pwm_timeout(float timeout);

		// Get methods
		float begin();
		float end();
		float step();
		float pwm_timeout();

	private:
		float _begin;			// Begin of range
		float _end;				// End of range
		float _step;			// Range iteration step
		float _pwm_timeout;		// Range iteration timeout
	};
}