//A sum program
#include<iostream>
#include<cstdlib>    //double atof(char*)
using namespace std;

int main(void)
{
	double m;
	double n;
	char a[10];
	char b[10];
	cout<<"Please input the first digit:";
	cin>>a;
	m=atof(a);
	cout<<"Please input the second digit:";
	cin>>b;
	n=atof(b);
	cout<<"The results is:"<<m+n<<endl;

	
	return 0;
}
