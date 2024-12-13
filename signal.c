/* ************************************************************************** */
/*			                                                                */
/*			                                            :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*			                                        +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>			          +#+  +:+       +#+        */
/*			                                    +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:45:38 by mpihur			#+#    #+#             */
/*   Updated: 2024/07/25 17:28:48 by sanoor           ###   ########.fr       */
/*			                                                                */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/wait.h>

void	sigchld_handler(int sig)
{
	(void)sig;
	g_signals[0] = 128 + sig;
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
}

void	sigint_handler(int sig)
{
	g_signals[1] = 1;
	g_signals[0] = 128 + sig;
	rl_replace_line("", 1);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(int sig)
{
	g_signals[0] = 128 + sig;
	if (sig == SIGPIPE)
		exit(1);
	if (sig == SIGSEGV)
	{
		write(STDERR_FILENO, "minishell: segmentation fault\n", 29);
		exit (139);
	}
}

static void	other_signals(const int *signal_list, unsigned long i, size_t size)
{
	while (i < size)
	{
		if (signal(signal_list[i++], signal_handler) == SIG_ERR)
		{
			perror("SIG_ERR");
			exit(EXIT_FAILURE);
		}
	}
}

void	setup_signal_handlers(void)
{
	const int			signal_list[] = {SIGHUP, SIGILL, SIGABRT, SIGFPE,
		SIGSEGV, SIGPIPE, SIGALRM, SIGTERM, SIGUSR1,
		SIGUSR2, SIGBUS, SIGPROF, SIGSYS};
	struct sigaction	sa;

	if (signal(SIGINT, sigint_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("SIGINT_ERR");
		exit(EXIT_FAILURE);
	}
	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit (g_signals[1]);
	}
	other_signals(signal_list, 0, sizeof(signal_list) / sizeof(signal_list[0]));
}
