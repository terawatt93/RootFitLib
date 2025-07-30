#include <FitLib.hh>
#include <TalysLib.hh>
#include <Parser.hh>

class FFitResult
{
	public:
	int pix,det,num;
	double GammaEnergy;
	int flag=-1;//0-хороший, 1-плохой.... далее - как именно плохой
	TFitFunction *function=0;
	void FromString(string s)
	{
		stringstream sstr(s);
		sstr>>num>>pix>>det>>GammaEnergy;
	}
	void FromFuncName(string s)
	{
		vector<string> strings=SplitString(s,'_');
		if(strings.size()>3)
		{
			pix=atoi(strings[1].c_str());
			det=atoi(strings[2].c_str());
			GammaEnergy=atof(strings[3].c_str())/10;
		}
	}
};

void ClassifyFitResults(vector<FFitResult> &Fits,vector<FFitResult> &Bad,vector<FFitResult> &Good)
{
	ifstream ifs("bad.tsv");
	string line;
	int MaxNum=0;
	while(getline(ifs,line))
	{
		stringstream sstr(line);
		int pix,det,num;
		double GammaEnergy;
		sstr>>num>>pix>>det>>GammaEnergy;
		if(MaxNum<num)
		{
			MaxNum=num;
		}
		
		for(unsigned int i=0;i<Fits.size();i++)
		{
			if(Fits[i].pix==pix && Fits[i].det==det && abs(Fits[i].GammaEnergy - GammaEnergy) < 1)
			{
				Fits[i].flag=1;
				Bad.push_back(Fits[i]);
			}
		}
	}
	for(unsigned int i=0;i<Fits.size();i++)
	{
		if(Fits[i].num<MaxNum && Fits[i].flag==-1)
		{
			Fits[i].flag=0;
			Good.push_back(Fits[i]);
		}
	}
}

void ProcessFitFile()
{
	FitManager *m=FitManager::GetPointer("TiO2_outFits.root");
	vector<FFitResult> Fits, BadFits, GoodFits;
	for(unsigned int i=0;i<m->Functions.size();i++)
	{
		FFitResult fr;
		fr.FromFuncName(m->Functions[i]->id);
		fr.function=m->Functions[i];
		fr.num=i;
		Fits.push_back(fr);
	}
	ClassifyFitResults(Fits,BadFits,GoodFits);
	TXlsxwriter xl;
	xl.Open("Fits.xlsx");
	xl.GoToWorksheet("Fits");
	xl<<"n"<<"pix"<<"det"<<"EGamma"<<"Chi2"<<"Chi2_substrate"<<"Chi2_peaks"<<"Good or bad?"<<"\n";
	for(unsigned int i=0;i<Fits.size();i++)
	{
		int n, pix,det;
		double GammaEnergy, Chi2, Chi2_substrate, Chi2_peaks;
		string Type="not defined";
		n=Fits[i].num;
		pix=Fits[i].pix;
		det=Fits[i].det;
		GammaEnergy=Fits[i].GammaEnergy;
		if(Fits[i].flag==0)
		{
			Type="good";
		}
		else if(Fits[i].flag>0)
		{
			Type="bad";
		}
		
		Chi2=Fits[i].function->Function.GetChisquare()/Fits[i].function->Function.GetNDF();
		Chi2_substrate=Fits[i].function->EvalChi2Substrate(2);
		Chi2_peaks=Fits[i].function->EvalChi2Peaks(2);
		xl<<n<<pix<<det<<GammaEnergy<<Chi2<<Chi2_substrate<<Chi2_peaks<<Type<<"\n";
	}
}
