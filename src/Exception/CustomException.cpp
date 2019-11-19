#include "CustomException.h"

namespace TrackingPlatform {
	CustomException::CustomException(std::string msg)
		: _msg(msg)
	{}

	const char* CustomException::what() const throw () {
		return _msg.c_str();
	}
}