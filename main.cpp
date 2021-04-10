/************************************************************************/
/*
OpenCVͼ������ʹ�õĺ����ǣ�resize
void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpolation=INTER_LINEAR )
�������壺
InputArray src     -ԭͼ��
OutputArray dst    -���ͼ��
Size dsize         -Ŀ��ͼ��Ĵ�С
double fx=0        -��x���ϵ����ű���
double fy=0        -��y���ϵ����ű���
int interpolation  -��ֵ��ʽ�����������ַ�ʽ
INTER_NN      -����ڲ�ֵ
INTER_LINEAR  -˫���Բ�ֵ (ȱʡʹ��)
INTER_AREA    -ʹ�����ع�ϵ�ز�������ͼ����Сʱ�򣬸÷������Ա��Ⲩ�Ƴ��֡���ͼ��Ŵ�ʱ�������� INTER_NN ������
INTER_CUBIC   -������ֵ��
˵����dsize��fx��fy���벻��ͬʱΪ��
*/
/************************************************************************/


#include "head.h"

const char* out_path = "C:/Users/Administrator/Desktop/train/neg.txt";
String dir = "C:/Users/Administrator/Desktop/train/neg/";

//ͼ����ת
Mat anglerotate(Mat& src, int angle)
{
	//�Ƕ�ת��
	float alpha = angle * CV_PI / 180;
	//������ת����
	float rotateMat[3][3] = {
		{cos(alpha),-sin(alpha),0},
		{sin(alpha),cos(alpha),0},
		{0,0,1}
	};
	int nsrcrows = src.rows;
	int nsrccols = src.cols;
	//������ת��ͼ�����ĸ�������λ��
	float a1 = nsrccols * rotateMat[0][0];
	float b1 = nsrccols * rotateMat[1][0];
	float a2 = nsrccols * rotateMat[0][0] + nsrcrows * rotateMat[0][1];
	float b2 = nsrccols * rotateMat[1][0] + nsrcrows * rotateMat[1][1];
	float a3 = nsrcrows * rotateMat[0][1];
	float b3 = nsrcrows * rotateMat[1][1];
	//���㼫ֵ��
	float kxmin = min(min(min(0.0f, a1), a2), a3);
	float kxmax = max(max(max(0.0f, a1), a2), a3);
	float kymin = min(min(min(0.0f, b1), b2), b3);
	float kymax = max(max(max(0.0f, b1), b2), b3);
	//�����������ĳߴ�
	int nrows = abs(kxmax - kxmin);
	int ncols = abs(kymax - kymin);
	Mat dst(nrows, ncols, src.type(), Scalar::all(0));
	for (int i = 0; i < nrows; ++i)
	{
		for (int j = 0; j < ncols; ++j)
		{
			//��ת����任
			int x = (j + kxmin) * rotateMat[0][0] - (i + kymin) * rotateMat[0][1];
			int y = -(j + kxmin) * rotateMat[1][0] + (i + kymin) * rotateMat[1][1];
			//������ת
			if ((x >= 0) && (x < nsrccols) && (y >= 0) && (y < nsrcrows))
			{
				dst.at<Vec3b>(i, j) = src.at<Vec3b>(y, x);
			}
		}
	}
	return dst;
}


//������
int main(int argc, char** argv)  
{
	/*
	//ͼ����ת
	Mat src = imread("3.jpg");
	namedWindow("1", CV_WINDOW_NORMAL);
	imshow("1", src);
	Mat dst;
	double angle = 180;
	dst = Mat::zeros(src.rows, src.cols, src.type());
	//��ת���� 
	Point2f center(src.cols / 2., src.rows / 2.);
	//��ȡ��ת����2x3����
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);
	//Scalar borderColor = Scalar(0, 238, 0);
	warpAffine(src, dst, rot_mat, src.size(), INTER_LINEAR, BORDER_REPLICATE);//BORDER_REPLICATE ���Ʊ�Ե���
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
	//�����������
	Mat warp_mat= (Mat_<double>(2, 3) << 0.5*cos(alpha), 0.5*(-sin(alpha)),-4 ,0.5*sin(alpha), 0.5*cos(alpha),-4);
	warpAffine(src, dst, warp_mat, src.size());
	namedWindow("����任", CV_WINDOW_NORMAL);
	imshow("����任", dst);
	waitKey(0);
	*/

/*
//����任
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
	namedWindow("����任", CV_WINDOW_NORMAL);
	imshow("����任", dst);
	waitKey(0);
*/
	
/*
	//ͼ����ת
	Mat src = imread("3.jpg");
	namedWindow("1", CV_WINDOW_NORMAL);
	imshow("1",src);
	Mat dst;
	double angle = 180;
	dst = Mat::zeros(src.rows, src.cols, src.type());
	//��ת���� 
	Point2f center(src.cols / 2., src.rows / 2.);
	//��ȡ��ת����2x3����
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);
	//Scalar borderColor = Scalar(0, 238, 0);
	warpAffine(src, dst, rot_mat, src.size(), INTER_LINEAR, BORDER_REPLICATE);//BORDER_REPLICATE ���Ʊ�Ե���
	//imshow("1", src);
	namedWindow("2", CV_WINDOW_NORMAL);
	imshow("2", dst);
	waitKey(0);
*/
	//imwrite("��ת��3(222).jpg", dst);
/*
//ͼ����ת
	Mat image = imread("3.jpg");
	imshow("ԭͼ", image);
	int angle = 45;
	Mat resultImage = anglerotate(image, angle);
	imshow("��ת", resultImage);
	imwrite("��ת��3.jpg", resultImage);
	waitKey(0);
*/
/*********************************************************************************************************/
/*
//����任
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
	//imshow("ԭͼ", image);
	//imshow("������ת", resultImage);
	waitKey(0);
	return 0;
*/
/**********************************************************************************************************/
	/*
	freopen("C:/Users/Administrator/Desktop/train/neg.txt", "r", stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
	freopen("C:/Users/Administrator/Desktop/train/neg2.txt", "w", stdout); //����ض���������ݽ�������out.txt�ļ���
	string str;
	for (int i = 0; i < 40000; ++i)
	{
		cin >> str;
		for (int j = 0; j < str.size(); ++j)
		{
			if(str[j]=='\\')

		}
	}
	fclose(stdin);//�ر��ļ�
	fclose(stdout);//�ر��ļ�*/
	//String s1 = "C:/Users/Administrator/Desktop/train/neg/";
	//String s2 = "C:/Users/Administrator/Desktop/train/";
	//bat(s1, s2);
	//String s1 = "C:/Users/Administrator/Desktop/��ҵ���/ѵ������/8#������20.06.03-151����ȱʧ.JPG";
	//String s2 = "C:/Users/Administrator/Desktop/��ҵ���/ѵ������/8#������20.06.03-151����ȱʧ���ҶȻ���.JPG";
	//rgb_to_gray(s1, s2, 0);
/*************************************************************************/

//ʶ��
	CascadeClassifier classifier("C:/Users/Administrator/Desktop/train/xml/cascade.xml");
	Mat img = imread("8#������20.06.03-151����ȱʧ���ҶȻ���.JPG");
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
// ѵ������Ԥ����
	String in_path1 = "C:/Users/Administrator/Desktop/��ҵ���/ѵ������/������/";
	String out_path1 = "C:/Users/Administrator/Desktop/��ҵ���/ѵ������/�������ҶȻ�/";
	String in_path2 = "C:/Users/Administrator/Desktop/��ҵ���/ѵ������/������/";
	String out_path2 = "C:/Users/Administrator/Desktop/��ҵ���/ѵ������/�������ҶȻ�/";
	bat_togray(in_path1, out_path1,1);
	bat_togray(in_path2, out_path2, 0);
*/
/**********************************************************************/


/************************************************************************/
/*
// ��������Ԥ����
	String in_path1 = "C:/Users/Administrator/Desktop/��ҵ���/��������/";
	String out_path1 = "C:/Users/Administrator/Desktop/��ҵ���/��������/�ҶȻ�/";
	bat_togray(in_path1, out_path1,0);
*/
/**********************************************************************/

/***********************************************************************/
/*
//�������ͼ
	Mat Image = imread("29.jpg", 0);
	namedWindow("ԭͼ",CV_WINDOW_NORMAL);
	imshow("ԭͼ", Image);
	Mat sum = Mat::zeros(Image.rows + 1, Image.cols + 1, CV_32FC1);
	Mat sqsum = Mat::zeros(Image.rows + 1, Image.cols + 1, CV_64FC1);
	integral(Image, sum, sqsum, CV_32FC1, CV_64FC1);
	//��һ��������ʾ
	Mat result;
	normalize(sum, result, 0, 255, NORM_MINMAX, CV_8UC1);
	namedWindow("����ͼ", CV_WINDOW_NORMAL);
	imshow("����ͼ", result);
	waitKey(0);

*/
/***********************************************************************/
	return 0;
}


