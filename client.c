/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:51:02 by mzoheir           #+#    #+#             */
/*   Updated: 2023/03/02 16:36:20 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int size;

void    send_char(pid_t pid, char c)
{
    int i = 0;
    while (i < 8)
    {
        if((c & 1 << i))
            kill(pid,SIGUSR1);
        else
            kill(pid,SIGUSR2);
        i++;
        usleep(100);
    }
        
}

int main(int argc, char** argv) 
{
    pid_t server_pid;
    
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
    
    while (argv[2][i])
    {
        send_char(server_pid,argv[2][i]);
        i++;
    }
    return 0;
}
