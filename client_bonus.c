/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:51:02 by mzoheir           #+#    #+#             */
/*   Updated: 2023/03/13 22:38:17 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(pid_t pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c & 1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(300);
	}
}

void	incoming_sig(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("Message received by the server");
}

void	error_pid(char *argv)
{
	if (ft_atoi(argv) < 0)
	{
		ft_printf("Invalid PID\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	struct sigaction	act;
	int					i;

	if (argc == 3)
	{
		act.sa_handler = incoming_sig;
		sigaction(SIGUSR2, &act, NULL);
		if (sigaction(SIGUSR2, &act, NULL) == -1)
		{
			ft_printf("Error: sigaction failed");
			exit(EXIT_FAILURE);
		}
		error_pid(argv[1]);
		server_pid = ft_atoi(argv[1]);
		i = 0;
		while (argv[2][i])
		{
			send_char(server_pid, argv[2][i]);
			i++;
		}
		send_char(server_pid, '\0');
	}
	return (0);
}
