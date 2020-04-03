#include "cchain.h"

CChain::CChain()
{

}

void CChain::Init()
{

}

void CChain::AddField(SField newField)
{
    fieldList.push_back( newField );
}

void CChain::EraseField(int id)
{
    if(id > 0 || id < fieldList.size()) {
        fieldList.erase( fieldList.begin() + id );
    }
}

SField* CChain::GetField(int id)
{
    if(id > 0 || id < fieldList.size()) {
        return &fieldList[id];
    }
}
