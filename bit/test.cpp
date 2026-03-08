#include <iostream>
using namespace std;

int main()
{
  const char* p = "0123456789";
  cout<< p <<endl;
  for(size_t i = 0; p[i]; i++)
  {
    cout<< "p "<< " + " << i << " = " << p[i] <<endl;
  }
  cout<<endl;

  return 0;
}
