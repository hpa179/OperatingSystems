#include <stdlib.h>
#include <cstdlib>
//#include <glut.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
 
using namespace std;

#define PORT 5457
#define MAX_NUMBERS 10
 
struct input_data{
	int number[MAX_NUMBERS];
		int length;
};
int main (int argc, char *argv[])
{
	int size= argc - 1;
	int sock1;
	sock1 =  socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serv;
	serv.sin_port = htons(PORT);
        cout << "PORT" << PORT << "   " << htons(PORT) << endl;
	//printf("%x %x\n",PORT,htons(PORT));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
        cout << "CLIENT CONNECTING" << endl;
	//printf("client connecting\n");
	connect(sock1, (struct sockaddr *)&serv,sizeof(serv));
	int buf[size];
	write( sock1, &size, 4);
	for(int i = 1; i < argc; i++){
	buf[i - 1] = atoi(argv[i]); 
	}
        write (sock1,buf,size * 4);
	int arr[size];
	read(sock1, arr, size * 4);
	for(int i = 0; i < size; i++){
	printf("%d ", arr[i]);
	}
	close(sock1);
	return 0;
	}
/*	FILE* fp = fopen(buf,"w");
	while(1){
		//bzero(buf,sizeof(buf));
		read(sock1,buf,50);
		if(strcmp(buf,"cmsc312")==0)
		{
			break;	
		}
		fprintf(fp,"%s",buf);
	}
	fclose(fp); */
