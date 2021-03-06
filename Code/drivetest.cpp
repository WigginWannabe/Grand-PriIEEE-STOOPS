#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ImageAnalyze.hpp"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

//#define ADDRESS 0x04 // need to dynamically discover real each boot

//static const char *devName = "/dev/i2c-1";

//char killFlag[1] = 0;
unsigned char speed;
unsigned char angle;
unsigned char prev_angle = 0;
const float kP = 1.3;
const float kD = 0;

void setAngle(float angle) {
  FILE * file;
  static float divisor = 1.8;
  file = fopen ("/dev/servoblaster","w+");
  
  float percent = angle/divisor;
  fprintf(file, "0=%f%\n", percent);
  fprintf(stdout,"0=%f%\n", percent);
  fclose (file);
}

int main() {

/*    printf("I2C: Connecting\n");
    int file;
 
    if ((file = open(devName, O_RDWR)) < 0) {
        cerr << "I2C: Failed to access " << devName << endl;
        exit(1);
    }

    cerr << "I2C: acquiring bus to " << ADDRESS << endl;
 
    if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
        cerr << "I2C: Failed to acquire bus access/talk to slave " <<
                            ADDRESS << endl;
        exit(1);
    }
*/
    ImageAnalyze imganlz;

    while(1){
        angle = imganlz.errorDetect(); // must encode
        cout << "angle: " << angle << endl;
        setAngle(kP*angle + kD*(angle-prev_angle));
        angle = prev_angle;
        
        // speed = 191;// will be called once we vary speed, for now const ~75%

        // cout << "Sending " << (int)speed << endl;
        // write(file, speed, 1);


        /* --------------------
         *  Kill switch stuff. Not applicable yet
         
        if (read(file, killFlag, 1) != 1) {
         fprintf(stderr, "I2C: Failed to read interrupt from slave 0x%x\n");
        }

        if ( (int) killFlag[0] == 1 ) {
            close(file);
            return 0;
        }*/ 
   }
}
