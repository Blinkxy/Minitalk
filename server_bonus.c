/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:08:25 by mzoheir           #+#    #+#             */
/*   Updated: 2023/03/13 16:52:54 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static char	c;
	static int	i;
	static int	pid_c;

	if (pid_c != info->si_pid)
	{
		c = 0;
		i = 0;
	}
	pid_c = info->si_pid;
	(void)context;
	if (signum == SIGUSR1)
		c ^= 1 << i;
	i++;
	if (i == 8 && c == '\0')
		kill(info->si_pid, SIGUSR2);
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	act;
	pid_t				pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	if (sigaction(SIGUSR1, &act, NULL) == -1 && sigaction(SIGUSR2, &act,
			NULL) == -1)
	{
		ft_printf("Error: sigaction failed");
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
