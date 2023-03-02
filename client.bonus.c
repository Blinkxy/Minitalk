/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:51:02 by mzoheir           #+#    #+#             */
/*   Updated: 2023/03/02 16:39:56 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int send;

void    send_char(pid_t pid, char c)
{
    int i = 0;
    while (i < 8)
    {
        if((c & 1 << i))
            kill(pid,SIGUSR1);
        i++;
        usleep(100);
    }       
}

void    incoming_sig(int signal)
{ 
    if( signal == SIGUSR2)
    {
        write(1,"hi\n",2);
        send++;
    }
}
int main(int argc, char** argv) 
{
    pid_t server_pid;
    struct sigaction act;
    int size;
    
    sigaction(SIGUSR2, &act, NULL);
    act.sa_handler = incoming_sig;
    if (argc != 3) 
    {
        printf("Error: Not enough/Too many arguments\n");
        exit(0);
    }
    if (ft_atoi(argv[1]) < 0)
        {
            ft_printf("Invalid PID\n");
            exit(0);
        }
    server_pid = atoi(argv[1]);
    int i = 0;
    size = ft_strlen(argv[2]);
    while (argv[2][i])
    {
        send_char(server_pid,argv[2][i]);
        i++;
    }
    if(send == size)
        ft_printf("Full Message received\n");
    return 0;
}
