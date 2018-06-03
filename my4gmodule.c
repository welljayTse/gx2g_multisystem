#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

#include "mysocketcan.h"
#include "my4gmodule.h"

#define LENGTH 	 800 

//#define PORT     10010 
//#define IP       "220.180.240.174"     // gotionsever for test

//#define PORT     33333 
//#define IP       "120.193.108.138"   // baiyiserver for client

#define PORT     15500             // twtrserver for client
//#define PORT     15501              // twtrserver for test
#define IP       "211.22.205.163"   // twtrserver for client


char     revstr[];            		                 	// Receive buffer for byte2hexstr

static void dealSigAlarm(int signo)
 {
	int n;
        n = -1;
        return;   /* just interrupt the recvfrom() */
 }

unsigned char chksumgen (const unsigned char *source, unsigned int len)
{
	unsigned int i;
	unsigned char chksum =0;

	for (i = 0; i < len; i++) {
		chksum = source[i] ^ chksum;
	}

	chksum = (chksum + 1) % 0x100;

	if ((chksum == 0x00)|(chksum == 0x7e)|(chksum == 0x08)|(chksum == 0x0a)|(chksum == 0x0d)|(chksum == 0x22)) {
		chksum = chksum + 0x30;
	}

	return chksum;
}


void transfercontrl(unsigned char *data, unsigned char *frame, unsigned short cid, unsigned short len)
{
	unsigned int i = 0;
//	psh->gs_bwtaddr[0] = 0x1020304;
 
//	psh->gs_bwtaddr[2] = 0x5060708;

	*frame = 0x7e;
	if (psh->g_ucBWTVersion == 0x91){

		*(frame+1) = psh->g_ucBWTVersion;

		for(i = 0; i < 8; i++ ){
			
			*(frame+2+i) = psh->gs_bwtaddr[i];
		}

		*(frame+10) = (unsigned char)(cid >> 8);
		*(frame+11) = (unsigned char)cid;

		*(frame+12) = (unsigned char)(len >> 8);
		*(frame+13)= (unsigned char)len;
		
		for (i = 0; i < len; i++){
		
			*(frame+14+i) = *(data+i);
		}
		
		*(frame+14+len) = chksumgen(frame+1,len+10);
		*(frame+15+len) = 0x0d;
	}
	else if (psh->g_ucBWTVersion == 0x90){

		*(frame+1) = psh->g_ucBWTVersion;

		for(i = 0; i < 4; i++ ){
			
			*(frame+2+i) = psh->gs_bwtaddr[i];
		}

		*(frame+6) = (unsigned char)(cid >> 8);
		*(frame+7) = (unsigned char)cid;

		*(frame+8) = (unsigned char)(len >> 8);
		*(frame+9)= (unsigned char)len;
		
		for (i = 0; i < len; i++){
		
			*(frame+10+i) = *(data+i);
		}
		
		*(frame+10+len) = chksumgen(frame+1,len+10);
		*(frame+11+len) = 0x0d;
	}

       printf("transfercontrl is ready!!!!!\n");

}

void tcpinit()
{

	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	sleep(1);
/* Get the Socket file descriptor */
	if ((psh->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		printf("ERROR: Failed to obtain Socket Descriptor!\n");
		return (0);
	}

printf("llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n");
printf("llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n");
printf("llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n");
printf("llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n");
printf("llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n");
printf("llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n");
printf("llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n");
printf("llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n");
printf("llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n");
printf("llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n");
        bzero(&psh->addr_remote, sizeof(psh->addr_remote));              	// Flush the rest of struct
        psh->addr_remote.sin_family = AF_INET;                  	// Protocol Family
        psh->addr_remote.sin_port = htons(PORT);           		// Port number
       // addr_remote.sin_addr = *((struct in_addr *)host->h_addr);
        psh->addr_remote.sin_addr.s_addr = inet_addr(IP);

        psh->addrlen = sizeof(psh->addr_remote);
       // printf ("udpinit sockfd=%d\n",psh->sockfd);

	if (connect(psh->sockfd, (struct sockaddr *)(&psh->addr_remote), sizeof(struct sockaddr)) == -1) {
        	printf ("ERROR: Failed to connect to the host!\n");
        	return (0);
    	}
       	else {
        	printf ("OK: Have connected to the Port %d!\n",PORT);
    	}
       sleep(1);
}


void udpinit()
{
/* Get the Socket file descriptor */
	if ((psh->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		printf("ERROR: Failed to obtain Socket Descriptor!\n");
		return (0);
	}


        bzero(&psh->addr_remote, sizeof(psh->addr_remote));              	// Flush the rest of struct
        psh->addr_remote.sin_family = AF_INET;                  	// Protocol Family
        psh->addr_remote.sin_port = htons(PORT);           		// Port number
       // addr_remote.sin_addr = *((struct in_addr *)host->h_addr);
        psh->addr_remote.sin_addr.s_addr = inet_addr(IP);

        psh->addrlen = sizeof(psh->addr_remote);
       // printf ("udpinit sockfd=%d\n",psh->sockfd);
}


int udpsend(unsigned char sdbuf[],unsigned int len)
{
    	int      num;                       			// Counter of received bytes

   	num = sendto(psh->sockfd, sdbuf, len, 0, (struct sockaddr *)&psh->addr_remote,psh->addrlen);
        if (num < 0){
		printf ("Error: Failed to send data!\n");
		printf ("udpclient sockfd=%d \n",psh->sockfd);
	}

        else printf("OK:sent to %s total %d bytes! ",sdbuf, num);
}

int udprecv_test(unsigned char revbuf[],unsigned int fd)

{
    	int      num,i,count,ret;                       			// Counter of received bytes
	char     temp[3];
	int      canfd;
	int      exin;
        memset (revbuf,0,512); 
	printf("&&&*****************************************\n");
	num = recvfrom(psh->sockfd, revbuf,256, 0,(struct sockaddr *)&psh->peer,&psh->addrlen);

	printf("###*****************************************\n");
        if (num < 0){ 
		printf("recvfrom() error\n");
	}

        else {
		for(i = 0; i < num; i++){
			sprintf(temp,"%02X",(unsigned char)revbuf[i]);
			memcpy (&revstr[i*2],temp,2);
		}
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!num is %d,Server Message:%s\n",num,revstr);
		if (revbuf[6]==0xb2 && revbuf[7]==0x10){
			for (count = 0;count < 10; count++ ){
				ret = pack_send_test(INF1, fd);
				if(ret > 0){
					printf("handshake success!!!\n");
					if (pack_send_retry_test(INF13,fd) < 0){
					       continue; 
					}	       

					break;
				}
			//can_config(psh->can_fd,(unsigned char *)(&psh->gs_transferbuf));
				else usleep(50000);
			       	}
			}	

		if (revbuf[6]==0xb2 && revbuf[7]==0x11){

			psh->gs_remotecfg_recvflag = 2;
			can_remote_config_test(psh->can_fd);
			
			printf("#######################################################################handshake success!!!\n");
/*
			for (count = 0;count < 10; count++ ){
				ret = pack_send(INF1, fd,revbuf);
				printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ret= %d\n",ret);
				if(ret > 0){
					exin = pack_send_retry(INF3,fd);

					printf("#######################################################################handshake success!!!\n");
					printf("pack_send_retry(INF3,fd) = %d \n",exin);
					if (exin < 0){
					       continue; 
					}
				      	can_config(psh->can_fd);
					break;
				}
				else usleep(50000);
			       	}
*/
	           //     sleep(1);

		//	pack_send(INF1, fd);
		//	printf ("psh->can_fd=%d\n",psh->can_fd);
		//	can_config(psh->can_fd);
		}
		
	}
      return 1; 
}

int udprecv(unsigned char revbuf[],unsigned int fd)

{
    	int      num,i,count,ret;                       			// Counter of received bytes
	char     temp[3];
	int      canfd;
	int      exin;
        memset (revbuf,0,512); 
	printf("&&&*****************************************\n");
	num = recvfrom(psh->sockfd, revbuf,256, 0,(struct sockaddr *)&psh->peer,&psh->addrlen);

	printf("###*****************************************\n");
        if (num < 0){ 
		printf("recvfrom() error\n");
	}

        else {
		for(i = 0; i < num; i++){
			sprintf(temp,"%02X",(unsigned char)revbuf[i]);
			memcpy (&revstr[i*2],temp,2);
		}
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!num is %d,Server Message:%s\n",num,revstr);
		if (revbuf[10]==0xb2 && revbuf[11]==0x10){
			for (count = 0;count < 10; count++ ){
				ret = pack_send(INF1, fd,(unsigned char *)(&revbuf));
				if(ret > 0){
					printf("handshake success!!!\n");
					if (pack_send_retry(INF13,fd,(unsigned char *)(&revbuf)) < 0){
					       continue; 
					}	       

					break;
				}
			//can_config(psh->can_fd,(unsigned char *)(&psh->gs_transferbuf));
				else usleep(50000);
			       	}
			}	

		if (revbuf[10]==0xb2 && revbuf[11]==0x11){

			psh->gs_remotecfg_recvflag = 2;
			can_remote_config(psh->can_fd,revbuf);
			
			printf("#######################################################################handshake success!!!\n");
/*
			for (count = 0;count < 10; count++ ){
				ret = pack_send(INF1, fd,revbuf);
				printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ret= %d\n",ret);
				if(ret > 0){
					exin = pack_send_retry(INF3,fd);

					printf("#######################################################################handshake success!!!\n");
					printf("pack_send_retry(INF3,fd) = %d \n",exin);
					if (exin < 0){
					       continue; 
					}
				      	can_config(psh->can_fd);
					break;
				}
				else usleep(50000);
			       	}
*/
	           //     sleep(1);

		//	pack_send(INF1, fd);
		//	printf ("psh->can_fd=%d\n",psh->can_fd);
		//	can_config(psh->can_fd);
		}
		
	}
      return 1; 
}
/*
int udprecv_test(unsigned char revbuf[],unsigned int fd)

{
    	int      num,i,count,ret;                       			// Counter of received bytes
	char     temp[3];
	int      canfd;
       // if(count == 5){			
		for (count = 0;count < 10; count++ ){
			ret = pack_send(INF1, fd);
			if(ret > 0){
				printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
				printf("handshake success!!!\n");
				if (pack_send_retry(INF13,fd) < 0){
					printf("bbbbbbbbbbbbbbbnbbbbbbbbbbb\n");
				       continue; 
				}	       
				printf("cccccccccccccccccccccccccccccccc\n");
				break;
			//	usleep(100);
			//	transfercontrl((unsigned char *)(&psh->gs_remotecfg_sendall),(unsigned char *)(&psh->gs_transferbuf),0xb210,48);
			//	udpsend(psh->gs_transferbuf,60);

		//can_config(psh->can_fd,(unsigned char *)(&psh->gs_transferbuf));
			}
			else usleep(50000);
		}
//	}	
//	count ++;
//	if (count > 5) count=0;
        return 1;
}
*/
