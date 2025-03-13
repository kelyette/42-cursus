/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:45:57 by kcsajka           #+#    #+#             */
/*   Updated: 2025/03/12 13:14:22 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	drop_forks(t_philo *philo, int n)
{
	pthread_mutex_unlock(philo->fork_l);
	if (n == 2)
		pthread_mutex_unlock(philo->fork_r);
	return (1);
}

void	msgf(t_philo *philo, char *msg, pthread_mutex_t *fork)
{
	static uint64_t	start_time;

	if (!start_time)
		start_time = philo->table->start_time;
	pthread_mutex_lock(&philo->table->msg_lock);
	printf("%lld %d %s %lu\n", (long)get_time() - start_time, philo->id + 1, msg, (unsigned long)(++fork - philo->table->forks));
	pthread_mutex_unlock(&philo->table->msg_lock);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*tmp;

	pthread_mutex_lock(philo->fork_l);
	if (philo->table->dead)
		return (drop_forks(philo, 1));
	msgf(philo, MFORK, philo->fork_l);
	if (philo->fork_l == philo->fork_r)
		return (drop_forks(philo, 1));
	pthread_mutex_lock(philo->fork_r);
	if (philo->table->dead)
		return (drop_forks(philo, 1));
	pthread_mutex_lock(&philo->lock);
	msgf(philo, MFORK, philo->fork_r);
	tmp = philo->fork_l;
	philo->fork_l = philo->fork_r;
	philo->fork_r = tmp;
	return (0);
}

int	eat(t_philo *philo, uint64_t tteat)
{
	if (take_forks(philo))
		return (1);
	msg(philo, MEAT);
	philo->eating = 1;
	pthread_mutex_unlock(&philo->lock);
	precise_sleep(tteat);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	philo->mealcount++;
	philo->lastmeal = get_time();
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo, 2);
	return (philo->table->dead);
}
