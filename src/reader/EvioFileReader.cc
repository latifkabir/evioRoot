/**
* Autogenerated Source File for TEvioFileReader
* \\file TEvioFileReader.cc
* \\author G.Gavalian
* \\date 2012-07-14
*/
#include "EvioFileReader.h"
//#include "TEvioDataBank.h"

#include "evio.h"
#include "evioUtil.hxx"
#include "evioBankIndex.hxx"

EvioFileReader::EvioFileReader()
{
  cout << "***************************************************************" << endl;
  cout << "*  Initializing EvioFileReader library implementing interface *" << endl;
  cout << "***************************************************************" << endl;
}
/*
TEvioFileReader::TEvioFileReader(const TEvioFileReader &obj)
{
}
*/

EvioFileReader::~EvioFileReader()
{
}

void EvioFileReader::close()
{
  evClose(evioFileHandle);
  cout << " EVENTS READ = " << numberOfEventsRead << "  TIME = " 
          << readTimeTotalMS
          << " ms " << endl;
}
/**
 * Open a File with given filename. Check for access.
 */
void EvioFileReader::open(const char *filename)
{
  char file[128];
  currentFileName = filename;
  sprintf(file,"%s",filename);
  evOpen(file,"r",&evioFileHandle);
  numberOfEventsRead = 0;
  readTimeTotalMS    = 0.0;
  cout << "***** OPENED FILE : " << filename << endl;
}

/**
 * Reads next event into internal buffer. returns true if there is an event in the file,
 * and false if end of file is reached.
 */

bool EvioFileReader::next()
{
    long double start_time = time(0);
    int read_status = evRead(evioFileHandle,buffer,MAXEVIOBUF);
    //cout << "read status = " << read_status << endl;
    long double end_time   = time(0);
    //cout << " measured = " << start_time << " " << end_time << endl;
    if(read_status!=-1){
        readTimeTotalMS += (end_time-start_time)*1000.0;
        numberOfEventsRead += 1;
        dataEvent.init(buffer,MAXEVIOBUF);
        return true;
    }
    return false;
}

const EvioDataEvent &EvioFileReader::getEvent()
{
    return dataEvent;
}

void  EvioFileReader::getEvent(EvioDataEvent &event)
{
    event.init(buffer,MAXEVIOBUF);
}

vector<double>   *EvioFileReader::getDoubleVector(int tag, int num)
{
  evio::evioBankIndex b0(buffer,0);
  evio::bankIndex b;
  if(b0.tagNumExists(evio::tagNum(tag,num))){
    //cout << " found data with tag and num = " << tag << "  " << num << endl;                                                                           
    b = b0.getBankIndex(evio::tagNum(tag,num));
    int dataLength;
    const double *data_ptr = b0.getData<double>(b,&dataLength);
    //cout << " found data with tag and num = " << tag << "  " << num << "  length = " << dataLength << endl;                                            
    vector<double> *vec_ptr = new vector<double>(dataLength);
    memcpy(vec_ptr->data(),data_ptr,dataLength*sizeof(double));
    return vec_ptr;
  }
  return new vector<double>();
}

vector<int32_t>  *EvioFileReader::getIntVector(int tag, int num)
{
  evio::evioBankIndex b0(buffer,0);
  evio::bankIndex b;
  
  if(b0.tagNumExists(evio::tagNum(tag,num))){
    //cout << " found data with tag and num = " << tag << "  " << num << endl;
    b = b0.getBankIndex(evio::tagNum(tag,num));
    int dataLength;
    const int32_t *data_ptr = b0.getData<int32_t>(b,&dataLength);
    //cout << " found data with tag and num = " << tag << "  " << num << "  length = " << dataLength << endl;
    vector<int32_t> *vec_ptr = new vector<int32_t>(dataLength);
    memcpy(vec_ptr->data(),data_ptr,dataLength*sizeof(int32_t));
    return vec_ptr;
  }
  return new vector<int32_t>();
}

void              EvioFileReader::getBank(EvioDataBank& bank,int tag, int num)
{
  
}

string            EvioFileReader::getDataFormat(int tag, int num)
{
}

