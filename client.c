#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <progbase/net.h>
#include <jansson.h>
#include <string.h>
#include "request.h"

#define BUFFER_LEN 10000

int main(void) {
    // initialize all data
    TcpClient * client = TcpClient_init(&(TcpClient){});
    IpAddress * serverAddress = IpAddress_init(
        &(IpAddress){},  // value on stack
        "127.0.0.1",  // server host IP-address (localhost)
        9999);  // server port

    NetMessage * message = NetMessage_init(
        &(NetMessage){},  // value on stack
        (char[BUFFER_LEN]){},  // array on stack 
        BUFFER_LEN); 
	
	if (!TcpClient_connect(client, serverAddress)) {
        perror("tcp connect");
        return 1;
	}

	char request[BUFFER_LEN] = "";
	fgets(request, BUFFER_LEN, stdin);
	request[strlen(request)-1] = '\0';
	char * temp1 = malloc(sizeof(char*));
	strcpy(temp1,request);
	parseHttpRequest(request);
	NetMessage_setDataString(message, request);

	//
	// send string to server
	printf("Send string `%s` to server %s:%d\n",
		NetMessage_data(message), 
		IpAddress_address(serverAddress),
		IpAddress_port(serverAddress));
	if(!TcpClient_send(client, message)) {
		perror("send");
		return 1;
	}

	while (1) {
	if(!TcpClient_receive(client, message)) {
		perror("recv");
		return 1;
	}
	if (NetMessage_dataLength(message) == 0) {
         // no more data to receive from server
        break;
	}
	printf("Response received from server (%d bytes): %s\r\n", 
		NetMessage_dataLength(message),
		NetMessage_data(message));

		puts(temp1);
		if(strcmp(temp1,"test") == 0){
			FILE *f;
			f = fopen("test1.png", "wb");

			fprintf(f, "%s",NetMessage_data(message));
			fclose(f);
		}

}
//
// close client object
TcpClient_close(client);
printf("\n");
return 0;
}
