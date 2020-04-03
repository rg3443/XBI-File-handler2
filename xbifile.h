#ifndef XBIFILE_H
#define XBIFILE_H

#include <vector>
#include <string>
#include <stdio.h>
using namespace std;
#include "cchain.h"
//#include "FileSys/cfilesystem.h"

class XBIfile {
public:
    XBIfile();
    void Init( string name, string path );
    void AddChain( string chainName );
    CChain* GetChain(int id);

    string GetPath() { return path; }
    string GetName() { return name; }
    int GetChainSize() { return chainList.size(); }
private:
    string name,path;
    vector<CChain> chainList;
  //  CFileSystem fileStream;

};

#endif // XBIFILE_H
