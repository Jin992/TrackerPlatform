#pragma once
#include <exception>
#include <string>

namespace TrackingPlatform {
	class CustomException : public std::exception {
	public:
		CustomException(std::string msg);
		const char* what() const override;

	private:
		std::string _msg;

	};
}