/**
 * TCP client, this client connects to the server using the port 54000
 * allows the user to send a message so that the server can reverse the
 * string and then displays the response of the server
 */

#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>

int main() {

    //create a socket
    int clientsocket = socket(AF_INET, SOCK_STREAM, 0);

    if(clientsocket == -1){

        printf("%s", "can't create socket");
        return -1;

    }

    //create a hint structure for the server we are connecting with
    int port = 54000;
    std::string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //connect on the server on the socket
    int connectResult = connect(clientsocket, (sockaddr*)&hint, sizeof(hint));

    if(connectResult == -1){

        printf("%s", "problem with connection");
        return -2;

    }

    char buf[4096];
    std::string userInput;

    /**
     *do while loop allows the user to send and receive multiple strings
     *it's an infinite loop that only stops when the execution is stopped
     */

    do{

        printf("%s", ">");
        getline(std::cin, userInput);

        int sendResult = send(clientsocket, userInput.c_str(),userInput.size()+1, 0);

        if(sendResult == -1){

           printf("%s", "problem with result string");

        }

        memset(buf, 0,4096);
        int bytesReceived = recv(clientsocket, buf, 4096, 0);

        if(bytesReceived == -1){

            printf("%s", "problem with response");

        }else{

            printf("%s%s%s", "SERVER: ", std::string(buf, bytesReceived).c_str(), "\r\n");

        }

    }while(true);

    //close the socket
    close(clientsocket);

    return 0;
}