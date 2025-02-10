/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:20:06 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/07 18:17:11 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	send_byte(pid_t pid, char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1 + ((c >> i) & 1));
		usleep(30);
	}
}

int	send_msg(pid_t pid, char *msg)
{
	while (*msg)
		send_byte(pid, *msg++);
	send_byte(pid, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t		srv_pid;

	if (argc < 3 && ft_printf("usage: %s <server pid> <message>\n", argv[0]))
		return (1);
	srv_pid = ft_atoi(argv[1]);
	if (srv_pid == 0
		&& ft_printf("erorr: make sure \"%s\" is a valid PID\n", argv[1]))
		return (1);
	send_msg(srv_pid, argv[2]);
}
