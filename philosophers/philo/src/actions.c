/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:45:57 by kcsajka           #+#    #+#             */
/*   Updated: 2025/03/06 13:58:25 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(philo->fork_l);
		return (1);
	}
	msg(philo, MFORK);
	if (philo->fork_l == philo->fork_r)
	{
		pthread_mutex_unlock(philo->fork_l);
		return (1);
	}
	pthread_mutex_lock(philo->fork_r);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return (1);
	}
	msg(philo, MFORK);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

int	eat(t_philo *philo, uint64_t tteat)
{
	if (take_forks(philo))
		return (1);
	msg(philo, MEAT);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	pthread_mutex_unlock(&philo->lock);
	precise_sleep(tteat);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	philo->lastmeal = get_time();
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
	return (philo->table->dead);
}
