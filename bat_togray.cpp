#pragma warning
#include "head.h"

// RGB批量转灰度
void bat_togray(String in_path, String out_path , bool lag)
{
	vector<String> filenames;
	glob(in_path, filenames);
	int rank[100];
	for (int i = 0; i < 100; ++i)rank[i] = i + 1;
	for (int i = 0; i < filenames.size(); ++i)
	{
		char rank1[100];
		sprintf(rank1, "%d", rank[i]);
		string out_string="";
		for (int i = 0; i < strlen(rank1); ++i)out_string += rank1[i];
		//cout << filenames[i] << endl;
		rgb_to_gray(filenames[i] , out_path+out_string+".jpg", lag);
	}
};

void bat(String in_path, String out_path)
{
	freopen("C:/Users/Administrator/Desktop/train/neg.txt", "w", stdout); //输出重定向，输出数据将保存在out.txt文件中
	vector<String> filenames;
	glob(in_path, filenames);
	for (int i = 0; i < filenames.size(); ++i)
	{
		cout << filenames[i] << endl;
	}
	fclose(stdout);//关闭文件
};