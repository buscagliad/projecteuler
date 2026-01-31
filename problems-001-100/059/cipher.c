#ifdef PROBLEM_DESCRIPTION

XOR decryption
Problem 59

Each character on a computer is assigned a unique code and the preferred standard is ASCII (American Standard Code for Information Interchange). For example, uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.

A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each byte with a given value, taken from a secret key. The advantage with the XOR function is that using the same encryption key on the cipher text, restores the plain text; for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.

For unbreakable encryption, the key is the same length as the plain text message, and the key is made up of random bytes. The user would keep the encrypted message and the encryption key in different locations, and without both "halves", it is impossible to decrypt the message.

Unfortunately, this method is impractical for most users, so the modified method is to use a password as a key. If the password is shorter than the message, which is likely, the key is repeated cyclically throughout the message. The balance for this method is using a sufficiently long password key for security, but short enough to be memorable.

Your task has been made easy, as the encryption key consists of three lower case characters. Using p059_cipher.txt (right click and 'Save Link/Target As...'), a file containing the encrypted ASCII codes, and the knowledge that the plain text must contain common English words, decrypt the message and find the sum of the ASCII values in the original text.
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_FILE 5000

char edata[MAX_FILE];	// encrypted data
int edata_size;
char udata[MAX_FILE];	// unencrypted data

void efile(const char *fname)
{
	FILE *f = fopen(fname, "r");
	char *p = edata;
	memset(edata, 0, MAX_FILE);
	while (!feof(f))
	{
		int c = fgetc(f);
		if (feof(f)) break;
		if (c == ',') p++;
		else
			*p = 10 * (*p) + (c - '0');
	}
	fclose(f);
	edata_size = p-edata+1;

}

void	decipher(char a, char b, char c)
{
	char fn[] = {a, b, c, '.', 't', 'x', 't', 0};
	FILE *f = fopen(fn, "w");
	char *p = edata;
	char *u = udata;
	for (int i = 0; i < edata_size; i+=3)
	{
		*u = *p ^ a; u++; p++;
		*u = *p ^ b; u++; p++;
		*u = *p ^ c; u++; p++;
	}
	int sum = 0;
	for (int i = 0; i < edata_size; i++)
	{
	    fprintf(f, "%c", udata[i]);
	    sum += udata[i];
	}
	printf("File: %s   Sum: %d\n", fn, sum);
	fclose(f);
}


int main()
{
	efile("p059_cipher.txt");
//
// Note - created files for each possible combination (26*26*26 files), then
// searched for common english words - like "the", etc.
// turns out "exp" is the cipher
// running just that one	
//	for (char a = 'a'; a <= 'z'; a++)
//	for (char b = 'a'; b <= 'z'; b++)
//	for (char c = 'a'; c <= 'z'; c++)
//	decipher(a,b,c);
	decipher('e', 'x', 'p');
	
}

