#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

 
#define PORT 5457
 int compare(const void *a, const void *b) {
    int diff = *(int *)a - *(int *)b;
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

main()
{
	int size;
	int sock1,sock2, clength;
	sock1 =  socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serv,cli;
 
	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sock1,(struct sockaddr *)&serv, sizeof(serv));
	listen(sock1,5);
	clength = sizeof(cli);
	int i=0;
        while(1){
	sock2 = accept(sock1,(struct sockaddr *)&cli, (socklen_t *)&clength);
        cout << "\n CLIENT CONNECTED" << endl;
	//printf("\n Client Connected\n");
        read(sock2, &size, 4);
	int buf[size];
	//printf("%d\n", size);
	read(sock2,buf,size * 4);
	for(int i = 0; i < size; i++){
	//printf("%d ", buf[i]);
	}	
	qsort(buf, size, sizeof(int), compare);
        //cout << "\n DISPLAY : " << buf << endl;
        //printf("Display: %s",buf);
	write(sock2,buf,size * 4);
        cout << "\n testing" << endl;
       //printf ("testing");
	return 0;
}
}
 
