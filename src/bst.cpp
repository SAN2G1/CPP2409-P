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
bool fdata::operator<(const fdata &other) const
{
    if (year < other.year)
        return true;
    if (year == other.year && month < other.month)
        return true;
    if (year == other.year && month == other.month && day < other.day)
        return true;
    return false;
}
bsTree *Insert(fdata fdata, bsTree *node)
{
    if (node == nullptr)
        return MakeNode(fdata); // 트리가 공백이면 새로운 노드를 만들어 반환
    // left가 공백이면 위 조건으로 인해 삽입되고 left가 공백이 아니라면 계속 탐색한다.
    if (node->file_data > fdata) // 연산자 오버로딩적용
        node->left = Insert(fdata, node->left);
    else
        node->right = Insert(fdata, node->right);
    return node; // 변경된 노드를 반환한다.
}
bsTree *MakeNode(fdata fdata)
{
    bsTree *tmp = new bsTree{fdata, nullptr, nullptr};
    // NULL vs nullptr 코드의 명확성과 타입 안정성을 높이는 최신 cpp 스타일임.
    return tmp;
}
//함수 오버로딩
vector<string> Search(int year, int month, int day, bsTree *node)
{
    vector<string> results;
    if (node == nullptr)
        return results; // 노드가 없으면 빈 문자열 반환
    if (node->file_data.year == year && node->file_data.month == month && node->file_data.day == day)
        results.push_back(node->file_data.file_name);

      // 왼쪽 서브트리와 오른쪽 서브트리를 탐색하여 결과를 병합
    vector<string> leftResults = Search(year, month, node->left);
    vector<string> rightResults = Search(year, month, node->right);

    // 왼쪽과 오른쪽 결과 병합
    results.insert(results.end(), leftResults.begin(), leftResults.end());
    results.insert(results.end(), rightResults.begin(), rightResults.end());

    return results;
}

vector<string> Search(int year, int month, bsTree *node)
{
    vector<string> results;
    if (node == nullptr)
        return results; // 현 노드가 비어있으면 빈 벡터를 반환
    //현재 노드가 데이터 조건을 만족하면 추가
    if (node->file_data.year == year && node->file_data.month == month)
        results.push_back(node->file_data.file_name);

// 왼쪽과 오른쪽 서브트리를 탐색. 
// template <class InputIterator>iterator insert (const_iterator position, InputIterator first, InputIterator last);

   // 왼쪽 서브트리와 오른쪽 서브트리를 탐색하여 결과를 병합
    vector<string> leftResults = Search(year, month, node->left);
    vector<string> rightResults = Search(year, month, node->right);

    // 왼쪽과 오른쪽 결과 병합
    results.insert(results.end(), leftResults.begin(), leftResults.end());
    results.insert(results.end(), rightResults.begin(), rightResults.end());

    return results;
}
vector<string> Search(int year, bsTree *node)
{
    vector<string> results;
    if (node == nullptr)
        return results; // 현 노드가 비어있으면 빈 벡터를 반환
    //현재 노드가 데이터 조건을 만족하면 추가
    if (node->file_data.year == year )
        results.push_back(node->file_data.file_name);

// 왼쪽과 오른쪽 서브트리를 탐색. 
// template <class InputIterator>iterator insert (const_iterator position, InputIterator first, InputIterator last);

   // 왼쪽 서브트리와 오른쪽 서브트리를 탐색하여 결과를 병합
    vector<string> leftResults = Search(year, node->left);
    vector<string> rightResults = Search(year, node->right);

    // 왼쪽과 오른쪽 결과 병합
    results.insert(results.end(), leftResults.begin(), leftResults.end());
    results.insert(results.end(), rightResults.begin(), rightResults.end());

    return results;
}

void DeleteTree(bsTree* node){
    if (node == nullptr)
        return;
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}