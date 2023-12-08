    #include <stdio.h>      // standard input / output functions
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definition
#include <vector>

std::string deviceUsed = "";

char getMsg(std::string msg) {
    char msgToSend;

    // Create an input string stream
    std::istringstream iss(msg);

    // Vector to store parsed words
    std::vector<std::string> words;

    // Parse the string using the >> operator
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }

	if (words[0] == "set") {
		return '0';
	} else if  (words[0] == "led1") {
		deviceUsed = "led1";
	    return '0';
	} else if (words[0] == "led2") {
		deviceUsed = "led2";
		return '0';
	} else if (words[0] == "led3") {
		deviceUsed = "led3";
		return '0';
	} else if (words[0] == "led4") {
		deviceUsed = "led4";
		return '0';
	} else if (words[0] == "p5") {
		deviceUsed = "p5";
		return '0';
	} else if (words[0] == "p27") {
		deviceUsed = "p27";
		return '0';
	} else if (words[0] == "p28") {
		deviceUsed = "p28";
		return '0';
    }


    /*
    LED1: high(1), low(5)
    LED2: high(2), low(6)
    LED3: high(3), low(7)
    LED4: high(4), low(8)
    p5: high(a), low(A)
    p6: high(b), low(B)
    p7: high(c), low(C)
    p8: high(d), low(D)
    p9: high(e), low(E)
    p10: high(f), low(F)
    p11: high(g), low(G)
    p12: high(h), low(H)
    p13: high(i), low(I)
    p14: high(j), low(J)
    p15: high(k), low(K)
    p16: high(l), low(L)
    p17: high(m), low(M)
    p18: high(n), low(N)
    p19: high(o), low(O)
    */
    if (deviceUsed == "led1") {
        if (words[0] == "high") {
            return '1';
        }
        else if (words[0] == "low") {
            return '5';
        }
    }
    else if (deviceUsed == "led2") {
        if (words[0] == "high") {
            return '2';
        }
        else if (words[0] == "low") {
            return '6';
        }
        else {
            std::cout << "Unrecognised input for led2 " << words[0] << std::endl;
            return '0';
        }
    }
    else if (deviceUsed == "led3") {
        if (words[0] == "high") {
            return '3';
        }
        else if (words[0] == "low") {
            return '7';
        }
        else {
            std::cout << "Unrecognised input for led3 " << words[2] << std::endl;
            return 0;
        }
    }
    else if (deviceUsed == "led4") {
        if (words[0] == "high") {
            return '4';
        }
        else if (words[0] == "low") {
            return '8';
        }
        else {
            std::cout << "Unrecognised input for led4 " << words[0] << std::endl;
            return '0';
        }
    }
    else if (deviceUsed == "p5") {
        if (words[0] == "high") {
            return 'a';
        }
        else if (words[0] == "low") {
            return 'A';
        }
        else {
            return '0';
        }
    } else if (deviceUsed == "p27") {
	if(words[0] == "high") {
		return 'z';
	} else if (words[0] == "low") {
		return 'Z';
	}
    } else if (deviceUsed == "p28") {
	if(words[0] == "high") {
		return 'y';
	} else if (words[0] == "low") {
		return 'Y';
	}
    }
    return '0';
}

int main() {

    while (1) {

        int USB = open( "/dev/ttyACM0", O_RDWR| O_NOCTTY );

        struct termios tty;
        struct termios tty_old;
        memset (&tty, 0, sizeof tty);

        // printf("Initialized\n");


        /* Error Handling */
        if ( tcgetattr ( USB, &tty ) != 0 ) {
        std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
        }

        /* Save old tty parameters */
        tty_old = tty;

        /* Set Baud Rate */
        cfsetospeed (&tty, (speed_t)B9600);
        cfsetispeed (&tty, (speed_t)B9600);

        /* Setting other Port Stuff */
        tty.c_cflag     &=  ~PARENB;            // Make 8n1
        tty.c_cflag     &=  ~CSTOPB;
        tty.c_cflag     &=  ~CSIZE;
        tty.c_cflag     |=  CS8;

        tty.c_cflag     &=  ~CRTSCTS;           // no flow control
        tty.c_cc[VMIN]   =  1;                  // read doesn't block
        tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
        tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

        /* Make raw */
        cfmakeraw(&tty);

        // printf("Weird stuff happens\n");


        /* Flush Port, then applies attributes */
        tcflush( USB, TCIFLUSH );
        if ( tcsetattr ( USB, TCSANOW, &tty ) != 0) {
            std::cout << "Error " << errno << " from tcsetattr" << std::endl;
        }

        // printf("Before write\n");

        std::string s;
        std::cin >> s;
        char msgToSend = getMsg(s);
        s = msgToSend;

        char cmd[s.size() + 1]; //as 1 char space for null is also required
        strcpy(cmd, s.c_str());
        int n_written = 0,
            spot = 0;

        do {
            n_written = write(USB, &cmd[spot], 1);
            spot += n_written;
        } while (cmd[spot-1] != '\r' && n_written > 0);

        //printf("After write\n");


        int n = 0;
        spot = 0;
        char buf = '\0';

        /* Whole response*/
        char response[1024];
        memset(response, '\0', sizeof response);

        do {
            n = read( USB, &buf, 1 );
            sprintf( &response[spot], "%c", buf );
            spot += n;
        } while( buf != '\r' && n > 0);

        if (n < 0) {
            std::cout << "Error reading: " << strerror(errno) << std::endl;
        }
        else if (n == 0) {
            std::cout << "Read nothing!" << std::endl;
        }
        else {
          //  std::cout << "Response: " << response << std::endl;
		;
        }
    }

    // printf("Exited\n");
}
