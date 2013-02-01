
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

int main()
{

	int fd;

	//open serial device /dev/usbserial...

	fd = open("/dev/cu.usbserial-A800eIEM", O_RDWR | O_NOCTTY | O_NDELAY);

	struct termios serial_opt;

	tcgetattr(fd, &serial_opt);	

	//c_flag no parity, 8 bit, receiever, ignore CD modem, no hardware flow control
	//for hardware.. follows hardware characteristic..arduino:
	serial_opt.c_cflag &= ~CSTOPB; //1 stop bit
	serial_opt.c_cflag &= ~CRTSCTS; //output hardware flow control (only used if the cable has all necessary lines. See sect. 7 of Serial-HOWTO)
	serial_opt.c_cflag &= ~PARENB; //disable parity bit
	serial_opt.c_cflag &= ~CSIZE; //clear size bit
	serial_opt.c_cflag |= CS8; // enable 8 bit
	serial_opt.c_cflag |= CREAD | CLOCAL; //enable receiver, local connection, no modem contol


	//hardware input
	//handle data before it goes to the program
	//When an application reads from a disk, the data is merely transferred from the disk to the
	//program, with no special processing taking place. This is not true when data is read from a
	//terminal. When a character is typed on a terminal, the system does some processing before
	//handing it to the user program. This processing consists of two tasks:
    serial_opt.c_iflag &= ~(IXON | IXOFF | IXANY); //disable software flow control

	//Local term settings
	serial_opt.c_lflag &= ~ISIG; //disable signal interrupt
	serial_opt.c_lflag &= ~ECHOE; //disable ECHO
	serial_opt.c_lflag &= ~ECHO; //disable ECHO
	serial_opt.c_lflag &= ~ICANON; //enable non canon (raw)

	//disable output processing
	serial_opt.c_oflag &= ~OPOST;


	//printf("serial opt: %i\n", (int) serial_opt.c_cflag);

	printf("asssik!\n");

	close(fd);
	return 0;
}