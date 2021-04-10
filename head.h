#pragma once
#include <iostream>
#include <io.h>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace cv;
using namespace std;

// 加权平均法RGB转灰度
void rgb_to_gray(String filename, String out_path , bool lag);
// RGB批量转灰度
void bat_togray(String in_path, String out_path , bool lag);

void bat(String in_path, String out_path);

void get_route(String dir, const char* out_path);
