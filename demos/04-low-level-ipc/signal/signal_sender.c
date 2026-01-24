#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "utils.h"

static void send_signal(pid_t pid, int sig)
{
	int rc;

	rc = kill(pid, sig);
	DIE(rc < 0, "kill");

	usleep(100000);
}

int main(int argc, char **argv)
{
	pid_t receiver_pid;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <receiver_pid>\n", argv[0]);
		exit(1);
	}

	receiver_pid = atoi(argv[1]);

	send_signal(receiver_pid, SIGUSR1);  // h
	send_signal(receiver_pid, SIGUSR2);  // e
	send_signal(receiver_pid, SIGALRM);  // l
	send_signal(receiver_pid, SIGALRM);  // l
	send_signal(receiver_pid, SIGINT);   // o
	send_signal(receiver_pid, SIGTERM);  // w
	send_signal(receiver_pid, SIGINT);   // o
	send_signal(receiver_pid, SIGQUIT);  // r
	send_signal(receiver_pid, SIGALRM);  // l
	send_signal(receiver_pid, SIGTSTP);  // d
	send_signal(receiver_pid, SIGCONT);  // end and print newline

	return 0;
}
