#include <iostream>
#include <fstream>

char Base64Char(unsigned char b) {
	if (b >= 'A' && b <= 'Z')return b - 65;
    if (b >= 'a' && b <= 'z')return b - 71;
    if (b >= '0' && b <= '9')return b + 4;
    if (b == '+')return 62;
    if (b == '/')return 63;
    return 0;
}
int Base64Decode(char *inStr, int Len, char *outStr) {
	int i = 0, j = 0;
	for (i = 0; i < Len; i += 4) {
		unsigned char a1, a2, a3, a4;
		char b1, b2, b3;
		a1 = Base64Char(inStr[i]);
		a2 = Base64Char(inStr[i+1]);
		a3 = Base64Char(inStr[i+2]);
		a4 = Base64Char(inStr[i+3]);
		b1 = ( ( a1 << 2 ) | ( a2 >> 4 ) );
		b2 = ( ( a2 << 4 ) | ( a3 >> 2 ) );
		b3 = ( ( a3 << 6 ) | a4 );
		outStr[j++] = b1;
		outStr[j++] = b2;
		outStr[j++] = b3;
	}
	return j;
}
int main()
{
	char inputFileName[1024];
	char outputFileName[1024];
	std::cout << "Input source file name: ";
	std::cin.getline(inputFileName, 1024);
	
	std::ifstream inFile(inputFileName);
	if (!inFile) {
		std::cout << "Can not open file " << inputFileName << std::endl;
		return 1;
	}

	std::cout << "Input destination file name: ";
	std::cin.getline(outputFileName, 1024);

	std::ofstream outFile(outputFileName);
	if (!outFile) {
		inFile.close();
		std::cout << "Can not write to file " << outputFileName << std::endl;
		return 2;
	}
	const int block_size = 1;
    char inStr[4 * block_size], outStr[3 * block_size];
    int s;
    while (inFile.peek() != EOF) {
        s = 0;
        for (int i = 0; i < 4*block_size;++i) {
            if(inFile.peek() != EOF)
            {
            	char ch;
	            ch=inFile.get();
	            if (isalpha(ch)||isdigit(ch)||ch=='+'||ch=='/'||ch=='=')
				{
					inStr[i] = ch;
					++s;
	            }
			}
        }
        s=Base64Decode(inStr,s,outStr);
        outFile.write(outStr,s);
    }
	inFile.close();
	outFile.close();
	std::cout << "Decoded - OK" << std::endl;
}
