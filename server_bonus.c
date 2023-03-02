/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:08:25 by mzoheir           #+#    #+#             */
/*   Updated: 2023/03/02 16:41:58 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void handle_signal(int signum, siginfo_t *info, void *context) 
{
    static char c;
    static int i;
    static int pid_c;
    
    if(pid_c != info->si_pid)
    {
        c = 0;
        i = 0;
    }
    pid_c = info->si_pid;
    (void)context;
    if (signum == SIGUSR1)  
        c ^= 1 << i;
    i++;
    if(i == 8)
    {
        write(1,&c,1);
        i = 0;
        c = 0;
        kill(pid_c, SIGUSR2);
    }     
}

int main() 
{
    struct sigaction act;
    pid_t pid;
    
    pid = getpid();
    ft_printf("Server PID: %d\n", pid);
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = handle_signal;
    sigaction(SIGUSR1, &act, NULL);
    while (1)
    {
        pause();
    }
    return 0;
}

