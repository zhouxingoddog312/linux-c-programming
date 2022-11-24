#include <iostream>
using namespace std;
int main()
{
	int acnt=0,ecnt=0,icnt=0,ocnt=0,ucnt=0,spacecnt=0,tcnt=0,ncnt=0;
	char ch;
	while(cin.get(ch))
	{
		switch(ch)
		{
			case 'a':case'A':
				acnt++;
				break;
			case 'e':case 'E':
				ecnt++;
				break;
			case 'i':case 'I':
				icnt++;
				break;
			case 'o':case 'O':
				ocnt++;
				break;
			case 'u':case 'U':
				ucnt++;
				break;
			case ' ':
				spacecnt++;
				break;
			case '\t':
				tcnt++;
				break;
			case '\n':
				ncnt++;
				break;
			default:
				;
		}
	}
	cout<<"Number of vowel a:\t"<<acnt<<endl;
	cout<<"Number of vowel e:\t"<<ecnt<<endl;
	cout<<"Number of vowel i:\t"<<icnt<<endl;
	cout<<"Number of vowel o:\t"<<ocnt<<endl;
	cout<<"Number of vowel u:\t"<<ucnt<<endl;
	cout<<"Number of vowel space:\t"<<spacecnt<<endl;
	cout<<"Number of vowel \\t:\t"<<tcnt<<endl;
	cout<<"Number of vowel \\n:\t"<<ncnt<<endl;
	return 0;
}
