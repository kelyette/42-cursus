/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:20:06 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/26 12:24:16 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#ifndef TIMEOUT_US
# define TIMEOUT_US 1000000
#endif

int	g_ack;

void	handle_ack(int sig, siginfo_t *info, void *ctx)
{
	(void)sig;
	(void)info;
	(void)ctx;
	g_ack = 1;
}

int	send_byte(pid_t pid, char c)
{
	int		i;
	long	time;

	i = 8;
	while (i--)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		time = 0;
		g_ack = 0;
		while (!g_ack)
		{
			usleep(10);
			time += 10;
			if (time * 10 >= TIMEOUT_US
				&& ft_printf("error: server did not acknowledge in time\n"))
				return (1);
		}
	}
	return (0);
}

int	send_msg(pid_t pid, char *msg)
{
	while (*msg)
		if (send_byte(pid, *msg++))
			return (1);
	return (send_byte(pid, 0));
}

int	main(int argc, char **argv)
{
	pid_t				srv_pid;
	struct sigaction	sa;

	g_ack = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_ack;
	if (argc != 3 && ft_printf("usage: %s <server pid> <message>\n", argv[0]))
		return (1);
	srv_pid = ft_atoi(argv[1]);
	if ((srv_pid <= 0)
		&& ft_printf("error: make sure \"%s\" is a valid PID\n", argv[1]))
		return (1);
	if (sigaction(SIGUSR1, &sa, NULL)
		&& ft_printf("error: sigaction error\n"))
		return (1);
	send_msg(srv_pid, argv[2]);
}
