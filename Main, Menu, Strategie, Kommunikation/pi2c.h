#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), */
#include <sys/ioctl.h>

class Pi2c {
		//Var to hold the i2c communications handle, 
		//...this will only be needed by the class itself, so it's private
		int i2cHandle_;
	public:
		//Function: Constructor - First parameter is the I2C address of the slave being talked to.
		//...Second parameter is optional. Set true if using a Rev0 Raspberry Pi.
		//...Returns: Nothing.
		Pi2c(int address, bool rev0 = false);
		
		//Function: Destructor - Closes the I2C File handle.
		//...Returns: Nothing.
		~Pi2c();
		
		//Function: i2cRead - First parameter is a pointer to a char array. This will also contain the 
		//...values passed back from the Arduino.
		//...Second parameter is the length of the array.
		//...Returns: Error value. > 0 is ok. < 0 means there was an error.
		int i2cRead(char *data,int length);
		
		//Function: i2cWrite - First parameter is a pointer to a char array.containing the data to send.
		//...Second parameter is the length of the array.
		//...Returns: Error value. > 0 is ok. < 0 means there was an error.
		int i2cWrite(char *data,int length);
		
		//Function: i2cWrite - No Parameters.
		//...Returns: An Int value sent from the arduino, or -1 if there was an error.
		int i2cReadArduinoInt();
		
		//Function: i2cWrite - First parameter the int to send to the array.
		//...Returns: Error value. > 0 is ok. < 0 means there was an error.
		int i2cWriteArduinoInt(int x, int y);
};