#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "gx4g.h"


unsigned char gs_gpsrecvbuf[100];
const unsigned char ubx_cmd01[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x05,0x01,0x00,0x01,0x01,0x01,0x01,0x09,0x56};//VTG
const unsigned char ubx_cmd02[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x00,0x01,0x00,0x01,0x01,0x01,0x01,0x04,0x33};//GGA
const unsigned char ubx_cmd03[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x02,0x01,0x00,0x01,0x01,0x01,0x01,0x06,0x41};//GSA
const unsigned char ubx_cmd04[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x03,0x01,0x00,0x01,0x01,0x01,0x01,0x07,0x48};//GSV
const unsigned char ubx_cmd05[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x01,0x01,0x00,0x01,0x01,0x01,0x01,0x05,0x3A};//GLL
const unsigned char ubx_cmd06[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x5B};//ZDA
const unsigned char ubx_cmd07[] = {0xB5,0x62,0x06,0x16,0x08,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x26,0x97};//DIS_SBAS
const unsigned char ubx_cmd08[] = {0xB5,0x62,0x06,0x24,0x24,0x00,0xFF,0xFF,0x04,0x03,0x00,0x00,0x00,0x00,0x10,0x27,
				   0x00,0x00,0x05,0x00,0xFA,0x00,0xFA,0x00,0x32,0x00,0x2C,0x01,0x64,0x00,0x00,0x00,
				   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46,0x8C};//CFG_NAV5

//const unsigned char ubx_cmd01[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x05,0x00,0x00,0x00,0x00,0x00,0x01,0x05,0x47};//VTG
//const unsigned char ubx_cmd02[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x24};//GGA
//const unsigned char ubx_cmd03[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x02,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x32};//GSA
//const unsigned char ubx_cmd04[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x03,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x39};//GSV
//const unsigned char ubx_cmd05[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x2b};//GLL
//const unsigned char ubx_cmd06[] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x5B};//ZDA
//const unsigned char ubx_cmd07[] = {0xB5,0x62,0x06,0x16,0x08,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x26,0x97};//DIS_SBAS
//const unsigned char ubx_cmd08[] = {0xB5,0x62,0x06,0x24,0x24,0x00,0xFF,0xFF,0x04,0x03,0x00,0x00,0x00,0x00,0x10,0x27,
//				   0x00,0x00,0x05,0x00,0xFA,0x00,0xFA,0x00,0x32,0x00,0x2C,0x01,0x64,0x00,0x00,0x00,
//				   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46,0x8C};//CFG_NAV5


void ubxconfig(int fd)
{
	sleep(1);
	//usleep(500*1000);
       	gxgk_write_serial(fd,ubx_cmd01,16);usleep(50*1000); 	
        gxgk_write_serial(fd,ubx_cmd02,16);usleep(50*1000);
        gxgk_write_serial(fd,ubx_cmd03,16);usleep(50*1000);
        gxgk_write_serial(fd,ubx_cmd04,16);usleep(50*1000);
        gxgk_write_serial(fd,ubx_cmd05,16);usleep(50*1000);
        gxgk_write_serial(fd,ubx_cmd06,16);usleep(50*1000);
        gxgk_write_serial(fd,ubx_cmd07,16);usleep(50*1000);
        gxgk_write_serial(fd,ubx_cmd08,44);usleep(50*1000);
        sleep(1);
//	gxgk_write_serial(fd,(unsigned char *)ubx_cmd01,16);usleep(100*1000); 	
//        gxgk_write_serial(fd,(unsigned char *)ubx_cmd02,16);usleep(100*1000);
//        gxgk_write_serial(fd,(unsigned char *)ubx_cmd03,16);usleep(100*1000);
//        gxgk_write_serial(fd,(unsigned char *)ubx_cmd04,16);usleep(100*1000);
//        gxgk_write_serial(fd,(unsigned char *)ubx_cmd05,16);usleep(100*1000);
//        gxgk_write_serial(fd,(unsigned char *)ubx_cmd06,16);usleep(100*1000);
//        gxgk_write_serial(fd,(unsigned char *)ubx_cmd07,16);usleep(100*1000);
//        gxgk_write_serial(fd,(unsigned char *)ubx_cmd08,44);usleep(100*1000);
}







void uartgetstr(int fd)
{
	unsigned char recvflag =0;
	unsigned char temp;
	int gpsrecvcnt = 0;

	while(!recvflag){
		temp = uart_get_byte(fd);

		if(temp == '$'){
			recvflag = 1;
		}
	}
	while(recvflag){
		temp = uart_get_byte(fd);
		if(temp != '*'){
			gs_gpsrecvbuf[gpsrecvcnt++] = temp;
		}
		else{
			gpsrecvcnt = 0;
			recvflag = 0;
			printf("..............................\n");
			printf("..............................\n");
			printf("..............................\n");
			printf("..............................\n");

			printf ("gs_gpsrecvbuf = %s\n",gs_gpsrecvbuf);
			break;
		}
	}
}


/*********************************************************************************************************
** Function name:       GpsInfoGet
** Descriptions:        获取GPS信息
** input parameters:    无
** output parameters:   获取完成返回 1   获取失败返回 0
** Returned value:      无
*********************************************************************************************************/
//          time    status  lat          	 log               spd     cog     date
//$ GPRMC , 083559.00 , A , 4717.11437 , N , 00833.91522 , E , 0.004 , 77.52 , 091202 ,,,A*57



unsigned char gpsinfoget(int fd)
{
	unsigned char i; 
	unsigned char *ptr;
	unsigned char *index;
	unsigned short temp;

	uartgetstr(fd);

	psh->gs_gpsinfo_recv.len = 18;
        
	printf ("/////////////fd=%d\n",fd);
      
//	char * gs_gpsrecvbuf = "$GPRMC,084100.0,A,3154.576498,N,11722.141770,E,0.0,,010616,0.0,E,A*27";
        
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
printf("//////////////////////////////////////////////////////////////////\n");
	printf ("gs_gpsrecvbuf = %s\n",gs_gpsrecvbuf);

//	ptr = (unsigned char *)strstr((unsigned char *)gs_gpsrecvbuf,(unsigned char *)"GPRMC");
	ptr = (unsigned char *)strstr((const char *)gs_gpsrecvbuf,(const char *)"GPRMC");
        
        printf ("\n ptr = %s\n",ptr);

	if(NULL == ptr)
	{
		return 0;
	}


//	for (i=0;i<68;i++){
//		printf("gps recv buf[%d] =%c \n",i,gs_gpsrecvbuf[i]);
//	}
//	printf("gs_gpsrecvbuf[ptr - gs_gpsrecvbuf + 16]=%c \n", gs_gpsrecvbuf[ptr - gs_gpsrecvbuf + 16]);

//	if(gs_gpsrecvbuf[ptr - gs_gpsrecvbuf + 16] == 'A')
//

	if(gs_gpsrecvbuf[16] == 'A'){

                printf("\n GPRMC get it \n ");

                psh->gs_gpsinfo_recv.len = 18; 

		// GPS 时间
		ptr = (unsigned char *)strstr((const char *)gs_gpsrecvbuf,",") + 1;
		psh->gs_gpsinfo_recv.time[3]   = (*ptr - '0') * 10 + (*(ptr+1) - '0') +8;	     // 时
		psh->gs_cellinfo_recv.time[3]  = psh->gs_gpsinfo_recv.time[3];	    				 // 时
		psh->gs_extrminfo_recv.time[3] = psh->gs_gpsinfo_recv.time[3];					 // 时
		psh->gs_govinfo_recv.time[3]   = psh->gs_gpsinfo_recv.time[3];					 // 时

		psh->gs_gpsinfo_recv.time[4]   = (*(ptr+2) - '0') * 10 + (*(ptr+3) - '0');  // 分
		psh->gs_cellinfo_recv.time[4]  = psh->gs_gpsinfo_recv.time[4];	    				 // 分
		psh->gs_extrminfo_recv.time[4] = psh->gs_gpsinfo_recv.time[4];
		psh->gs_govinfo_recv.time[4]   = psh->gs_gpsinfo_recv.time[4];

		// 分
		psh->gs_gpsinfo_recv.time[5]   = (*(ptr+4) - '0') * 10 + (*(ptr+5) - '0');  // 秒
		psh->gs_cellinfo_recv.time[5]  = psh->gs_gpsinfo_recv.time[5];	    				 // 秒
		psh->gs_extrminfo_recv.time[5] = psh->gs_gpsinfo_recv.time[5];						 // 秒
		psh->gs_govinfo_recv.time[5] = psh->gs_gpsinfo_recv.time[5];						 // 秒

		//g_ucGPSInfo[0] = 0;

		// GPS 纬度
		//          time    status  lat          	 log               spd     cog     date
		//$ GPRMC , 083559.00 , A , 4717.11437 , N , 00833.91522 , E , 0.004 , 77.52 , 091202 ,,,A*57
		ptr = (unsigned char *)strstr((const char *)ptr,",");
		ptr = (unsigned char *)strstr((const char *)(ptr+1),",") + 1;
		if(*(ptr+11) == 'S')
		{
			psh->gs_gpsinfo_recv.lat[0] = 0x01;
			//
			psh->gs_gpsinfo_recv.lat[0] = 0x01;
		}
		else
		{
			psh->gs_gpsinfo_recv.lat[0] = 0x00;
			//
			psh->gs_govinfo_recv.lat[0] = 0x00;
		}
		psh->gs_gpsinfo_recv.lat[1] = (*ptr - '0') * 10 + *(ptr+1) - '0';	
		//
		psh->gs_govinfo_recv.lat[1] = (*ptr - '0') * 10 + *(ptr+1) - '0';	

		temp = 	(*(ptr+2) - '0') * 10000 + 
				(*(ptr+3) - '0') * 1000 + 
				(*(ptr+5) - '0') * 100 + 
				(*(ptr+6) - '0') * 10 + 
				(*(ptr+7) - '0');
												  
		psh->gs_gpsinfo_recv.lat[2] = (unsigned char)(temp >> 8);									  
		psh->gs_gpsinfo_recv.lat[3] = (unsigned char)temp ;
		//
		psh->gs_govinfo_recv.lat[2] = (unsigned char)(temp >> 8);									  
		psh->gs_govinfo_recv.lat[3] = (unsigned char)temp ;
	

		// GPS 经度
		ptr = (unsigned char *)strstr((const char *)ptr,",");
		ptr = (unsigned char *)strstr((const char *)(ptr+1),",") + 1;
		if(*(ptr+12) == 'W')
		{
		 	psh->gs_gpsinfo_recv.lon[0] = 0x01;
		 	//
			psh->gs_govinfo_recv.lon[0] = 0x01;
		}
		else
		{
			psh->gs_gpsinfo_recv.lon[0] = 0x00;
			//
			psh->gs_govinfo_recv.lon[0] = 0x00;
		}
		psh->gs_gpsinfo_recv.lon[1] = ((*ptr - '0') * 100 + (*(ptr+1) - '0') * 10 + *(ptr+2) - '0');	
		//
		psh->gs_govinfo_recv.lon[1] = ((*ptr - '0') * 100 + (*(ptr+1) - '0') * 10 + *(ptr+2) - '0');	
			
		temp = 	(*(ptr+3) - '0') * 10000 + 
				(*(ptr+4) - '0') * 1000 + 
				(*(ptr+6) - '0') * 100 + 
				(*(ptr+7) - '0') * 10 + 
				(*(ptr+8) - '0');
					  
		psh->gs_gpsinfo_recv.lon[2] = (unsigned char)(temp >> 8);									  
		psh->gs_gpsinfo_recv.lon[3] = (unsigned char)temp;
		//
		psh->gs_govinfo_recv.lon[2] = (unsigned char)(temp >> 8);									  
		psh->gs_govinfo_recv.lon[3] = (unsigned char)temp;


     		// GPS 速度
		ptr   = (unsigned char *)strstr((const char *)ptr,",");
		ptr   = (unsigned char *)strstr((const char *)(ptr+1),",") + 1;
		index = (unsigned char *)strstr((const char *)(ptr+1),".");

		switch(index - ptr)
		{
			case 1:
				psh->gs_gpsinfo_recv.spd[1] = *ptr - '0';
				break;

			case 2:
				psh->gs_gpsinfo_recv.spd[1] = (*ptr - '0') * 10 + (*(ptr+1)- '0');
				break;

			case 3:
				psh->gs_gpsinfo_recv.spd[1] = (*ptr - '0') * 100 + (*(ptr+1)- '0') * 10 + *(ptr+2)- '0';
				break;

			default:
				psh->gs_gpsinfo_recv.spd[1] = 0;
				break;
		}


		ptr = (unsigned char *)strstr((const char *)ptr,",")+1;
		index = (unsigned char *)strstr((const char *)(ptr+1),".");
		 
		switch(index - ptr)
		{
			case 1:
				psh->gs_gpsinfo_recv.cog[0] = 0;
				psh->gs_gpsinfo_recv.cog[1] = *ptr - '0';
				//
				psh->gs_govinfo_recv.cog[0] = 0;
				psh->gs_govinfo_recv.cog[1] = *ptr - '0';
				break;

			case 2:
				psh->gs_gpsinfo_recv.cog[0] = 0;
				psh->gs_gpsinfo_recv.cog[1] = (*ptr - '0') * 10 + (*(ptr+1)- '0');
				//
				psh->gs_govinfo_recv.cog[0] = 0;
				psh->gs_govinfo_recv.cog[1] = (*ptr - '0') * 10 + (*(ptr+1)- '0');
				break;

			case 3:
				temp = 	(*ptr - '0') * 100 + (*(ptr+1)- '0') * 10 + *(ptr+2)- '0';
				psh->gs_gpsinfo_recv.cog[1] = (unsigned char)temp ;
				psh->gs_gpsinfo_recv.cog[0] = (unsigned char)(temp >> 8);
				//
				psh->gs_gpsinfo_recv.cog[1] = (unsigned char)temp ;
				psh->gs_gpsinfo_recv.cog[0] = (unsigned char)(temp >> 8);
				break;

			default:
				psh->gs_gpsinfo_recv.cog[0] = 0x00;
				psh->gs_gpsinfo_recv.cog[1] = 0x00;
				//
				psh->gs_govinfo_recv.cog[0] = 0x00;
				psh->gs_govinfo_recv.cog[1] = 0x00;
				break;
		}

		ptr = (unsigned char *)strstr((const char *)ptr,(const char *)(",")) + 1;
		psh->gs_gpsinfo_recv.time[2]   = (*ptr - '0') * 10 + (*(ptr+1) - '0');	    // 年
		psh->gs_cellinfo_recv.time[2]  = psh->gs_gpsinfo_recv.time[2];	    				// 年
		psh->gs_extrminfo_recv.time[2] = psh->gs_gpsinfo_recv.time[2];						// 年
		psh->gs_govinfo_recv.time[2]   = psh->gs_gpsinfo_recv.time[2];						// 年

		psh->gs_gpsinfo_recv.time[1]   = (*(ptr+2) - '0') * 10 + (*(ptr+3) - '0'); // 月
		psh->gs_cellinfo_recv.time[1]  = psh->gs_gpsinfo_recv.time[1];	    				// 月
		psh->gs_extrminfo_recv.time[1] = psh->gs_gpsinfo_recv.time[1];	
		psh->gs_govinfo_recv.time[1]   = psh->gs_gpsinfo_recv.time[1];	
		
		psh->gs_gpsinfo_recv.time[0]   = (*(ptr+4) - '0') * 10 + (*(ptr+5) - '0'); // 日	
		psh->gs_cellinfo_recv.time[0]  = psh->gs_gpsinfo_recv.time[0];	    				// 日
		psh->gs_extrminfo_recv.time[0] = psh->gs_gpsinfo_recv.time[0];						// 日
		psh->gs_govinfo_recv.time[0]   = psh->gs_gpsinfo_recv.time[0];						// 日

         	memcpy(&psh->gs_gpsinfo_send, &psh->gs_gpsinfo_recv, sizeof(gps_info));
         	memcpy(&psh->gs_govinfo_send, &psh->gs_govinfo_recv, sizeof(gov_info));
                printf("gpsinfo read sending!!!!\n");
		psh->gps_recv_flag =1;
		return 1;
	}
	else
	{
		for(i = 0 ; i < 26 ; i++)
		{
	//		psh->gs_gpsinfo_send[i] = 0xff;
		}

		return 0;
	}

}
