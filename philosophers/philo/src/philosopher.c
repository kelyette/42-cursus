/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:59:30 by kcsajka           #+#    #+#             */
/*   Updated: 2025/03/06 13:51:09 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*barbouille(void *phptr)
{
	t_philo		*philo;
	uint64_t	ttdie;

	philo = (t_philo *)phptr;
	ttdie = philo->table->ttdie;
	while (!philo->table->dead)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() - philo->lastmeal >= ttdie)
		{
			pthread_mutex_lock(&philo->table->lock);
			if (!philo->table->dead)
				msg(philo, MDIED);
			philo->table->dead = 1;
			pthread_mutex_unlock(&philo->table->lock);
			pthread_mutex_unlock(&philo->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->lock);
		usleep(100);
	}
	return (NULL);
}

void	*philosopher(void *phptr)
{
	t_philo		*philo;
	pthread_t	tb;
	uint64_t	tteat;
	uint64_t	ttsleep;

	philo = (t_philo *)phptr;
	tteat = philo->table->tteat;
	ttsleep = philo->table->ttsleep;
	pthread_create(&tb, NULL, barbouille, philo);
	while (!philo->table->dead)
	{
		if (eat(philo, tteat))
			break ;
		msg(philo, MSLEEP);
		precise_sleep(ttsleep);
		if (philo->table->dead)
			break ;
		msg(philo, MTHINK);
	}
	pthread_join(tb, NULL);
	return (NULL);
}

int	init_philo(t_philo *philo, t_table *table, int id)
{
	philo->table = table;
	philo->id = id;
	philo->fork_l = &table->forks[id];
	philo->fork_r = &table->forks[(id + 1) % table->pcount];
	philo->lastmeal = table->start_time;
	pthread_create(&philo->tid, NULL, philosopher, philo);
	return (0);
}
