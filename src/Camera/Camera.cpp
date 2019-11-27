#include "Camera.h"
#include "CustomException.h"
#include "Utils.h"

namespace TrackingPlatform {
	Camera::Camera(unsigned width, unsigned height, unsigned x_range, unsigned x_step, unsigned y_range, unsigned y_step, std::string name)
		: _width(width), _height(height), _name(name), _cap(0), _rows_cnt(0), _cols_cnt(0)
	{
		if (!_cap.isOpened())
			throw TrackingPlatform::CustomException("CV::Error : Failed to open camera");
		_x_crop = x_step * (_width / 60);
		_y_crop = y_step * (_height / 60);
		unsigned x_border = (width - _x_crop) / 2;
		unsigned y_border = (height - _y_crop) / 2;
		_roi = cv::Rect(x_border, y_border, _x_crop, _y_crop);
		_cap.set(cv::CAP_PROP_FRAME_WIDTH, _width);
		_cap.set(cv::CAP_PROP_FRAME_HEIGHT, _height);
		_rows = y_range / y_step;
		_cols = x_range / x_step;
	}

	Camera::~Camera() {

	}


	void Camera::shot() {
		cv::Mat frame;
		cv::Mat cropped_frame;

		if (_cap.isOpened()) {
			_cap >> frame;
			// Crop ROI
			cropped_frame = frame(_roi).clone();
			if (_cols_cnt < _cols) {
				_mat_cols.push_back(cropped_frame.clone());
				_cols_cnt++;
			}
			else {
				_cols_cnt = 0;
				std::cout << std::endl;
				cv::Mat row;
				cv::hconcat(_mat_cols, row);
				_mat_rows.push_back(row.clone());
				_mat_cols.clear();
				_rows_cnt++;
				if (_rows_cnt == _rows) {
					cv::Mat full;
					cv::vconcat(std::vector<cv::Mat>(_mat_rows.rbegin(), _mat_rows.rend()), full);
					imwrite(_name + "_panoram" + ".jpg", full);
					//exit(1);
				}
			}
		}

	}

	void Camera::start_image() {
		cv::Mat frame;
		if (_cap.isOpened()) {
			_cap >> frame;
			imwrite(_name + "_start" + ".jpg", frame);
			Utils::sleep(500);
		}
	}
}