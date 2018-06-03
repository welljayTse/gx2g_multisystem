#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "gx4g.h"



struct_temp_global 	mytempglobal;

gxgk_stru_share *psh;


INT8U bmu_cell_cnt[BMU_CELL_CNT]={0};

INT16U bmu_cell_num_start[BMU_CELL_CNT]={0};

INT16U cell_cnt_per_bmu[BMU_CELL_CNT]={0};


void gxgk_share_params_init()
{

	memset(psh, 0, sizeof(gxgk_stru_share));
	psh->uartnum = 2;     
        psh->sd = 0;	
	psh->count = 0;
	psh->pid_can_recv = 0;
	psh->pid_gpsinfo_get = 0;
	psh->pid_server_recv = 0;
	psh->pid_data_send = 0;
        psh->pid_time_count = 0;
	psh->pid_ping_connect = 0;

	psh->status_machine = GX4G_SM_MAIN;

       	extrm_info gs_extrminfo_recv = {
		0x0C,0X80,        //batterytv[2]; 		
	        0x0C,0x80,        //current[2];		      
	        0x00,0x60,        //soc[2];		 	
	        0x0c,0xbd,        //maxcellvolt[2];	        
	        0x0c,0xb0,        //mincellvolt[2] ;	
	        0x01,0x0a,        //maxcellvoltno[2];       
	        0x02,0x14,        //mincellvoltno[2] ;    
	        0x0c,0xb6,        //averagecellvoltage[2];
	        0,0x0d,           //vtgsub[2];
	        0x41,             //maxtempera;		
		0x41,             //mintempera;		
		0x09,             //maxtemperano;           
	        0x12,             //mintemperano;
	        0x41,             //averagetemp;		
	        0,                //tempsub;		
                0,0,0,0,0,0,0,0,  //alarminfo[8];	
                12,5,12,1,55,50,  //time[6];		
                38                //len;		
		};
	memcpy(&psh->gs_extrminfo_recv,&gs_extrminfo_recv, sizeof(extrm_info));

        extrm_info gs_extrminfo_send = {
		0x0C,0X80,        //batterytv[2]; 		
	        0x0C,0x80,        //current[2];		      
	        0x00,0x60,        //soc[2];		 	
	        0x01,0x0a,        //maxcellvoltno[2];       
	       	0x0c,0xbd,        //maxcellvolt[2];	        
	        0x02,0x14,        //mincellvoltno[2] ;    
	       	0x0c,0xb0,        //mincellvolt[2] ;	
	        0x0c,0xb6,        //averagecellvoltage[2];
	        0,0x0d,           //vtgsub[2];
	        0x41,             //maxtempera;		
		0x41,             //mintempera;		
		0x09,             //maxtemperano;           
	        0x12,             //mintemperano;
	        0x41,             //averagetemp;		
	        0,                //tempsub;		
                0,0,0,0,0,0,0,0,  //alarminfo[8];	
                12,5,12,1,55,50,  //time[6];		
                38                //len;		
	};                     
	memcpy(&psh->gs_extrminfo_send, &gs_extrminfo_send, sizeof(extrm_info));

	gps_info gs_gpsinfo_recv = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	memcpy (&psh->gs_gpsinfo_recv,&gs_gpsinfo_recv,sizeof(gps_info));

	gps_info gs_gpsinfo_send = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	memcpy (&psh->gs_gpsinfo_send,&gs_gpsinfo_send,sizeof(gps_info));

	car_info gs_carinfo_recv = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	memcpy (&psh->gs_carinfo_recv,&gs_carinfo_recv,sizeof(car_info));

	car_info gs_carinfo_send = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	memcpy (&psh->gs_carinfo_send,&gs_carinfo_send,sizeof(car_info));

	cell_info gs_cellinfo_recv = {0x0f000000,0xffffffff,0xffff7f00,0xffffffff,0xff000000,0,0,0,0,0,0,0,0,0,0,0,0,
	                              0x5f00,0x5f00};
	memcpy(&psh->gs_cellinfo_recv,&gs_cellinfo_recv, sizeof(cell_info));

	cell_info gs_cellinfo_send = {0x0f000000,0xffffffff,0xffff7f00,0xffffffff,0xff000000,0,0,0,0,0,0,0,0,0,0,0,0,
	                              0x5f00,0x5f00};
	memcpy(&psh->gs_cellinfo_send,&gs_cellinfo_send, sizeof(cell_info));

	gov_info gs_govinfo_recv = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	memcpy (&psh->gs_govinfo_recv,&gs_govinfo_recv,sizeof(gov_info));

	gov_info gs_govinfo_send = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	memcpy (&psh->gs_govinfo_send,&gs_govinfo_send,sizeof(gov_info));




	remotecfg_info  gs_remotecfg_send    = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};//for test
	remotecfg_info  gs_remotecfg_sendall = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};//for test
	
	memcpy(&psh->gs_remotecfg_send,&gs_remotecfg_send, sizeof(remotecfg_info));
	memcpy(&psh->gs_remotecfg_sendall,&gs_remotecfg_sendall, sizeof(remotecfg_info));


	memset (psh->string,0,256);
	memset (psh->gs_transferbuf,0,512);
	memset (psh->gs_recvbuf,0,512);

        
	psh->sockfd =0;
        bzero(&psh->addr_remote, sizeof(psh->addr_remote));              	
        bzero(&psh->peer, sizeof(psh->peer));              	
	psh->addrlen =0;

	psh->recv_flag = 0;
	psh->wait_flag = 0;
	
        psh->gs_bwtaddr[0]=0;
        psh->gs_bwtaddr[1]=0;
        psh->gs_bwtaddr[2]=0;

	psh->gps_recv_flag =0;
	psh->gps_fd =0;
        psh->bmucnt =0;
        psh->totalcellcnt =0;
	memset (psh->cellcntperbmu,0,12);

	psh->extrminfo_send_flag = 0;
	psh->carinfo_send_flag  = 0;
	psh->cellinfo_send_flag = 0;
	psh->gpsinfo_send_flag  = 0;
	psh->govinfo_send_flag  = 0;
}


void caninit()
{
	unsigned char cmd[128];
	int ret = 0;

	bzero(cmd, 128);
	sprintf(cmd, "%s", "/opt/shell_all_4g.sh caninit");
	ret = system(cmd);
}

void longsunginit(void)
{
	unsigned char cmd[256];

	bzero(cmd, 256);
	sprintf(cmd, "%s", "/opt/shell_all_4g.sh 4ginit");
	system(cmd);
	sleep (30);
}

void pppdial(void)
{
	unsigned char cmd[256];

	bzero(cmd, 256);
	sprintf(cmd, "%s", "/opt/shell_all_4g.sh 4gdial ");
	system(cmd);
	sleep(30);
}

void netroute(void)
{
	unsigned char cmd[256];

	bzero(cmd, 256);
        sprintf(cmd, "%s", "/opt/shell_all_4g.sh 4groute");
	system(cmd);
	sleep(5);
}

void gps_init()
{
        unsigned char cmd[256];

	bzero(cmd, 256);
	sprintf(cmd, "%s", "/opt/shell_all_4g.sh gpsinit");
	system(cmd);
	usleep (100*1000);

	psh->gps_fd = open ("/dev/ttyUSB3",O_RDWR);
	printf("nnnnnnnnnnnnnnnnnnnpsh->gps_fd=%d\n",psh->gps_fd);
}

int ping()
{
	char   psBuffer[512];
	FILE   *pPipe;
	int ret = 0;

	if( (pPipe = popen( "ping " TARGET, "r" )) == NULL )
	exit( -1);

	while(fgets(psBuffer, 512, pPipe)){

		printf("%s", psBuffer);
		ret = 1;
		break;
	}
	pclose(pPipe);
	return ret;
}

void gxgk_init()
{
        //int s,extrminfo_send_flag,carinfo_send_flag,cellinfo_send_flag,gpsinfo_send_flag,govinfo_send_flag;
	
	psh = mmap(NULL, sizeof(gxgk_stru_share), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
         
	if (psh == MAP_FAILED) {
		fprintf(stderr, "gxgk_init: mmap error about psh\n");
		return;
	}
	
#if 1
       caninit();
       longsunginit();
       pppdial();
       netroute();  
#endif

//	gxgk_read_params();
//	gxgk_save_params();
//
	gxgk_share_params_init();
	
        gps_init();
	//tcpinit();
	udpinit();
        socketcan_init();

        can_up_config();

	/*
	 *2016-11-11
	 *add serial fuc.
	*/
	 mytempglobal.uartnum = gxgk_open_serial(GXGK_UART_NAME);		  
	 printf("mytempglobal.uartnum = %d\n",mytempglobal.uartnum );
	 printf("can fd = %d\n",psh->can_fd );
	 
	ubxconfig(mytempglobal.uartnum);



   	psh->pid_ping_connect = fork();
	if (psh->pid_ping_connect< 0) {
        	fprintf(stderr, "ping error: create child process error\n");
         	return;
	}
        else if (psh->pid_ping_connect == 0) {
		int cnt = 0;
		while (1){
		     if(ping() == 1){
			     sleep (60);
			     continue;
		     }
		     sleep(1);
		     netroute();  
		}
	}


   	psh->pid_time_count = fork();
	if (psh->pid_time_count < 0) {
        	fprintf(stderr, "time_count: create child process error\n");
         	return;
	}
        else if (psh->pid_time_count == 0) {
		while (1){
			usleep(20000);
			if(psh->can_time_count++ > 60000) {
				psh->can_time_count = 0;
			}
		}	
	}

	psh->pid_gpsinfo_get = fork();
	if (psh->pid_gpsinfo_get < 0) {
        	fprintf(stderr, "gpsinfo_get: create child process error\n");
         	return;
	}
        else if (psh->pid_gpsinfo_get == 0) {
		int i = 0,ret=0;
		char buf[100];
		char tmp;

		for(i = 0; i < 100; i++)
		{
			buf[i] = i;
		}
		while (1){
			//usleep(100*1000);
			printf("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\n");
			printf("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\n");
			printf("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\n");
			printf("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\n");
			printf("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\n");
			printf("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\n");

			usleep(1000);
                        //gxgk_write_serial(mytempglobal.uartnum,psh->gs_transferbuf,16);

			// printf("mytempglobal.uartnum = %d\n",mytempglobal.uartnum );
                        //gxgk_read_serial(mytempglobal.uartnum,psh->gs_transferbuf,100);
			//read (mytempglobal.uartnum,buf,100);	
			//for(i = 0; i < 100; i++)
			//{
			//printf("%c",buf[i]);
			//printf("buf[%d]=%c\n",i,buf[i]);
			//}
			gpsinfoget(mytempglobal.uartnum);
			printf("mytempglobal.uartnum=%d\n",mytempglobal.uartnum);
			//gpsinfoget(mytempglobal.uartnum);
		//	for(i = 0; i < 100; i++)
		//	{
		//		tmp = uart_get_byte(mytempglobal.uartnum);

		//		printf("tmp=%c\n",tmp);
		//
		//	}
		}	
	}

	/* creat process to recv can data*/
        psh->pid_can_recv = fork();

       	if (psh->pid_can_recv < 0) {
        	fprintf(stderr, "can_recv: create child process error\n");
         	return;
	}
        else if (psh->pid_can_recv == 0) {
		/* timer signal per second */
		//alarmtimer(1);
		//signal(SIGALRM, sig_handle_timer);
		
		while (1) 
		{
	       		//printf ("psh->sd=%d,m=%d",psh->sd,m);
			can_read(psh->can_fd);
			//memcpy(psh->string,(unsigned ehar *)(&gs_extrminfo_recv),psh->data);
		}
	}

	/* creat process to send data to sever */
	psh->pid_data_send = fork();

  	if (psh->pid_data_send  < 0){
		fprintf(stderr, "data_send: create child process error\n");
		return;
  	}
  	else if (psh->pid_data_send  == 0) {
  	       	
	//	can_config(psh->can_fd,(unsigned char *)(&psh->gs_transferbuf));

		while (1) {
			sleep(1);
			psh->extrminfo_send_flag++;
			psh->carinfo_send_flag++;
			psh->cellinfo_send_flag++;
			psh->gpsinfo_send_flag++;
			psh->govinfo_send_flag++;
                        
			if(psh->extrminfo_send_flag >= 10){
				transfercontrl((unsigned char *)(&psh->gs_extrminfo_send),(unsigned char *)(&psh->gs_transferbuf),0xb110,38);
				udpsend(psh->gs_transferbuf,54);
				usleep(10000);
				psh->extrminfo_send_flag = 0;
			}
			if(psh->carinfo_send_flag >= 10){
				transfercontrl((unsigned char *)(&psh->gs_carinfo_send),(unsigned char *)(&psh->gs_transferbuf),0xb111,34);
				udpsend(psh->gs_transferbuf,50);
				usleep(10000);
				psh->carinfo_send_flag = 0;
			}
                        if(psh->gpsinfo_send_flag >= 15){
                               if(psh->gps_recv_flag == 1){
				       transfercontrl((unsigned char *)(&psh->gs_gpsinfo_send),(unsigned char *)(&psh->gs_transferbuf),0xb112,18);
				       udpsend(psh->gs_transferbuf,34);
				       psh->gps_recv_flag = 0;
				       usleep(10000);
			       }
			       psh->gpsinfo_send_flag = 0;
		       }
			if(psh->cellinfo_send_flag >= 600){
				transfercontrl((unsigned char *)(&psh->gs_cellinfo_send),(unsigned char *)(&psh->gs_transferbuf),0xb113,psh->totalcellcnt*3+86);
				udpsend(psh->gs_transferbuf,psh->totalcellcnt*3+102);
			        usleep(10000);
				psh->cellinfo_send_flag = 0;
			}
			if(psh->govinfo_send_flag >= 3){
				transfercontrl((unsigned char *)(&psh->gs_govinfo_send),(unsigned char *)(&psh->gs_transferbuf),0xb114,33);
				udpsend(psh->gs_transferbuf,49);
			        usleep(10000);
				psh->govinfo_send_flag = 0;
			}

			//usleep(50);
		//	usleep(500000);
		        printf ("psh->gs_remotecfg_recvflag =%d\n",psh->gs_remotecfg_recvflag);
			if (psh->gs_remotecfg_recvflag == 1){
				psh->gs_remotecfg_recvflag = 0;
				transfercontrl((unsigned char *)(&psh->gs_remotecfg_sendall),(unsigned char *)(&psh->gs_transferbuf),0xb114,49);
				udpsend(psh->gs_transferbuf,65);
			}
			
			if (psh->gs_remotecfg_recvflag == 2){
				psh->gs_remotecfg_recvflag = 0;
				transfercontrl((unsigned char *)(&psh->gs_recvbuf),(unsigned char *)(&psh->gs_transferbuf),0xb115,49);
				udpsend(psh->gs_transferbuf,65);
			}
		}
  	}

	/* creat process to recv data from sever */
	psh->pid_server_recv = fork();

  	if (psh->pid_server_recv < 0){

		fprintf(stderr, "server_recv: create child process error\n");
		return;
  	}
  	else if (psh->pid_server_recv == 0) {
  	       	
		while (1) {
			printf("1111111111111111111111\n");
			usleep(1000);	
	        //	udprecv_test(psh->gs_recvbuf,psh->can_fd);
//			memset (psh->gs_recvbuf,0,512);
	        	udprecv(psh->gs_recvbuf,psh->can_fd);
			//	printf("ddddddddddddddddddddddd");
			//	transfercontrl((unsigned char *)(&psh->gs_remotecfg_sendall),(unsigned char *)(&psh->gs_transferbuf),0xb210,48);
			//	udpsend(psh->gs_transferbuf,60);
		}
	}

	close (psh->can_fd);
}

void gxgk_free()
{
	/* kill process to get system stat */
	kill(psh->pid_time_count, SIGKILL);
	kill(psh->pid_gpsinfo_get, SIGKILL);
	kill(psh->pid_can_recv, SIGKILL);
	kill(psh->pid_data_send, SIGKILL);
	kill(psh->pid_server_recv, SIGKILL);

        /* free global share memory */
	munmap(psh, sizeof(gxgk_stru_share));
}

void main(int argc, char ** argv[]) 

{
	int status_machine = GX4G_SM_MAIN ;
	

	while(1){
		switch(status_machine){
			case GX4G_SM_MAIN: gxgk_init();
                                           usleep(500000);
                                           status_machine = GX4G_SM_RUN;
		                           break;
			case GX4G_SM_RUN:  usleep(500000);
			                   printf("flying!!!!!!!\n");
			                   break;
			case GX4G_SM_CONFIGURE:	
					   usleep(500000);

				           status_machine = GX4G_SM_MAIN;
				           break;

                        default:	   usleep(500000);
		                           break;
		}

	   //     gxgk_free();
		}

}
