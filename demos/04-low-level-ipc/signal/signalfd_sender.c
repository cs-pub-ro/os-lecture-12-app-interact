#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signalfd.h>

#include "utils.h"

static void send_signal(int sfd, int sig)
{
	struct signalfd_siginfo fdsi = {0};
	int rc;

	fdsi.ssi_signo = sig;

	rc = write(sfd, &fdsi, sizeof(struct signalfd_siginfo));
	DIE(rc < 0, "write");
	DIE(rc != sizeof(struct signalfd_siginfo), "write");

	usleep(100000);
}

int main(int argc, char **argv)
{
	pid_t receiver_pid;
	int sfd;
	sigset_t mask;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <receiver_pid>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	receiver_pid = atoi(argv[1]);

	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);
	sigaddset(&mask, SIGALRM);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGTERM);
	sigaddset(&mask, SIGQUIT);
	sigaddset(&mask, SIGTSTP);
	sigaddset(&mask, SIGCONT);

	sfd = signalfd(-1, &mask, 0);
	DIE(sfd < 0, "signalfd");

	send_signal(sfd, SIGUSR1);  // h
	send_signal(sfd, SIGUSR2);  // e
	send_signal(sfd, SIGALRM);  // l
	send_signal(sfd, SIGALRM);  // l
	send_signal(sfd, SIGINT);   // o
	send_signal(sfd, SIGTERM);  // w
	send_signal(sfd, SIGINT);   // o
	send_signal(sfd, SIGQUIT);  // r
	send_signal(sfd, SIGALRM);  // l
	send_signal(sfd, SIGTSTP);  // d
	send_signal(sfd, SIGCONT);  // end and print newline

	close(sfd);

	return 0;
}
