#include "head.h"


//提取路径输出到txt
void get_route(String dir , const char * out_path)
{
	freopen(out_path, "w", stdout); //输出重定向，输出数据将保存在out_path文件中
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