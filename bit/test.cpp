#include <iostream>
#include <string>
using namespace std;

int main()
{
  string s1("asdfdasfsfasd");
  string s2(s1);
  string s3("abcdefg", 2, 3);
  cout<< s1 <<endl; 
  cout<< s2 <<endl; 
  cout<< s3 <<endl; 
  
  cout<< "s1.size = " << s1.size() <<endl;
  cout<< "s2.size = " << s2.size() <<endl;
  cout<< "s3.size = " << s3.size() <<endl;

  cout<< "s1.capacity = " << s1.capacity() <<endl;
  cout<< "s2.capacity = " << s2.capacity() <<endl;
  cout<< "s3.capacity = " << s3.capacity() <<endl;

  return 0;
}
