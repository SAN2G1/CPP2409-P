#include <iostream>

#include "bst.h"

using namespace std;
bool fdata::operator>(const fdata &other) const
{
    if (year > other.year)
        return true;
    if (year == other.year && month > other.month)
        return true;
    if (year == other.year && month == other.month && day > other.day)
        return true;
    return false;
}
bsTree *insert(fdata fdata, bsTree *node)
{
    if (node == nullptr)
        return makeNode(fdata); // 트리가 공백이면 새로운 노드를 만들어 반환
    // left가 공백이면 위 조건으로 인해 삽입되고 left가 공백이 아니라면 계속 탐색한다.
    if (node->file_data > fdata) // 연산자 오버로딩적용
        node->left = insert(fdata, node->left);
    else
        node->right = insert(fdata, node->right);
    return node; // 변경된 노드를 반환한다.
}
bsTree *makeNode(fdata fdata)
{
    bsTree *tmp = new bsTree{fdata, nullptr, nullptr}; 
    // NULL vs nullptr 코드의 명확성과 타입 안정성을 높이는 최신 cpp 스타일임.
    return tmp;
}
