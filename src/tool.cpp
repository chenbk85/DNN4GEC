#include "DNN.h"

void DNN::saveModel(string ofile)
{
    string ofileA = ofile+"A";
    string ofileB = ofile+"B";
    string ofileC = ofile+"C";

    saveMaxtrixA(ofileA);
    saveMaxtrixB(ofileB);
    saveMaxtrixC(ofileC);
}

void DNN::saveMaxtrixA(string ofile)
{
    ofstream fout(ofile.c_str());
    fout<<this->AH<<"\t"<<this->AW<<"\n";
    for(int i=0;i<AH;i++)
    {
        for(int j=0;j<AW-1;j++)
        {
            fout<<A[i][j]<<"\t";
        }
        fout<<A[i][AW-1]<<"\n";
    }
    fout.close();

}

void DNN::saveMaxtrixB(string ofile)
{
    ofstream fout(ofile.c_str());
    fout<<this->BH<<"\t"<<this->BW<<"\n";
    for(int i=0;i<BH;i++)
    {
        for(int j=0;j<BW-1;j++)
        {
            fout<<B[i][j]<<"\t";
        }
        fout<<B[i][BW-1]<<"\n";
    }
    fout.close();
}

void DNN::saveMaxtrixC(string ofile)
{
    ofstream fout(ofile.c_str());
    fout<<this->CH<<"\t"<<this->CW<<"\n";
    for(int i=0;i<CH;i++)
    {
        for(int j=0;j<CW-1;j++)
        {
            fout<<C[i][j]<<"\t";
        }
        fout<<C[i][CW-1]<<"\n";
    }
    fout.close();
}

void DNN::loadModel(string ofile)
{

    cout<<"load model from "<<ofile<<endl;
    string ofileA = ofile+"A";
    string ofileB = ofile+"B";
    string ofileC = ofile+"C";

    loadMaxtrixA(ofileA);
    loadMaxtrixB(ofileB);
    loadMaxtrixC(ofileC);

}

void DNN::loadMaxtrixA(string ofile)
{
    ifstream fin(ofile.c_str());
    int h=0,w=0;
    fin>>h>>w;
    assert(h==AH && w==AW);
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            fin >> A[i][j];
            assert(fin);
        }
    }

}

void DNN::loadMaxtrixB(string ofile)
{
    ifstream fin(ofile.c_str());
    int h=0,w=0;
    fin>>h>>w;
    assert(h==BH && w==BW);
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            fin >> B[i][j];
            assert(fin);
        }
    }

}

void DNN::loadMaxtrixC(string ofile)
{
    ifstream fin(ofile.c_str());
    int h=0,w=0;
    fin>>h>>w;
    assert(h==CH && w==CW);
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            fin >> C[i][j];
            assert(fin);
        }
    }
}


double DNN::normal(double E, double V)
{
    static double V1, V2, S;
    static int phase = 0;
    double X;

    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;

            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);

        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);

    phase = 1 - phase;

    X = X*V + E;
    return X;
}



double DNN::activate_tanh(double val)
{
	if(val < -maxEXP)
	{
		return -1.0;
	}
	else if (val > maxEXP)
	{
		return 1.0;
	}
	else
		return tanh(val);
}

double DNN::activate_tanh_output(double val)
{
	if(val < -maxEXP)
		return -1.7159;
	else if (val > maxEXP)
		return 1.7159;
	else
		return 1.7159*tanh(2.0*val/3.0);
}


void DNN::setWP()
{
    for(int i=0;i<WPW;i++)
    {
        int index = (i-1)*this->vectorL;
        for(int j=0;j<WPH;j++)
        {
            if(index<0)
            {
                WP[j][i] = vbe[index+vectorL];
                assert(index+vectorL<vectorL && index+vectorL >=0);   //can comment !
                index++;
            }
            else if(index<inputL)
            {
                WP[j][i] = input[index++];
            }
            else
            {
                WP[j][i] = vbe[index-inputL];
                assert(index-inputL>=0 && index-inputL<vbeL);  //can comment !
                index ++;
            }
        }
    }
}