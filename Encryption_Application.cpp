//This program is written by Ulku Eylul Sahin on May 2020

#include<iostream>
#include <sstream>

using namespace std;

unsigned char P (unsigned char a)	//function to permute plaintext
{
	unsigned char c1, c2, c3, c4;
	c1 = a & 0x11;
	c1 = c1 << 2;

	c2 = a & 0x22;
	c2 = c2 >> 1;

	c3 = a & 0x44;
	c3 = c3 << 1;

	c4 = a & 0x88;
	c4 = c4 >> 2;

	a = c1|c2|c3|c4;

	return a;
}

int main()
{
	string key, plaintext, line;
	unsigned char  ciphertext;

	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl;
	cout<< "Please enter the encryption key: " ;

	int count=0;
	while(getline(cin, line))
	{
		if(count == 0)	//first string entered is key
		{
			key = line;
		}
		else
		{
			plaintext = line;
			cout <<"Ciphertext: ";
			int x=0;
			for(int i=0; i<plaintext.length(); i++)	//for all characters in plaintext
			{
				unsigned char temp = plaintext[i];
				ciphertext = P(temp);	//permute the characters  bits

				
				ciphertext = ciphertext ^ key[x];	//XOR operation starts from first char of key
				if(x < (key.length()-1))	//iterate chars of key
					x++;
				else //when key  chars end, come back to first char
					x=0;

				cout << hex << (int) ciphertext;	//print ciphertext
			}
			cout << endl;
		}
		cout << endl << "Please enter the plaintext to be encrypted: ";
		count++;
	}
	return 0;
}