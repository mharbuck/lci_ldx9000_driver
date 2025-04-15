/***************************************************************************** 
 *                          USBLCPD Test Program                             *
 *																			 *
 *****************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define GET_HARD_VERSION	1001
#define GET_DRV_VERSION		1002
#define DEFAULT_TEXT " - Boot Complete - "
#define CLR_TEXT "                                        "
int Command_Set=0;

int clr_pd(int f)
{
	char buf[] = CLR_TEXT;
	
	if(write(f,buf,40)!=40) {
	      fprintf(stderr,"Error writing clear text: %s\n",strerror(errno));
	      return -1;
	  } 
	return 0;
	
}
int
print_driver_version(int f)
{
	char buf[128];

	memset(buf,0,128);
	if( ioctl(f,GET_DRV_VERSION, buf)!=0) {
	      fprintf(stderr,"IOCTL failed, could not get Driver Version!\n");
	      return -1;
	  } ;
	  printf("--Driver Version: %s\n",buf);
	  return 0;
	
}

int print_device_version(int f)
{
	char buf[128];
	  memset(buf,0,128);

	  if( ioctl(f,GET_HARD_VERSION, buf)!=0) {
	      fprintf(stderr,"IOCTL failed, could not get Hardware Version!\n");
	      return -1;
	  } 
	   printf("--Hardware Version: %s\n",buf);
	   return 0;


}
int write_pd_default_text(int f)
{
	printf("Display Default Text: HAL9000 ");
	printf(DEFAULT_TEXT);
	sleep(4);
	printf("\n");
	char buf[128]=DEFAULT_TEXT;
      if(write(f,buf,40)!=40) {
	      fprintf(stderr,"--Error writing text: %s\n",strerror(errno));
	      return -5;
	  } 
      else
      	{
      		printf("--write ok!\n");
      	}
      return 0;

}
int write_pd_text(int f, char* text, int len)
{
	printf("Display Text: ");
	printf("%s",text);
	printf("\n");
	char buf[128];
	strncpy(buf, text,len);
      if(write(f,buf,len)!=len) {
	      fprintf(stderr,"--Error writing text: %s\n",strerror(errno));
	      return -5;
	  } 
      else
      	{
      		printf("--write ok!\n");
      	}
      return 0;
	
}
int pd_cursor_on(int f)
{
	char buf[5];
	int len;
	
	{
		buf[0]= 0x13;
		len = 1;
	}

	printf("Cursor ON: \n");

      if(write(f,buf,len)!=len) {
	      fprintf(stderr,"--Error writing cursor on: %s\n",strerror(errno));
	      return -1;
	  } 
      else
      	{
      		printf("--cursor on ok!\n");
      	}
      return 0;
	
}
int pd_cursor_off(int f)
{
	char buf[5];
	int len;

	{
		buf[0]= 0x14;
		len = 1;
	}
	
	printf("Cursor Off: \n");

      if(write(f,buf,len)!=len) {
	      fprintf(stderr,"--Error writing cursor off: %s\n",strerror(errno));
	      return -1;
	  } 
      else
      	{
      		printf("--cursor off ok!\n");
      	}
      return 0;
	
}
int pd_position(int f, int p)
{
	char buf[5];
	int len;
	
	{
		buf[0]= 0x10;
		buf[1]=p;
		len = 2;
	}
	

	
	printf("Cursor Position: \n");

      if(write(f,buf,len)!=len) {
	      fprintf(stderr,"--Error cursor position: %s\n",strerror(errno));
	      return -1;
	  } 
      else
      	{
      		printf("--cursor position ok!\n");
      	}
      return 0;

}





int main(int argc, char *argv[ ])
{

 char buffer[10];
	
  int i,f1;
  char buf[128];
  unsigned char   test_text[]=DEFAULT_TEXT;
  
  printf("\nUSBLCPD Test Programm (C) 2003 Logic Controls, Inc.\n");
  printf("-----------------------------------------------\n");


    if( (f1=open("/dev/lcpd",O_RDONLY | O_WRONLY))==-1) { //in kernel 3.x, use this name
      fprintf(stderr,"Error opening /dev/usb/lcpd: %s\n",strerror(errno));
      fprintf(stderr,"Was the drivers loaded ? Does /dev/lcpd exist ?\n");
      return -1;
  };
  printf("Opened the Driver!");
  printf("IO Control:\n");

  print_driver_version(f1);
  print_device_version(f1);

  
  
  printf("----Test PD-------\n"); 
  
  // message flasher
  
  pd_position(f1, 0);
  write_pd_default_text(f1);
  sleep(2);
  clr_pd(f1);
  
  // sleep(1);
  
  pd_position(f1, 0);
  write_pd_default_text(f1);
  sleep(2);
  clr_pd(f1);
  
  pd_position(f1, 0);
  write_pd_default_text(f1);
  sleep(2);
  clr_pd(f1);
  
  pd_position(f1, 0);
  write_pd_default_text(f1);
  sleep(2);
  clr_pd(f1);
  
  
 
  // closer 
  pd_position(f1, 0);
  close(f1);

  printf("-----------------------------------------------\n");
  printf("Test Done !\n");

  return(0);
}
