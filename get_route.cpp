#include "head.h"


//��ȡ·�������txt
void get_route(String dir , const char * out_path)
{
	freopen(out_path, "w", stdout); //����ض���������ݽ�������out_path�ļ���
	vector<String> filenames;
	glob(dir, filenames);
	for (int i = 0; i < filenames.size(); ++i)
	{
		string s1 = "";
		for (int j = 37; j < filenames[i].size(); ++j)
		{
			if (filenames[i][j] == '\\')s1+= '//';
			else s1 += filenames[i][j];
		}
		cout << s1 << endl;
	}
	fclose(stdout);
}