/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:59:30 by kcsajka           #+#    #+#             */
/*   Updated: 2025/03/12 13:00:16 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*barbouille(void *phptr)
{
	t_philo		*philo;
	uint64_t	ttdie;

	philo = (t_philo *)phptr;
	ttdie = philo->table->ttdie;
	while (!philo->table->dead && !philo->done)
	{
		pthread_mutex_lock(&philo->lock);
		if (!philo->eating && get_time() - philo->lastmeal >= ttdie)
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

static inline int	check_meals(t_philo *philo)
{
	if (philo->mealcount != philo->table->nmeals)
		return (0);
	pthread_mutex_lock(&philo->lock);
	philo->done = 1;
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

void	*philosopher(void *phptr)
{
	t_philo		*philo;
	pthread_t	tb;

	philo = (t_philo *)phptr;
	while (get_time() < philo->table->start_time || !philo->table->init)
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(10000);
	pthread_create(&tb, NULL, barbouille, philo);
	while (!philo->table->dead)
	{
		if (eat(philo, philo->table->tteat) == 1 || check_meals(philo))
			break ;
		msg(philo, MSLEEP);
		precise_sleep(philo->table->ttsleep);
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
