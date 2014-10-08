/**
* Autogenerated Header File for TBankDescriptor
* \\file TBankDescriptor.h
* \\author G.Gavalian
* \\date 2014-09-26
*/
#ifndef __TBANKDESCRIPTOR__
#define __TBANKDESCRIPTOR__
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "TROOT.h"
#include "TObject.h"

using namespace std;
//! A Brief Description
/*
 * A detailed description
 */
class TBankDescriptor  : public TObject {

private:
  string  descName;
  vector< pair<int,int> > entryTagNum;
  vector< pair<string,string> > entryNameType;

public:

/** Default Constructor */
TBankDescriptor();
TBankDescriptor(const char *name);
/** Default Destructor */
~TBankDescriptor();
/** Copy Constructor if one is needed */
/*TBankDescriptor( const TBankDescriptor &obj); */ 

void   Copy(const char *name, int tag, TBankDescriptor &desc);
void   Copy(TBankDescriptor &desc);
void   AddEntry(const char *name, const char *type,int tag, int num);
int    GetEntries();

bool   isInt8   ( int entry );
bool   isInt32  ( int entry );
bool   isInt16  ( int entry );
bool   isFloat  ( int entry );
bool   isDouble ( int entry );

string GetFormatString();

int    GetTag(int entry);
int    GetNum(int entry);
const char *GetName();
const char *GetEntryName(int entry);
const char *GetEntryType(int entry);

void Print();
void SetName(const char *name);
/** An operator = if one is needed */
/* const TBankDescriptor &operator=(const TBankDescriptor &obj); */

 ClassDef(TBankDescriptor,1)

};
#endif