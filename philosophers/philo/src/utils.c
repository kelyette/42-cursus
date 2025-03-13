/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:56:21 by kcsajka           #+#    #+#             */
/*   Updated: 2025/03/07 18:28:40 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

int	atoi_check(char *str, int *ptr)
{
	long	n;

	n = 0;
	while (*str && n <= INT_MAX)
	{
		if ((*str < '0' || *str > '9')
			&& printf("error: unexpected character '%c'\n", *str))
			return (1);
		n = n * 10 + (*str++ - '0');
	}
	if (n > INT_MAX
		&& printf("error: too big\n"))
		return (1);
	*ptr = n;
	return (0);
}

uint64_t	get_time(void)
{
	struct timeval			ctime;

	if (gettimeofday(&ctime, NULL) == -1
		&& printf("error: gettimeofday error (%d)\n", errno))
		return (0);
	return (ctime.tv_sec * 1000 + ctime.tv_usec / 1000);
}

void	precise_sleep(uint64_t t)
{
	const uint64_t	s = get_time();

	while (get_time() - s < t)
		usleep(100);
}

void	msg(t_philo *philo, char *msg)
{
	static uint64_t	start_time;

	if (!start_time)
		start_time = philo->table->start_time;
	pthread_mutex_lock(&philo->table->msg_lock);
	if (1 || msg[0] == 'd' || !philo->table->dead) // TODO
		printf("%lld %d %s\n", (long)get_time() - start_time,
			philo->id + 1, msg);
	pthread_mutex_unlock(&philo->table->msg_lock);
}
