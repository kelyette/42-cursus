/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:21:40 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/26 12:21:14 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	handle_message(int sig, siginfo_t *info, void *ctx)
{
	static char		v = 0;
	static int		i = 0;
	static pid_t	c_pid;

	(void)ctx;
	if (c_pid && c_pid != info->si_pid)
	{
		v = 0;
		i = 0;
	}
	c_pid = info->si_pid;
	i++;
	v <<= 1;
	v += sig == SIGUSR2;
	if (i == 8)
	{
		if (v)
			write(1, &v, 1);
		else
			write(1, "\n", 1);
		i = 0;
		v = 0;
	}
	kill(c_pid, SIGUSR1);
}

int	main(void)
{
	const pid_t			pid = getpid();
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_message;
	ft_printf("server PID: %d\n", pid);
	if (sigaction(SIGUSR1, &sa, NULL) || sigaction(SIGUSR2, &sa, NULL))
	{
		ft_printf("error: sigaction error\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
