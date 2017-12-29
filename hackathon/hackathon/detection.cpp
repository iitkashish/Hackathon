#include "stdafx.h"
#include "detection.h"

bool detect::detector::loadAll() {
	bool loadOk = true;
	if (!faceCascade.load(faceCascadeName))
		loadOk = false;
	if (!eyeCascade.load(eyeCascadeName))
		loadOk = false;
	if (!bodyCascade.load(bodyCascadeName))
		loadOk = false;
	return loadOk;
}

void detect::detector::setFrame(cv::Mat frameName) {
	frame = frameName;
}

void detect::detector::setWindowName(cv::String name) {
	windowName = name;
}

std::vector<cv::Point> detect::detector::getFaceTgt() {
	std::vector<cv::Rect> faces;
	std::vector<cv::Point> target;
	cv::Mat frame_gray;

	cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
	cv::equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	faceCascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(60, 60));

	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		cv::ellipse(frame, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);

		cv::Mat faceROI = frame_gray(faces[i]);
		std::vector<cv::Rect> eyes;
		target.push_back(center);

		//-- In each face, detect eyes
		eyeCascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			cv::Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			cv::circle(frame, eye_center, radius, cv::Scalar(255, 0, 0), 4, 8, 0);
		}
	}

	//now frame holds its final value, ie. with the identification ellipses
	return target;
}


void detect::detector::display() {
	//call only after getFaceTgt and getBodyTgt have been called

	cv::imshow(windowName, frame);
}