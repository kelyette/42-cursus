/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:21:40 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/07 17:49:02 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	handle_message(int sig)
{
	static char	v = 0;
	static int	i = 0;

	i++;
	v <<= 1;
	v += sig - SIGUSR1;
	if (i == 8)
	{
		if (v)
			ft_printf("%c", v);
		else
			ft_printf("\n");
		i = 0;
		v = 0;
	}
}

int	main(void)
{
	const pid_t	pid = getpid();

	ft_printf("server PID: %d\n", pid);
	signal(SIGUSR1, &handle_message);
	signal(SIGUSR2, &handle_message);
	while (1)
		;
	return (0);
}
