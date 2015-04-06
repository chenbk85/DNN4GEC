#include "DNN.h"


void DNN::backpropagate()
{

	for(int i=0;i<AH;i++)
		for(int j=0;j<AW;j++)
		{
			A[i][j] -= this->alpha*AE[i][j]/this->miniBatch;
		}

	for(int i=0;i<BH;i++)
		for(int j=0;j<BW;j++)
		{

			B[i][j] -= this->alpha*BE[i][j]/this->miniBatch;
		}

	for(int i=0;i<CH;i++)
		for(int j=0;j<CW;j++)
		{

			C[i][j] -= this->alpha*CE[i][j]/this->miniBatch;
		}
}

double DNN::propagate()
{
	initError();
	setWP();//set the input array WP;

	for(int i=0;i<ConH;i++)
	{
		double maxval = -std::numeric_limits<double>::max();
        int index = -1;
		for(int j=0;j<ConW;j++)
		{
			Con[i][j] = 0.0;
			for(int k=0;k<AW;k++)
			{
				Con[i][j] += A[i][k]*WP[k][j];
			}

            if(maxval<Con[i][j])
            {
                maxval = Con[i][j];
                index = j;
            }
		}
        maxCon[i] = maxval;  //jxq
        maxCon[i] = this->activate_tanh(maxval);
        assert(i<maxConL && i>=0);
        maxConI[i] = index;   //第i行，最大值所在的列的索引是第j列；
	}
	maxCon[maxConL] = 1.0;

	for(int i=0;i<LFL;i++)
		feature[i] = 0.0;

	for(int i=0;i<BH;i++)
	{
		feature[i+LFL] = 0;
		for(int j=0;j<BW;j++)
		{
			feature[i+LFL] += B[i][j]*maxCon[j]; 
		}
		feature[i+LFL] = activate_tanh(feature[i+LFL]);
	}

	feature[featureL] = 1.0;

	double temp1 = -8.0;

	for(int i=0;i<CH;i++)
	{

		output[i] = 0.0;
		for(int j=0;j<CW;j++)
		{
			output[i] += C[i][j]*feature[j];
		}
		output[i] = activate_tanh_output(output[i]);
		if(temp1<output[i])  //get the max abs of the output!
		{
			temp1 = output[i];
			predictIndex = i;
		}
	}

	if(temp1<=0)	predictIndex = -1;

	//calculate the output error!
	double L = 0;

	for(int i=0;i<outputL;i++)
	{
		int index = (i==expectIndex)?1:-1;
		outputE[i] = 2*(output[i]-index)*1.7159*(2.0/3.0)*(1-pow(output[i]/1.7159,2));
		L+=pow((output[i]-index),2);
	}

	//cout<<"output:"<<setprecision(10)<<g<<endl;

	//calculate the feature error!
    for(int i=0;i<featureL;i++)
    {
        featureE[i] = 0;
        for(int j=0;j<outputL;j++)
        {
            featureE[i] += outputE[j]*C[j][i];
        }
        featureE[i] = featureE[i]*(1-pow(feature[i],2));
    }

    //calculate the maxCon error;
    for(int i=0;i<maxConL;i++)
    {
        maxConE[i] = 0;
        for(int j=LFL;j<featureL;j++)
        {
            maxConE[i] += featureE[j]*B[j-LFL][i];
            assert(j-LFL<BH && j-LFL>=0);
        }
        maxConE[i] = maxConE[i]*(1-pow(maxCon[i],2));  //jxq
        //没有使用激活函数,因此这一步可以忽略
    }

    for(int i=0;i<AH;i++)
    {
        for(int j=0;j<AW;j++)
        {
            AE[i][j] += (maxConE[i]*WP[j][maxConI[i]] + this->lambda*A[i][j] );
        }
    }
    

    for(int i=0;i<BH;i++)
    {
        for(int j=0;j<BW;j++)
        {
            BE[i][j] += (featureE[LFL+i]*maxCon[j] + this->lambda*B[i][j]);
        }
    }


    for(int i=0;i<CH;i++)
    {
        for(int j=0;j<CW;j++)
        {
            CE[i][j] += (outputE[i]*feature[j] + this->lambda*C[i][j]);
        }
    }

    //return the error L;
    return L;
}
