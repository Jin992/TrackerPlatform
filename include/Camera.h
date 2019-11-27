#include <opencv2/opencv.hpp>

namespace TrackingPlatform {

	class Camera {
	public:
		Camera(unsigned width, unsigned height, unsigned x_range, unsigned x_step, unsigned y_range, unsigned y_step, std::string name);
		~Camera();
		void shot();
		void start_image();

	private:
		unsigned				_width;
		unsigned				_height;
		unsigned				_x_crop;
		unsigned				_y_crop;
		std::string				_name;
		cv::VideoCapture		_cap;

		unsigned				_pixels_per_degree;
		cv::Mat					_panoram;
		cv::Rect				_roi;
		std::vector<cv::Mat>	_mat_cols;
		std::vector<cv::Mat>	_mat_rows;
		unsigned				_rows;
		unsigned				_cols;
		unsigned				_rows_cnt;
		unsigned				_cols_cnt;
	};
}