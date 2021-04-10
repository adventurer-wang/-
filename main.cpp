/************************************************************************/
/*
OpenCV图像缩放使用的函数是：resize
void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpolation=INTER_LINEAR )
参数含义：
InputArray src     -原图像
OutputArray dst    -输出图像
Size dsize         -目标图像的大小
double fx=0        -在x轴上的缩放比例
double fy=0        -在y轴上的缩放比例
int interpolation  -插值方式，有以下四种方式
INTER_NN      -最近邻插值
INTER_LINEAR  -双线性插值 (缺省使用)
INTER_AREA    -使用象素关系重采样，当图像缩小时候，该方法可以避免波纹出现。当图像放大时，类似于 INTER_NN 方法。
INTER_CUBIC   -立方插值。
说明：dsize与fx和fy必须不能同时为零
*/
/************************************************************************/


#include "head.h"

const char* out_path = "C:/Users/Administrator/Desktop/train/neg.txt";
String dir = "C:/Users/Administrator/Desktop/train/neg/";

//图像旋转
Mat anglerotate(Mat& src, int angle)
{
	//角度转换
	float alpha = angle * CV_PI / 180;
	//构造旋转矩阵
	float rotateMat[3][3] = {
		{cos(alpha),-sin(alpha),0},
		{sin(alpha),cos(alpha),0},
		{0,0,1}
	};
	int nsrcrows = src.rows;
	int nsrccols = src.cols;
	//计算旋转后图像矩阵的各个顶点位置
	float a1 = nsrccols * rotateMat[0][0];
	float b1 = nsrccols * rotateMat[1][0];
	float a2 = nsrccols * rotateMat[0][0] + nsrcrows * rotateMat[0][1];
	float b2 = nsrccols * rotateMat[1][0] + nsrcrows * rotateMat[1][1];
	float a3 = nsrcrows * rotateMat[0][1];
	float b3 = nsrcrows * rotateMat[1][1];
	//计算极值点
	float kxmin = min(min(min(0.0f, a1), a2), a3);
	float kxmax = max(max(max(0.0f, a1), a2), a3);
	float kymin = min(min(min(0.0f, b1), b2), b3);
	float kymax = max(max(max(0.0f, b1), b2), b3);
	//计算输出矩阵的尺寸
	int nrows = abs(kxmax - kxmin);
	int ncols = abs(kymax - kymin);
	Mat dst(nrows, ncols, src.type(), Scalar::all(0));
	for (int i = 0; i < nrows; ++i)
	{
		for (int j = 0; j < ncols; ++j)
		{
			//旋转坐标变换
			int x = (j + kxmin) * rotateMat[0][0] - (i + kymin) * rotateMat[0][1];
			int y = -(j + kxmin) * rotateMat[1][0] + (i + kymin) * rotateMat[1][1];
			//区域旋转
			if ((x >= 0) && (x < nsrccols) && (y >= 0) && (y < nsrcrows))
			{
				dst.at<Vec3b>(i, j) = src.at<Vec3b>(y, x);
			}
		}
	}
	return dst;
}


//主函数
int main(int argc, char** argv)  
{
	/*
	//图像旋转
	Mat src = imread("3.jpg");
	namedWindow("1", CV_WINDOW_NORMAL);
	imshow("1", src);
	Mat dst;
	double angle = 180;
	dst = Mat::zeros(src.rows, src.cols, src.type());
	//旋转中心 
	Point2f center(src.cols / 2., src.rows / 2.);
	//获取旋转矩阵（2x3矩阵）
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);
	//Scalar borderColor = Scalar(0, 238, 0);
	warpAffine(src, dst, rot_mat, src.size(), INTER_LINEAR, BORDER_REPLICATE);//BORDER_REPLICATE 复制边缘填充
	//imshow("1", src);
	namedWindow("2", CV_WINDOW_NORMAL);
	imshow("2", dst);
	waitKey(0);
	*/
	/*
	Mat src = imread("3.jpg");
	//namedWindow("1", CV_WINDOW_NORMAL);
	imshow("1", src);
	Mat dst;
	dst = Mat::zeros(src.rows, src.cols, src.type());
	double angle = -20;
	double alpha = angle * CV_PI / 180;
	//构建仿射矩阵
	Mat warp_mat= (Mat_<double>(2, 3) << 0.5*cos(alpha), 0.5*(-sin(alpha)),-4 ,0.5*sin(alpha), 0.5*cos(alpha),-4);
	warpAffine(src, dst, warp_mat, src.size());
	namedWindow("仿射变换", CV_WINDOW_NORMAL);
	imshow("仿射变换", dst);
	waitKey(0);
	*/

/*
//仿射变换
	Mat src = imread("3.jpg");
	Point2f srcTri[3];
	Point2f dstTri[3];
	Mat dst;
	dst = Mat::zeros(src.rows, src.cols, src.type());
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols, 0);
	srcTri[2] = Point2f(0, src.rows);
	dstTri[0] = Point2f(src.cols * 0.0, src.rows * 0.33);
	dstTri[1] = Point2f(src.cols * 0.85, src.rows * 0.25);
	dstTri[2] = Point2f(src.cols * 0.15, src.rows * 0.7);
	Mat warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(src, dst, warp_mat, dst.size());
	namedWindow("仿射变换", CV_WINDOW_NORMAL);
	imshow("仿射变换", dst);
	waitKey(0);
*/
	
/*
	//图像旋转
	Mat src = imread("3.jpg");
	namedWindow("1", CV_WINDOW_NORMAL);
	imshow("1",src);
	Mat dst;
	double angle = 180;
	dst = Mat::zeros(src.rows, src.cols, src.type());
	//旋转中心 
	Point2f center(src.cols / 2., src.rows / 2.);
	//获取旋转矩阵（2x3矩阵）
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);
	//Scalar borderColor = Scalar(0, 238, 0);
	warpAffine(src, dst, rot_mat, src.size(), INTER_LINEAR, BORDER_REPLICATE);//BORDER_REPLICATE 复制边缘填充
	//imshow("1", src);
	namedWindow("2", CV_WINDOW_NORMAL);
	imshow("2", dst);
	waitKey(0);
*/
	//imwrite("旋转后3(222).jpg", dst);
/*
//图像旋转
	Mat image = imread("3.jpg");
	imshow("原图", image);
	int angle = 45;
	Mat resultImage = anglerotate(image, angle);
	imshow("旋转", resultImage);
	imwrite("旋转后3.jpg", resultImage);
	waitKey(0);
*/
/*********************************************************************************************************/
/*
//坐标变换
	Mat image = imread("3.jpg");
	Mat resultImage(image.size(), image.type());
	Mat xMapImage(image.size(), CV_32FC1);
	Mat yMapImage(image.size(), CV_32FC1);
	int rows = image.rows;
	int cols = image.cols;
	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < cols; i++)
		{
			xMapImage.at<float>(j, i) = cols - i;
			yMapImage.at<float>(j, i) = rows - j;
		}
	}
	remap(image, resultImage, xMapImage, yMapImage, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	imwrite("101.jpg", resultImage);
	//imshow("原图", image);
	//imshow("坐标旋转", resultImage);
	waitKey(0);
	return 0;
*/
/**********************************************************************************************************/
	/*
	freopen("C:/Users/Administrator/Desktop/train/neg.txt", "r", stdin); //输入重定向，输入数据将从in.txt文件中读取
	freopen("C:/Users/Administrator/Desktop/train/neg2.txt", "w", stdout); //输出重定向，输出数据将保存在out.txt文件中
	string str;
	for (int i = 0; i < 40000; ++i)
	{
		cin >> str;
		for (int j = 0; j < str.size(); ++j)
		{
			if(str[j]=='\\')

		}
	}
	fclose(stdin);//关闭文件
	fclose(stdout);//关闭文件*/
	//String s1 = "C:/Users/Administrator/Desktop/train/neg/";
	//String s2 = "C:/Users/Administrator/Desktop/train/";
	//bat(s1, s2);
	//String s1 = "C:/Users/Administrator/Desktop/毕业设计/训练样本/8#中六线20.06.03-151销钉缺失.JPG";
	//String s2 = "C:/Users/Administrator/Desktop/毕业设计/训练样本/8#中六线20.06.03-151销钉缺失（灰度化）.JPG";
	//rgb_to_gray(s1, s2, 0);
/*************************************************************************/

//识别
	CascadeClassifier classifier("C:/Users/Administrator/Desktop/train/xml/cascade.xml");
	Mat img = imread("8#中六线20.06.03-151销钉缺失（灰度化）.JPG");
	Mat img_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	equalizeHist(img_gray, img_gray);
	vector<Rect> plates;
	classifier.detectMultiScale(img_gray, plates);
	for (int i = 0; i < plates.size(); ++i)
	{
		rectangle(img, plates[i], Scalar(0, 0, 255), 3);
	}
	imshow("plates", img);
	waitKey(0);

/**************************************************************************/
/************************************************************************/
/*
// 训练样本预处理
	String in_path1 = "C:/Users/Administrator/Desktop/毕业设计/训练样本/正样本/";
	String out_path1 = "C:/Users/Administrator/Desktop/毕业设计/训练样本/正样本灰度化/";
	String in_path2 = "C:/Users/Administrator/Desktop/毕业设计/训练样本/负样本/";
	String out_path2 = "C:/Users/Administrator/Desktop/毕业设计/训练样本/负样本灰度化/";
	bat_togray(in_path1, out_path1,1);
	bat_togray(in_path2, out_path2, 0);
*/
/**********************************************************************/


/************************************************************************/
/*
// 测试样本预处理
	String in_path1 = "C:/Users/Administrator/Desktop/毕业设计/测试样本/";
	String out_path1 = "C:/Users/Administrator/Desktop/毕业设计/测试样本/灰度化/";
	bat_togray(in_path1, out_path1,0);
*/
/**********************************************************************/

/***********************************************************************/
/*
//计算积分图
	Mat Image = imread("29.jpg", 0);
	namedWindow("原图",CV_WINDOW_NORMAL);
	imshow("原图", Image);
	Mat sum = Mat::zeros(Image.rows + 1, Image.cols + 1, CV_32FC1);
	Mat sqsum = Mat::zeros(Image.rows + 1, Image.cols + 1, CV_64FC1);
	integral(Image, sum, sqsum, CV_32FC1, CV_64FC1);
	//归一化方便显示
	Mat result;
	normalize(sum, result, 0, 255, NORM_MINMAX, CV_8UC1);
	namedWindow("积分图", CV_WINDOW_NORMAL);
	imshow("积分图", result);
	waitKey(0);

*/
/***********************************************************************/
	return 0;
}


