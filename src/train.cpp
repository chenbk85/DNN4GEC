#include "DNN.h"

void DNN::train(string trainFile,string validateFile,string model,int times,double tol)
{

    ifstream fin(trainFile.c_str());
    cout<<"Call the train function ..."<<endl;
    cout<<"Read the File:"<<"\t"<<trainFile<<endl;

    int decayTime = 1;  //decay the alpha 's time ;
    int trainTime = 1;   //train time;
    int perTrainTime = 1; // each term 's train time;

    int lastTimeError = 0;
    int trainError = 0;

    while(true)
    {
    	initError(); //initial the error variable !
    	for(int i=0;i<this->miniBatch;i++)
    	{
    		int nid=0,pid=0,sid=0,posi=0,ti=0,stag=0;
    		fin >> nid >> pid >> sid >> posi >> ti >> stag >> expectIndex;

    		if(fin.eof())
    		{
                fin.clear();
                fin.seekg(0,fin.beg);

                trainError = validate(validateFile);
                double dela = lastTimeError-trainError;
                lastTimeError = trainError;
                cout<<trainTime<<"\tError Decrease:\t"<<dela<<"\t"<<trainError<<"\t"<<this->alpha<<endl;

                if(dela<0 && perTrainTime>miniTrainTime)
                {
                	if(decayTime>LRNUM)
                		break;
                	int nnd =  decayTime%2?2:5;
                	decayTime++;
                	perTrainTime = 1;

                	this->alpha = this->alpha/nnd;
                	loadModel(model);
                }
				//save the model only when the model is better!
				if(dela>0)
					saveModel(model);

                trainTime ++;
                perTrainTime ++;

    			fin >> nid >> pid >> sid >> posi >> ti >> stag >> expectIndex;
    		}
            assert(fin);
    		for(int j=0;j<inputL;j++)
            {
                fin >> input[j];
                assert(fin);
            }

    		propagate();
    	}

        if(trainTime>times || decayTime>LRNUM)
            break;

    	backpropagate();
    }
    fin.close();
}


double DNN::validate(string validateFile)
{
	ifstream fin(validateFile.c_str());

	double trainError = 0.0;
	while(true)
	{
		int nid=0,pid=0,sid=0,posi=0,ti=0,stag=0;
		fin >> nid >> pid >> sid >> posi >> ti >> stag >> expectIndex;

		if(fin.eof())
		{
			return trainError;
		}

		for(int j=0;j<inputL;j++)
			fin >> input[j];

		trainError += propagate();
	}
}
