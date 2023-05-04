#include <iostream>
#include <map>
#include <vector>
#include <windows.h>

using namespace std;


int main()
{
	cout<<"Iniciando o sistema\n";
	for(int i = 0; i < 15; i++)
	{
    cout<<"\r[";
    for(int j = 0; j < 15; j++)
    {
      if(i >= j)
      {
        cout<<"=";
      }
      else
      {
        cout<<" ";
      }
      
    }
    cout<<"]";
		Sleep(100);
	}
	cout<<endl;

}