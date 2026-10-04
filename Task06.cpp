#include<iostream>
#include<cstdlib>
int main(){
 const char* user = std::getenv("USERNAME");
if (user != nullptr)
std::cout << "Current user is: "
<< user << "\n";
}// lab1
