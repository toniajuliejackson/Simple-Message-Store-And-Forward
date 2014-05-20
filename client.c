/* toniajacksonclient.c - main, client 
*  Tonia Jackson
*  C11424448
*  DT211/3
*/
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

extern int errno;

#define LINELEN 128
/*------------------------------------------------------------------------
* TCPChat Client - Get message from service and send a new message
*------------------------------------------------------------------------
*/
int main( argc, argv )
int argc;
char *argv[];
{
    char *host;                             	/* will hold the host name */
    char *service;                          	/* will hold the port number */
    char buf[ LINELEN+1 ];                  	/* buffer for one line of text */
    char bufin [ LINELEN+1 ];               	/* buffer for reading line of text */
    int s, n;                               	/* socket descriptor, read count */
    int outchars= LINELEN, inchars = LINELEN;	/* max characters sent */
	char msg[LINELEN] = "No message stored";
    if (argc != 3 ) {
        fprintf( stderr, "usage: tcpechoc host port \n" );
        exit( 1 );
    }
    else
        host = argv[1];
        service = argv[2];

      	/* connectsock creates and connects a socket to specified host & port no. */
        s = connectsock ( host, service );

		/* read in the buffer and display the message to the client */
        if (read(s, bufin, inchars)){
            printf("Message saved on server _ ");
            fputs( bufin, stdout );
        }

		/* requests user to enter a new message, reads message in */
        printf("\nEnter a new message _ ");
        if(fgets( buf, sizeof( buf ), stdin ) != 0){
                outchars = strlen(buf);
                buf[outchars-1 ] = '\0';            /* ensure line null terminated */
                
                /* place socket write statement here to write data from buf */
                write(s, buf, outchars);
                
                /* closes connection */ 
                close();
        }
}

/*------------------------------------------------------------------------
* connectsock - allocate & connect a socket using TCP
*------------------------------------------------------------------------
*/
int connectsock(
char *host,                     /* name of host to which connection is desired */
char *service                   /* port number as a character string */
) {
struct hostent *phe;            /* pointer to data structure containing IP address as 4-byte integer*/
struct sockaddr_in sin;         /* will hold a full Internet endpoint address*/
/* full address comprises address family, port number and IP address */
int s ;                         /* socket descriptor */
bzero((char *)&sin, sizeof( sin )); /* initialise sin with zeros */
sin.sin_family = AF_INET; /* place address family in sin.sin_family */

/* function atoi converts port number from character string to integer*/
/* htons converts from host to network byte order*/
/* place resultant port number into sin.sin_port */
if ( ( sin.sin_port = htons( (ushort)atoi( service ) ) ) == 0 )
{
fprintf( stderr, "can't get \"%s\" service entry\n", service );
exit( 1 );
}

/* gethostbyname converts host name to 4-byte IP address and places it in phe->h_addr */
/* bcopy copies 4-byte host IP address into sin.sin_addr */
if ((phe = gethostbyname(host)))
bcopy( phe->h_addr, &sin.sin_addr,4 );
else
{
fprintf( stderr, "can't get \"%s\" host entry\n", host );
exit( 1 );
}

/* Create a socket with the socket function call */
/* TCP/IP sockets can be type SOCK_STREAM (TCP) SOCK_DGRAM (UDP) */
/* SOCK_STREAM is a symbolic constant = 1 */
/* AF_INET is a symbolic constant = 2 indicating address family TCP/IP */
/* Put socket function call in here. Let s = socket descriptor */

s = socket(AF_INET, SOCK_STREAM, 0);

if ( s < 0 )
{
fprintf( stderr, "can't create socket: %s\n", strerror( errno ) );
exit( 1 );
}
/* Connect the socket */
/* put connect function call in here to connect to server , enclose it in an if statement so that if */
/* the connect call returns a value of -1 then the error handling code immediately following is executed */

if ( connect (s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
{
fprintf( stderr, "can't connect to %s.%s: %s\n", host, service,
strerror( errno ) );
exit( 1 );
}

return s;
}
