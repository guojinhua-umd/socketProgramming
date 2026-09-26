/*
 * multiThreadServer.c -- a multithreaded server
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>
#include <system_error>
#include <cstring>
#include <cstdlib>

using namespace std;

#define PORT 5432 // port we're listening on
#define MAX_LINE 256

fd_set master; // master file descriptor list
int listener;  // listening socket descriptor
int fdmax;
mutex masterMutex; // guards master/fdmax across threads

// the child thread
void ChildThread(long childSocket)
{
    char buf[MAX_LINE];
    int nbytes;
    int j;

    while (1)
    {
        // handle data from a client
        if ((nbytes = recv(childSocket, buf, sizeof(buf), 0)) <= 0)
        {
            // got error or connection closed by client
            if (nbytes == 0)
            {
                // connection closed
                cout << "multiThreadServer: socket " << childSocket << " hung up" << endl;
            }
            else
            {
                perror("recv");
            }
            close(childSocket); // bye!
            {
                lock_guard<mutex> lock(masterMutex);
                FD_CLR(childSocket, &master); // remove from master set
            }
            return;
        }
        else
        {
            // we got some data from a client
            cout << buf;

            // snapshot the shared state, then broadcast without holding the lock
            fd_set masterCopy;
            int fdmaxCopy;
            {
                lock_guard<mutex> lock(masterMutex);
                masterCopy = master;
                fdmaxCopy = fdmax;
            }
            for (j = 0; j <= fdmaxCopy; j++)
            {
                // send to everyone!
                if (FD_ISSET(j, &masterCopy))
                {
                    // except the listener and ourselves
                    if (j != listener && j != childSocket)
                    {
                        if (send(j, buf, nbytes, 0) == -1)
                        {
                            perror("send");
                        }
                    }
                }
            }
        }
    }
}

int main(void)
{
    struct sockaddr_in myaddr;     // server address
    struct sockaddr_in remoteaddr; // client address
    int newfd;                     // newly accept()ed socket descriptor
    int yes = 1;                   // for setsockopt() SO_REUSEADDR, below
    socklen_t addrlen;

    FD_ZERO(&master); // clear the master and temp sets

    // get the listener
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    // lose the pesky "address already in use" error message
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }

    // bind
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons(PORT);
    memset(&(myaddr.sin_zero), '\0', 8);
    if (bind(listener, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    // listen
    if (listen(listener, 10) == -1)
    {
        perror("listen");
        exit(1);
    }

    // add the listener to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one

    addrlen = sizeof(remoteaddr);

    // main loop
    for (;;)
    {
        // handle new connections
        if ((newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen)) == -1)
        {
            perror("accept");
            exit(1);
        }
        else
        {
            {
                lock_guard<mutex> lock(masterMutex);
                FD_SET(newfd, &master); // add to master set
                if (newfd > fdmax)
                { // keep track of the maximum
                    fdmax = newfd;
                }
            }
            cout << "multiThreadServer: new connection from "
                 << inet_ntoa(remoteaddr.sin_addr)
                 << " socket " << newfd << endl;

            try
            {
                thread cThread(ChildThread, (long)newfd);
                cThread.detach();
            }
            catch(const system_error &e)
            {
                cerr << "thread creation failed: " << e.what() << endl;
                exit(1);
            }
        }
    }
    return 0;
}
