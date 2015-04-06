#include "DNN.h"

void DNN::test(string testFile,string model,string result)
{
	ifstream fin(testFile.c_str());
	ofstream fout(result.c_str());

	//load the model to test;
	loadModel(model);

	while(true)
	{
		int nid=0,pid=0,sid=0,posi=0,ti=0,stag=0,atag=0;
    	fin >> nid >> pid >> sid >> posi >> ti >> stag >> atag;

    	if(fin.eof())
    	{
    		return;
    	}

    	for(int i=0;i<inputL;i++)
    	{
    		fin >> input[i];
    		assert(fin);
    	}
    	predictIndex = -1;
    	propagate();
		// 如果预测的标签的概率值过小，那么保持原来的标签
		if(predictIndex!=-1)
			fout<<nid<<"\t"<<pid<<"\t"<<sid<<"\t"<<posi<<"\t"<<ti<<"\t"<<stag<<"\t"<<predictIndex<<endl;
		else
			fout<<nid<<"\t"<<pid<<"\t"<<sid<<"\t"<<posi<<"\t"<<ti<<"\t"<<stag<<"\t"<<stag<<endl;
	}
	fin.close();
	fout.close();
}

void DNN::test(string testFile,string result)
{
	ifstream fin(testFile.c_str());
	ofstream fout(result.c_str());

	while(true)
	{
		int nid=0,pid=0,sid=0,posi=0,ti=0,stag=0,atag=0;
    	fin >> nid >> pid >> sid >> posi >> ti >> stag >> atag;

    	if(fin.eof())
    	{
    		return;
    	}

    	for(int i=0;i<inputL;i++)
    	{
    		fin >> input[i];
    	}
    	predictIndex = -1;
    	propagate();
		// 如果预测的标签的概率值过小，那么保持原来的标签
		if(predictIndex!=-1)
			fout<<nid<<"\t"<<pid<<"\t"<<sid<<"\t"<<posi<<"\t"<<ti<<"\t"<<stag<<"\t"<<predictIndex<<endl;
		else
			fout<<nid<<"\t"<<pid<<"\t"<<sid<<"\t"<<posi<<"\t"<<ti<<"\t"<<stag<<"\t"<<stag<<endl;
	}
	fin.close();
	fout.close();
}
