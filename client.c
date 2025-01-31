/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:23:31 by anguenda          #+#    #+#             */
/*   Updated: 2025/01/31 20:24:14 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "talk.h"

int		g_confirmation;

void	send_bytes(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (kill(pid, 0) < 0)
		{
			ft_putendl_fd("ERROR  D ENVOI AU SERVEUR", 1);
			exit(EXIT_FAILURE);
		}
		g_confirmation = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		while (g_confirmation != 1)
			usleep(50);
	}
}

void	send_msg(char *ptr, int pid)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		send_bytes(pid, ptr[i]);
		i++;
	}
	send_bytes(pid, 0);
}

void	handler(int signum)
{
	if (signum == SIGUSR1)
		g_confirmation = 1;
	else if (signum == SIGUSR2)
	{
		ft_putendl_fd("le message a bien recus", 1);
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
	{
		ft_putendl_fd("Usage : ./client <PID> <Message>", 1);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	pid = ft_atoi(av[1]);
	if (!pid)
	{
		ft_putendl_fd("invalid pid ", 1);
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(av[2]) == 0)
	{
		ft_putendl_fd("Tu dois écrire un message", 1);
		exit(EXIT_FAILURE);
	}
	send_msg(av[2], pid);
	while (12)
		usleep(50);
}
