#include "DNN.h"


DNN::DNN()
{	
	initParameter();
    this->alpha = 0.01;
}


void DNN::initParameter()
{

	for(int i=0;i<this->vbeL;i++)
		vbe[i] = 0;

    //srand(unsigned(time(0)));
    for(int i=0;i<AH;i++)
    {
        for(int j=0;j<AW;j++)
        {
            //0.02  <  0.03  > 0.04
            A[i][j] = normal(0,0.06);
        }
    }

    for(int i=0;i<BH;i++)
    {
        for(int j=0;j<BW;j++)
        {
            B[i][j] = normal(0,0.06);
        }
    }

    for(int i=0;i<CH;i++)
    {
        for(int j=0;j<CW;j++)
        {
            C[i][j] = normal(0,0.06);
        }
    }
}


void DNN::initError()
{
    for(int i=0;i<this->AH;i++)
        for(int j=0;j<this->AW;j++)
            AE[i][j]=0;


    for(int i=0;i<this->BH;i++)
        for(int j=0;j<this->BW;j++)
            BE[i][j]=0;

    for(int i=0;i<this->CH;i++)
        for(int j=0;j<this->CW;j++)
            CE[i][j]=0;

}
