#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "utils.h"

static void print_char(int signum)
{
	switch(signum) {
	case SIGUSR1:
		putchar('h');
		break;
	case SIGUSR2:
		putchar('e');
		break;
	case SIGALRM:
		putchar('l');
		break;
	case SIGINT:
		putchar('o');
		break;
	case SIGTERM:
		putchar('w');
		break;
	case SIGQUIT:
		putchar('r');
		break;
	case SIGTSTP:
		putchar('d');
		break;
	case SIGCONT:
		putchar('\n');
		exit(EXIT_SUCCESS);
	}
}

int main(void)
{
	printf("Receiver PID: %d\n", getpid());

	signal(SIGUSR1, print_char);
	signal(SIGUSR2, print_char);
	signal(SIGALRM, print_char);
	signal(SIGINT,  print_char);
	signal(SIGTERM, print_char);
	signal(SIGQUIT, print_char);
	signal(SIGTSTP, print_char);
	signal(SIGCONT, print_char);

	while(1) {
		pause();
	}

	return 0;
}
