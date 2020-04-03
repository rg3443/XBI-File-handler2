#include "xbifile.h"

XBIfile::XBIfile()
{

}

void XBIfile::Init(string name, string path)
{
    this->name = name;
     this->path = path;
}

void XBIfile::AddChain(string chainName)
{
    chainList.push_back(CChain(chainName));
   // fileStream.Open(path);
   // fileStream
}

CChain* XBIfile::GetChain(int id)
{
    return &chainList[id];
}
