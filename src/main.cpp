#include <iostream>
#include "DNN.h"

int main()
{
	DNN dnn;

	string trainFile = "/home/xqjin/Graduate/Corpus/Prep/vectorFeature/train.uvec";
	string testFile = "/home/xqjin/Graduate/Corpus/Prep/vectorFeature/test.uvec";
	string validateFile = "/home/xqjin/Graduate/Corpus/Prep/vectorFeature/validate.uvec";
	string model = "/home/xqjin/Graduate/Output/Prep/DNN/model/DNN-";
	string result = "/home/xqjin/Graduate/Output/Prep/DNN/Result/DNN.result";
	int times = 100;
	double tol = 0.01;

	dnn.train(trainFile,validateFile,model,times,tol);
	dnn.test(testFile,model,result);
}

