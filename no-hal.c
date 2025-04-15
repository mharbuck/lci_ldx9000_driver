/***************************************************************************** 
 *                          HAL9000                                          *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
// #include <ncurses.h>

#define GET_HARD_VERSION	1001
#define GET_DRV_VERSION		1002
#define DEFAULT_TEXT "---HAL9000---"
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
	printf("Display Default Text: ");
	printf(DEFAULT_TEXT);
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

// ______________________________________________________MAIN______________________

int main(int argc, char *argv[ ])
{

for (;;) 
  {

 char buffer[10];

	
  int i,f1;
  char buf[128];
  
  //unsigned char backlight_off[]={0x00,0x20};
  //unsigned char backlight_on[]={0x00,0x21};
  unsigned char   test_text[]=DEFAULT_TEXT;
  
  printf("\nHAL9000 Test Programm (C) 2022 Urbana Corp, LLC.\n");
  printf("-----------------------------------------------\n");
  sleep(0);

 // if( (f1=open("/dev/usb/lcpd",O_RDONLY | O_WRONLY))==-1) { //it is for kernel 2.6
    if( (f1=open("/dev/lcpd",O_RDONLY | O_WRONLY))==-1) { //in kernel 3.x, use this name
      fprintf(stderr,"Error opening /dev/usb/lcpd: %s\n",strerror(errno));
 //   fprintf(stderr,"Was the drivers loaded ? Does /dev/usb/lcpd exist ?\n");
      fprintf(stderr,"Was the drivers loaded ? Does /dev/lcpd exist ?\n");
      return -1;
  };
  
  clr_pd(f1);                                                               // Initial clear command / reinitialize
  printf("Opened the Driver!");
  printf("IO Control:\n");
  print_driver_version(f1);
  print_device_version(f1);
  printf("----Test HAL Logic------\n");                                    // ------------------------------------------- 
  
  
	    // --------------------  start dialogue -----------
  
  pd_position(f1, 3);
  write_pd_default_text(f1); // from default text variable
  sleep(2);
  
 
  
  clr_pd(f1);
  pd_position( f1, 0);
  write_pd_text(f1, "Hello, Dave.",20);
  sleep(2);
  
  // ------------------   start dialogue -------------------
  
  pd_position( f1, 0);
  write_pd_text(f1, "I'm sorry Dave, I   can't do that.",40 );
  sleep(2);
  
  //pd_position( f1, 35);
 
  // ----------------"1...5....0....5....0/....5....0 //
  // clr_pd(f1);
  	
  
  clr_pd(f1);
  pd_position( f1, 0);
  write_pd_text(f1, "I am putting mself  to the fullest",40 );
  sleep(2);
  
  
  clr_pd(f1);
  pd_position( f1, 0);
  write_pd_text(f1, "possible use, which is all I think that",40 );
  sleep(2);
  
  
  clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "any conscious entitycan ever ",40);
  sleep(2);
 
  clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "hope to do.",40);
  sleep(2);
 
 
  clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaa/aaaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "Open the pod bay    doors please, HAL.",40);
  sleep(2);
 
 
  
   clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "HAL : Affirmative,  Dave. I read you. ",40);
  sleep(2);
 
 
  
  clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "I  think  you  know what the problem is",40);
  sleep(2);
 
  clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "just   as   much    as  I  do.",40);
  sleep(2);
  
  clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "This mission is too important for me to",40);
  sleep(2);
  

  clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaa/aaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "allow   you    to   jeopardize it.",40);
  sleep(2);
  
  clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaa/aaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "I know that you and Frank were planning",40);
  sleep(2);

    clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaa/aaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "to disconnect me, and I'm afraid that's",40);
  sleep(2);
  
  clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaa/aaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "something  I  cannot  allow to happen.",40);
  sleep(2);
  
  clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaa/aaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "Dave, this conver-  sation can serve no",40);
  sleep(2);
  
  clr_pd(f1);
  pd_position( f1, 0);
  //				"aaaaaaaaaaaaaaaaaaaa/aaaaaaaaaaaaaaaaaaa"
  write_pd_text(f1, "pupose anymore.          Goodbye.",40);
  sleep(2);
 
  close(f1);                                                               // close connection to display/driver

  printf("-----------------------------------------------\n");             // ----------------------------------------
  printf("Test Complete !\n");
	  
	  
	  
	  }
  
  

  

  return(0);
}

