#include <string>


using namespace std;
typedef struct format {
    string tag ;
    string strContent;

}format ;

string getCurrentDate();
string getCurrentDateTime();
string caesar(const string& plaintext, int key);
void writediary(format * diaryFormat);
bool fileExists(const std::string& fileName);