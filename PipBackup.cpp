#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <vector>
using namespace std;
size_t strpos(const string &haystack, const string &needle);
size_t strpos(const string &haystack, const string &needle)
{
    int sleng = haystack.length();
    int nleng = needle.length();
    if (sleng==0 || nleng==0)
        return string::npos;
    for(int i=0, j=0; i<sleng; j=0, i++ )
    {
        while (i+j<sleng && j<nleng && haystack[i+j]==needle[j])
            j++;
        if (j==nleng)
            return i;
    }
    return string::npos;
}
string ssystem(const char *command) {
    char tmpname [L_tmpnam];
    tmpnam ( tmpname );
    string scommand = command;
    string cmd = scommand + " >> " + tmpname;
    system(cmd.c_str());
    ifstream file(tmpname, ios::in | ios::binary );
    string result;
    if (file) {
        while (!file.eof()) result.push_back(file.get())
            ;
        file.close();
    }
    remove(tmpname);
    return result;
}
string FormatLine(string text)
{
int length = text.size();
int x = 0;
string fixed;
while (x != length) {
        string letter = text.substr(x, 1);
        if (letter == " ") {
           letter = "==";}
        fixed = fixed + letter;
        x = x + 1;
                    }
return fixed;
}
int main(int argc, char *argv[])
{
    cout <<"Backing up your pip modules..."<<endl;
    string bash = "pip list";
    string s = ssystem(bash.c_str());
    string in;
    istringstream iss(s);
    string line;
    string output;
    int checker = 0;
    bool isbackup = false;
    srand(time(0));
    int FileID = (rand() % (99999 - 11111)) + 11111;
    string filename = "backup_"+to_string(FileID)+".txt";
    ofstream BackupFile(filename);
    while (getline(iss, line))
    {
        if(line.find("is not recognized") != string::npos){
            cout<<"PIP is not installed in your system!";
            isbackup = false;
            break;
        }
        checker++;
        if(checker > 2 && line.length() > 3) {
            int pos = -1;
            while ((pos = line.find("  ")) != -1)
                line.replace(pos, sizeof("  ") - 1, " ");
            BackupFile << FormatLine(line);
            isbackup = true;
        }
    }
    if(isbackup){
        for (size_t i = 0; i < 30; i++)
            cout<<'.';
        cout<<endl;
        cout<<"Your pip list was successfully backed up in (backup_"+filename+".txt)!"<<endl;
        cout<<"To install the backup, just use this command : (python -m pip install -r backup_"+filename+".txt)"<<endl;
    }
    BackupFile.close();
    getch();
    return 0;
}
