#pragma once

#include <opencv2\objdetect.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace detect {

	const cv::String faceCascadeName = "haarcascade_frontalface_alt.xml";
	const cv::String eyeCascadeName = "haarcascade_eye.xml";
	const cv::String bodyCascadeName = "haarcascade_upperbody.xml";

	class detector {
	private:
		cv::Mat frame;
		cv::CascadeClassifier faceCascade, eyeCascade, bodyCascade;
		cv::String windowName;

	public:
		bool loadAll();							//loads all the cascades into cascade classifiers
		void setFrame(cv::Mat);
		void setWindowName(cv::String);
		std::vector<cv::Point> getFaceTgt();
		std::vector<cv::Point> getBodyTgt();
		void display();
	};
}
