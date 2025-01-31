/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:23:50 by anguenda          #+#    #+#             */
/*   Updated: 2025/01/31 20:26:09 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "talk.h"

void	hundler(int signum, siginfo_t *info, void *context)
{
	static int	bit = -1;
	static int	c = 0;

	(void)context;
	if (kill(info->si_pid, 0) < 0)
	{
		ft_putendl_fd("ERROR D ENVOI LE SIGNALE DE CONFIRMATION", 1);
		exit(EXIT_FAILURE);
	}
	if (bit < 0 && !c)
		write(1, "\n", 1);
	if (bit < 0)
		bit = 7;
	if (signum == SIGUSR1)
		c = c | (1 << bit);
	else if (signum == SIGUSR2)
		c = c & (~(1 << bit));
	if (!bit && c)
		write(1, &c, 1);
	else if (!bit && !c)
		kill(info->si_pid, SIGUSR2);
	bit--;
	kill(info->si_pid, SIGUSR1);
}

void	sig_wejed(int sig, void (*handler1)(int, siginfo_t *, void *))
{
	struct sigaction	sigo;

	sigo.sa_sigaction = handler1;
	sigo.sa_flags = SA_SIGINFO;
	sigemptyset(&sigo.sa_mask);
	if (sig == SIGUSR1)
	{
		sigaction(sig, &sigo, 0);
	}
	if (sig == SIGUSR2)
	{
		sigaction(sig, &sigo, 0);
	}
}

int	main(void)
{
	sig_wejed(SIGUSR1, &hundler);
	sig_wejed(SIGUSR2, &hundler);
	ft_putstr_fd("le pid de ce serveur est : ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (154)
	{
		usleep(50);
	}
}
