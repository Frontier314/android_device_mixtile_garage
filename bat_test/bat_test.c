#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int get_adc(void)
{
  int fd, ret, len;
  char buffer[24];
	fd = open("/sys/class/power_supply/battery/batt_vol_adc", O_RDONLY);
	read(fd, buffer, 10);
	close(fd);
	return atoi(buffer);
}

void write_log(char *file_name, int adc_value, unsigned long time)
{
  int fd;
  char buf[64];
  sprintf(buf, "%06lu %04d\n", time, adc_value); 
  fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  if(fd<=0)
    printf("open file %s error\n", file_name);
  write(fd, buf, strlen(buf)+1);
  fsync(fd);
  close(fd);
}

int main(void)
{
  unsigned long int start_time, now_time;
  int adc_value;
  
  start_time = time(NULL);
  while(1)
  {
    adc_value = get_adc();
    now_time = time(NULL);
    write_log("/mnt/sdcard/bat_test.log", adc_value, now_time-start_time);
    sleep(10);
  }
  return 0;
}
