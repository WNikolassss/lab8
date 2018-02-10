#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <progbase/net.h>
#include <matan.h>
#include <list.h>
#include <request.h>

#include "fileWork.h"
#include "request.h"
#include "matan.h"

#define BUFFER_LEN 10240

char * readAllText1(const char * fileName);

int main(int argc, char * argv[]) {
	const int port = 9999;

    List * mat = List_new();

    matan  matan1;
    strcpy(matan1.name , "integral");
    matan1.id = 0;

    matan matan2;
    strcpy(matan2.name , "deff");
    matan2.id = 1;

    matan matan3;
    strcpy(matan3.name , "range");
    matan3.id = 2;

    List_add(mat , &matan1);
    List_add(mat , &matan2);
    List_add(mat , &matan3);

	TcpListener * server = TcpListener_init(&(TcpListener){});
    IpAddress * address = IpAddress_initAny(&(IpAddress){}, port);
    if(!TcpListener_bind(server, address)) {
        perror("tcp bind");
        return 1;
    }
    if (!TcpListener_start(server)) {
        perror("tcp server start");
        return 1;
    }
    printf("TCP Server is listening on port %d\n", 
        IpAddress_port(TcpListener_address(server)));
    
    NetMessage * message = NetMessage_init(
        &(NetMessage){},  // value on stack
        (char[BUFFER_LEN]){},  // array on stack 
        BUFFER_LEN);
	//
    // to store information about current client
    TcpClient client;
    while (1) {
        puts(">> Waiting for connection...");
		//
        // wait for someone to connect to server
        TcpListener_accept(server, &client);
        // wait for data from client
        if(!TcpClient_receive(&client, message)) {
			perror("recv");
			return 1;
		}
        IpAddress * clientAddress = TcpClient_address(&client);

        printf(">> Received message from %s:%d (%d bytes): `%s`\n",
            IpAddress_address(clientAddress),  // client IP-address
            IpAddress_port(clientAddress),  // client port
            NetMessage_dataLength(message),
            NetMessage_data(message));

	    	Request req = parseRequest(NetMessage_data(message));
            printRequest(&req);

        if(strcmp(req.command , "GET") == 0){
            if(strcmp(req.data , "/favorites") == 0){
                NetMessage_setDataString(message, parseAllJson(mat));
            }else if(strstr(req.data , "/favorites?") != NULL){
                NetMessage_setDataString(message, parseMatanRequest(req.data , mat));
            }else if(strstr(req.data , "/favorites/") != NULL){
                NetMessage_setDataString(message, parseIdRequest(req.data , mat));
            }else if(strcmp(req.data , "/file") == 0){
                NetMessage_setDataString(message, file());
            }else if(strcmp(req.data , "/file/data") == 0){
                NetMessage_setDataString(message, fileData());
            }else if(strcmp(req.data , "/") == 0){
                NetMessage_setDataString(message, defaultResponse());
            }else if(strcmp(req.data , "test") == 0){
                NetMessage_setDataString(message, readAllText1("test.png"));
            }else {
                NetMessage_setDataString(message, "Incorrect command");
            }
        }

        // send data back
        if(!TcpClient_send(&client, message)) {
			perror("send");
			return 1;
		}
        printf(">> String sent to client:\r\n%s\r\n", NetMessage_data(message));
        // close tcp connection
        TcpClient_close(&client);
    }
    // close listener
    TcpListener_close(server);
	return 0;
}

char * readAllText1(const char * fileName){
    FILE *file = fopen(fileName, "rb");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL) return NULL; //could not open file
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);

    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }

    code[n] = '\0';

    return code;
}
