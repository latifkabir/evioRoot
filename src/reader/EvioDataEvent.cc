/**
* Autogenerated Source File for TEvioFileReader
* \\file TEvioFileReader.cc
* \\author G.Gavalian
* \\date 2012-07-14
*/
#include "EvioDataEvent.h"
#include "evio.h"
#include "evioUtil.hxx"
#include "evioBankIndex.hxx"
#include "evioTypedefs.hxx"
#include "EvioCompositeDecoder.h"
/**
 * Default constructor the internal buffer is empty.
 */
EvioDataEvent::EvioDataEvent()
{
}
/**
 * Copy constructor.
 * @param orig
 * @return 
 */
EvioDataEvent::EvioDataEvent(const EvioDataEvent& orig)
{
    memcpy(buffer,orig.buffer,MAXEVIOBUFFER);
}
/**
 * constructor takes pointer to the data, and copies it to internal buffer.
 */
EvioDataEvent::EvioDataEvent(uint32_t *ptr, int len)
{
  init(ptr,len);
}
/**
 * Default Distructor.
 */
EvioDataEvent::~EvioDataEvent()
{
}
void EvioDataEvent::getList(){
  evio::evioDOMTree event(buffer);
  evio::evioDOMNodeListP fullList     = event.getNodeList();
  evio::evioDOMNodeList::const_iterator iter;
  for(iter=fullList->begin(); iter!=fullList->end(); iter++) {
    cout << "bank type,tag,num are: " << hex << "  0x" << (*iter)->getContentType() << dec << "  "  << (*iter)->tag
	 << "  " << (int)((*iter)->num) << endl;
  }
  
}
/**
 * initilizes the event with given evio buffer.
 */
void EvioDataEvent::init(uint32_t *ptr, int len)
{
  //cout << " initializing event with len = " << len << endl;
  memcpy(buffer,ptr,len*sizeof(int32_t));
}
/**
 * returns a bank containing double and int arrays filled from a data bank 
 * with given tag and num.
 */
void EvioDataEvent::getBank(EvioDataBank &bank, int tag, int num)
{
    bank.clear();
}
/**
 * returns a double vector containing data from a leaf for given tag and num.
 */
vector<double>  *EvioDataEvent::getDoubleVector(int tag, int num)
{
  evio::evioBankIndex b0(buffer,0);
  evio::bankIndex b;
  if(b0.tagNumExists(evio::tagNum(tag,num))){
    b = b0.getBankIndex(evio::tagNum(tag,num));
    int dataLength;
    const double *data_ptr = b0.getData<double>(b,&dataLength);
    vector<double> *vec_ptr = new vector<double>(dataLength);
    memcpy(vec_ptr->data(),data_ptr,dataLength*sizeof(double));
    return vec_ptr;
  }
  return new vector<double>();
}

vector<float>  *EvioDataEvent::getFloatVector(int tag, int num)
{
  evio::evioBankIndex b0(buffer,0);
  evio::bankIndex b;
  if(b0.tagNumExists(evio::tagNum(tag,num))){
    b = b0.getBankIndex(evio::tagNum(tag,num));
    int dataLength;
    const float *data_ptr = b0.getData<float>(b,&dataLength);
    vector<float> *vec_ptr = new vector<float>(dataLength);
    memcpy(vec_ptr->data(),data_ptr,dataLength*sizeof(float));
    return vec_ptr;
  }
  return new vector<float>();
}

vector<uint8_t> *EvioDataEvent::getVectorInt8(int tag, int num){
  evio::evioBankIndex b0(buffer,0);
  evio::bankIndex b;
  if(b0.tagNumExists(evio::tagNum(tag,num))){
    b = b0.getBankIndex(evio::tagNum(tag,num));
    //cout << " bank found index = " << b.bankLength << "  data length = " << b.dataLength << endl;
    int dataLength = b.dataLength;
    //const uint8_t *data_ptr = b0.getData<uint8_t>(b,&dataLength);
    //cout << "  Data Length at Get = " << dataLength << endl;
    vector<uint8_t> *vec_ptr = new vector<uint8_t>(dataLength);
    memcpy(vec_ptr->data(),b.data, dataLength*sizeof(uint8_t));
    return vec_ptr;
  }
  return new vector<uint8_t>();
}
/**
 * returns a integer vector containing data from a leaf for given tag and num.
 */
vector<int32_t> *EvioDataEvent::getIntegerVector(int tag, int num)
{
  evio::evioBankIndex b0(buffer,0);
  evio::bankIndex b;
  if(b0.tagNumExists(evio::tagNum(tag,num))){
    b = b0.getBankIndex(evio::tagNum(tag,num));

    int dataLength;
    const int32_t *data_ptr = b0.getData<int32_t>(b,&dataLength);
    vector<int32_t> *vec_ptr = new vector<int32_t>(dataLength);
    memcpy(vec_ptr->data(),data_ptr,dataLength*sizeof(int32_t));
    return vec_ptr;
  }
  return new vector<int32_t>();
}


vector<CompositeADC_t>  EvioDataEvent::getCompositeData(int tag, int num){
  
  evio::evioDOMTree event(buffer);
  evio::evioDOMNodeListP fullList     = event.getNodeList();
  evio::evioDOMNodeList::const_iterator iter;
  EvioCompositeDecoder decoder;

  vector<CompositeADC_t>  result;
  for(iter=fullList->begin(); iter!=fullList->end(); iter++) {
    if((*iter)->tag==tag&& ((int)(*iter)->num)==num){
      const evio::evioCompositeDOMLeafNode *leaf = static_cast<const evio::evioCompositeDOMLeafNode*>(*iter);
      int leafSize = leaf->getSize();
      //cout << "  SIZE = " << leaf->getSize() << endl;
      vector<uint32_t> *pData = const_cast<vector<uint32_t> *>(&(leaf->data));
      decoder.decode(pData,leafSize);
      if(decoder.getData().size()>0){
	try{
	  vector<CompositeADC_t>  decdata = decoder.getData();
	  for(int loop = 0; loop < decdata.size();loop++){
	    //result.insert(result.end(), decoder.getData().begin(), decoder.getData().end());
	    result.push_back(decdata[loop]);
	    //for(int i = 0; i < decdata[loop].samples.size(); i++){
	      //cout << " " << decdata[loop].samples[i];
	    //} //cout << endl;
	  }
	} catch (exception e){
	  cout << "ERROR" << endl;
	}
      }
      /*
      for(int loop = 0; loop < 10; loop++){
	printf("%X ",(*pData)[loop]);
      } printf("\n");
      char *archive = new char[lsize*4];
      memcpy(archive,reinterpret_cast<char *> (&(*pData)[0]),lsize*4);
      decodeCompositeData(archive,lsize*4);*/
      //vector<uint32_t> *vec =  &(leaf->data);      
      //int32_t *datavoid = const_cast<int32_t *> (&(leaf->data[0]));
      //int  *arrdata  = reinterpret_cast<int *> (datavoid);
      //char *arrchar  = reinterpret_cast<char *> (&arrdata[3+4]);
      //int size = leaf->getSize();
      //decodeCompositeData(iter);
      //cout << "bank type,tag,num are: " << hex << "  0x" << (*iter)->getContentType() << dec << "  "  << (*iter)->tag
      //<< "  " << (int)((*iter)->num) << endl;
    }
  }
  /*
    evio::evioDOMTree event(buffer);
    evio::evioDOMNodeP n = event.getFirstNode(evio::tagNumEquals(tag,num));
    if(n!=NULL) {
    cout << "Found node:  " << tag << "  " << num << "  " << endl << endl;
    cout << n->toString() << endl;
    } else {
    cout << "?unable to find string node" << endl;
    }*/
  return result;
}

uint8_t EvioDataEvent::getInt8(char *data, int offset){
  uint8_t value = *(reinterpret_cast<uint8_t *>(&data[offset]));
  return value;
}

uint16_t EvioDataEvent::getInt16(char *data, int offset){
  uint16_t value = *(reinterpret_cast<uint16_t *>(&data[offset]));
  return value;
}

uint32_t EvioDataEvent::getInt32(char *data, int offset){
  uint32_t value = *(reinterpret_cast<uint32_t *>(&data[offset]));
  return value;
}

int64_t EvioDataEvent::getInt64(char *data, int offset){
  int64_t value = *(reinterpret_cast<int64_t *>(&data[offset]));
  return value;
}

void EvioDataEvent::decodeCompositeData(char *data, int size){
  //int offset = 3+4+8;
  int offset = 0;
  //for(int loop = 0; loop < 40; loop++){
  //uint8_t      slot       = *(reinterpret_cast<uint8_t *>(&data[offset+loop]));
  //unsigned int  nchan     = *(reinterpret_cast<uint32_t *>(&data[offset+loop + 1 +4 +8]));
  //printf("LOOP %3d  DATA %X  SLOT = %d NCHAN = %d\n",loop,data[loop],slot,nchan);
  //}
  //return;
  uint8_t   slot       = getInt8 ( data, offset);
  uint32_t  trigger    = getInt32( data, offset + 1);
  unsigned long long time = getInt64( data, offset + 1 + 4);
  int  nchan     = getInt32( data, offset + 1 + 4 + 8);
  cout << " decoding : SLOT = " << (unsigned int) slot << "  TRIGGER = " << trigger << "  TIME = " << time << " NCHAN = " << nchan  << endl;
  printf("SLOT = %d \n",slot);
  //return;
  offset = offset + 1 + 4 + 8 + 4;
  int nchannels = 0;
  while(offset<size){
    uint8_t  chan    = getInt8(data,offset);
    uint32_t samples = getInt32(data,offset+1);
    offset = offset + 1 + 4;
    //cout << " CHANNEL = " << (unsigned int) chan << "  SAMPLES = " << (unsigned int) samples << "  " << 
    //offset + samples*sizeof(short) << "  " << size << endl;;
    if(offset + samples*sizeof(short) > size) break;
    cout << " scanning channels" << endl;
    for(int loop = 0; loop < samples; loop++){
      short sp = getInt16(data, offset);
      offset += 2;
      cout << sp << " " ;
    }
    cout << endl;
    nchannels++;
    if(nchannels>=nchan) break;
  }
}
