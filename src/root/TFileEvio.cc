/**
* Autogenerated Source File for TFileEvio
* \\file TFileEvio.cc
* \\author G.Gavalian
* \\date 2014-09-24
*/
#include "TFileEvio.h"

ClassImp(TFileEvio)

TFileEvio::TFileEvio() : TDirectory("CLASEvio","CLAS Evio Directory")
{
  cd();
//TH1D *H = new TH1D("H100","sample histogram",100,0.1,0.2);
  //Add(H);
}
TFileEvio::TFileEvio(const char *filename) : TDirectory("CLASEvio","CLAS Evio Directory")
{
  cd();
  ReadFile(filename);
//TH1D *H = new TH1D("H100","sample histogram",100,0.1,0.2);
  //Add(H);
}
/* 
TFileEvio::TFileEvio(const TFileEvio &obj)
{
}
*/
TFileEvio::~TFileEvio()
{
}

TBrowser  *TFileEvio::Browse(){
  cd();
  return new TBrowser("CLASEvio",this);
}
/* const TFileEvio &TFileEvio::operator=(const TFileEvio &obj){} */

void TFileEvio::ReadFile(const char *filename){
  EvioFileReader *reader = new EvioFileReader();
  reader->open(filename);
  int nentries = reader->getEntries();

  for(int loop = 0; loop < nentries; loop++){
    cout << " reading event " << loop << endl;
    reader->readEvent(loop);
    int len_type;
    int len_bins;
    int len_data;
    int len_limits;
    int len_name;

    int32_t *type   = reader->getEvent().geti32( 200, 1, &len_type);
    int32_t *bins   = reader->getEvent().geti32( 200, 2, &len_bins);
    double  *limits = reader->getEvent().getd  ( 200, 3, &len_limits);
    double  *data   = reader->getEvent().getd  ( 200, 4, &len_data);
    int8_t  *name   = reader->getEvent().geti8 ( 200, 6, &len_name);

    char *nameChar = reinterpret_cast<char *> (name);
    //string hname;
    char *hname = new char[len_name+1];
    if(type!=NULL && bins!=NULL&&limits!=NULL && data!=NULL && name!=NULL){
      for(int loop = 0; loop < len_name; loop++){
          hname[loop] = nameChar[loop];
      }
      hname[len_name] = '\0';
      //cout << "type = " << type[0] << " BINS = " << bins[0] << "  length = " << len_bins 
      //<<  " name = " << hname << endl;
      TH1D *H = new TH1D(hname,hname,bins[0],limits[0],limits[1]);
      for(int loop = 0; loop < bins[0]; loop++){
        H->SetBinContent(loop+1,data[loop]);
      }
      Add(H);
    }
  }
  /*
  cout << " reading file " << filename << endl;
  TEvioFileReader *reader = new TEvioFileReader();
  TEvioDataEvent  *event  = new TEvioDataEvent();
  cout << " openning file " << filename << endl;
  reader->open(filename);
  //cout << " openning file " << filename << endl;
  int counter  = 0;
  //char hname[128]
    cout << " scanning file " << filename << endl;;

  while(reader->next()){
    cout << " reading event " << counter << endl;
  	reader->getEvent(*event);
  	//cout << " step 1" << endl;
  	TArrayI type = event->getIntegerArray(200,1);
  	TArrayI bins = event->getIntegerArray(200,2);
  	TArrayD binLimits  = event->getDoubleArray(200,3);
  	TArrayD binContent = event->getDoubleArray(200,4);
  	TArrayC name       = event->getCharArray(200,6);
  	//cout << " name size = " << name.GetSize() << endl;
  	if(bins.GetSize()>0){
  		//cout << " step 2" << endl;	
  		//sprintf(hname,"H%d",100+counter);
  		int nbins = bins.At(0);
      char *histogramName = GetNameFromArray(name);
  	 //cout << " step 3  name = " << histogramName << endl;
      TH1D *H = new TH1D(histogramName,histogramName,bins.At(0),binLimits.At(0),binLimits.At(1));
      delete histogramName;
  		
  		for(int loop = 0; loop < nbins; loop++){
  			H->SetBinContent(loop+1,binContent.At(loop));
  		}
  		Add(H);
  		counter++;
  	}	
  }*/
}



char  *TFileEvio::GetNameFromArray(TArrayC &array){
	int nameSize = array.GetSize()+1;
	char *name = new char[nameSize];

	for(int loop = 0 ; loop < nameSize - 1; loop++){
		name[loop] = array.At(loop);
	}
	name[nameSize-1] = '\0';
	return name;
}


