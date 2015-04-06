#ifndef DNN_H
#define DNN_H


#include <iostream>
#include <sstream>
#include <assert.h>

#include <ctime>   //产生时间种子
#include <cstdlib> //产生随机数
#include <cmath>
#include <limits>
#include <fstream>
#include <iomanip>

using namespace std;

class DNN
{
	public:
		DNN();

		void test(string testFile,string result);
		void test(string testFile,string model,string result);
		void train(string trainFile ,string validateFile,string model,int times,double tol);
		double validate(string validateFile);

		void setWP();
		void initError();
		void initParameter();
		void backpropagate();

	    void saveModel(string fin);
	    void saveMaxtrixA(string fin);
	    void saveMaxtrixB(string fin);
	    void saveMaxtrixC(string fin);

	    void loadModel(string ofile);
	    void loadMaxtrixA(string ofile);
	    void loadMaxtrixB(string ofile);
	    void loadMaxtrixC(string ofile);

		double normal(double E, double V);
		double propagate();
		double activate_tanh(double val);
		double activate_tanh_output(double val);


	private:
		const static int vectorL = 50;  //the length of the vector 
		const static int windowsL = 3; //the size of the window
		const static int wordL = 8;    //the word 's num in the input
		const static int outputL = 9;  //the length of the output
		const static int convolutionL = 50; //the convolution's length
		const static int SFL = 100;      //sentence feature's length
		const static int LFL = 2;	  //lecial feature's lenght
		const static int miniBatch = 10;  //set the minibatch per time 

		const static double maxEXP = 16;
		const static double lambda = 0;
		const static int miniTrainTime = 4;
		const static int LRNUM = 4;
		

		double alpha;


		const static int vbeL = vectorL;
		double vbe[vbeL];   //default vector of the begin and the end of the wrod !

		/*************/
		const static int inputL = wordL*vectorL;
		double input[inputL];


		const static int WPH = windowsL*vectorL,WPW = wordL - windowsL +3;
		double WP[WPH][WPW];


		const static int ConH = convolutionL, ConW = WPW;
		double Con[ConH][ConW];


		const static int maxConL = convolutionL;
		int maxConI[maxConL];
		double maxCon[maxConL+1];
		double maxConE[maxConL+1];


		const static int featureL = SFL+LFL;
		double feature[featureL+1];
		double featureE[featureL+1];

		int expectIndex;
		int predictIndex;
		double output[outputL];
		double outputE[outputL];

		/*********************/

		const static int AH = convolutionL,AW = windowsL*vectorL;
		double A[AH][AW];
		double AE[AH][AW];

		const static int BH = SFL,BW = convolutionL+1;
		double B[BH][BW];
		double BE[BH][BW];

		const static int CH = outputL,CW = featureL+1;
		double C[CH][CW];
		double CE[CH][CW];


};


#endif
