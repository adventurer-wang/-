#include "head.h"

// 加权平均法RGB转灰度
void rgb_to_gray(String filename,String out_path , bool lag)
{
	Mat src,out_gray;
	src = imread(filename);
	//imshow("原图", src);
	Mat gray = Mat(src.rows, src.cols, CV_8UC1);
	float R, G, B;
	for (int y = 0; y < src.rows; y++)
	{
		uchar* data = gray.ptr<uchar>(y);
		for (int x = 0; x < src.cols; x++)
		{
			B = src.at<Vec3b>(y, x)[0];
			G = src.at<Vec3b>(y, x)[0];
			R = src.at<Vec3b>(y, x)[0];
			data[x] = (int)(R * 0.3 + 0.59 * G + 0.11 * B);
		}
	}
	//imshow("加权平均法灰度图", gray);
	if(lag)resize(gray, gray, Size(24, 24));
	imwrite(out_path, gray);
}