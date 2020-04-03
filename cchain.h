#ifndef CCHAIN_H
#define CCHAIN_H

#include <vector>
#include <string>
#include <stdio.h>
using namespace std;

struct SField {
    //table
    string name;
    int type;
    int fieldSize;
    string description;
    SField() {}

};

class CChain {
public:
    CChain();
    CChain(string name) { this->name = name; }
    void Init();
    void AddField(SField newField);
    void EraseField(int id);
    SField* GetField(int id);
    string GetName() { return name; }
private:
    string name;
    vector<SField> fieldList;

};

#endif // CCHAIN_H
