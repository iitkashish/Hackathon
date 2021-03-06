// hackathon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "detection.h"

using namespace std;
using namespace cv;

int main()
{
	detect::detector D1;
	vector<Point> faceVector;
	VideoCapture capture;
	Mat frame;

	if (D1.loadAll()) {
		D1.setWindowName("shooter");
		capture.open(0);

		if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }
		while (capture.read(frame))
		{
			D1.setFrame(frame);
			faceVector = D1.getFaceTgt();				//copies value or address???
			D1.display();
			if (cv::waitKey(10) == 27) { break; } // escape
		}
	}
    return 0;
}

