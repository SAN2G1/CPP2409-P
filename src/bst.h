#include <iostream>
#include <vector>
using namespace std;

typedef struct fdata
{
    string file_name;
    int year;
    int month;
    int day;
    bool operator>(const fdata &fdata) const;
    bool operator<(const fdata &fdata) const;

} fdata;

// binary search tree
typedef struct bsTree
{
    struct fdata file_data;
    bsTree *left;
    bsTree *right;
} bsTree;

bsTree *Insert(fdata, bsTree *);
bsTree *MakeNode(fdata);
vector<string> Search(int, int, int, bsTree *);
vector<string> Search(int , int, bsTree *node);
vector<string> Search(int , bsTree *);


void DeleteTree(bsTree*); //할당을 해제하는 함수
