#include<iostream>
using namespace std;
#include<fstream>
int main(int argc,char* argv[]){
 std::ofstream file("diary.txt");
file << "Hello OS\n";
file.close();}