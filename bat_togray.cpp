#pragma warning
#include "head.h"

// RGB����ת�Ҷ�
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
	freopen("C:/Users/Administrator/Desktop/train/neg.txt", "w", stdout); //����ض���������ݽ�������out.txt�ļ���
	vector<String> filenames;
	glob(in_path, filenames);
	for (int i = 0; i < filenames.size(); ++i)
	{
		cout << filenames[i] << endl;
	}
	fclose(stdout);//�ر��ļ�
};