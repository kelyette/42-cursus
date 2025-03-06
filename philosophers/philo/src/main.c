/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:54:57 by kcsajka           #+#    #+#             */
/*   Updated: 2025/03/06 13:32:09 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_param(t_table	*table, char **args, int argc)
{
	int	ttdie;
	int	tteat;
	int	ttsleep;

	table->nmeals = 0;
	if (atoi_check(args[0], &table->pcount) || atoi_check(args[1], &ttdie)
		|| atoi_check(args[2], &tteat) || atoi_check(args[3], &ttsleep))
		return (1);
	if ((!table->pcount || table->pcount > MAX_PHILOS)
		&& printf("error: invalid value for philo count %d, "
			"0 < x < %d needed\n", table->pcount, MAX_PHILOS))
		return (1);
	table->ttdie = (uint64_t)ttdie;
	table->tteat = (uint64_t)tteat;
	table->ttsleep = (uint64_t)ttsleep;
	if (argc == 5 && atoi_check(args[4], &table->nmeals))
		return (1);
	return (0);
}

int	init_table(t_table *table, char **args, int argc)
{
	int	i;

	pthread_mutex_lock(&table->lock);
	if (init_param(table, args, argc))
		return (1);
	pthread_mutex_init(&table->lock, NULL);
	pthread_mutex_init(&table->msg_lock, NULL);
	i = -1;
	while (++i < table->pcount)
	{
		pthread_mutex_init(&table->philos[i].lock, NULL);
		pthread_mutex_init(&table->forks[i], NULL);
	}
	table->start_time = get_time();
	pthread_mutex_unlock(&table->lock);
	i = -1;
	while (++i < table->pcount)
	{
		table->philos[i].table = table;
		table->philos[i].id = i;
		table->philos[i].fork_l = &table->forks[i];
		table->philos[i].fork_r = &table->forks[(i + 1) % table->pcount];
		table->philos[i].lastmeal = table->start_time;
		pthread_create(&table->philos[i].tid, NULL,
			philosopher, &table->philos[i]);
		usleep(100);
	}
	i = -1;
	while (++i < table->pcount)
		pthread_join(table->philos[i].tid, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	static t_table	table = {0};

	if (argc != 5 && argc != 6
		&& printf("usage: %s <num. philosophers> <time to die> "
			"<time to eat> <time to sleep> [<num. meals required>]\n", argv[0]))
		return (1);
	if (init_table(&table, argv + 1, argc - 1))
		return (1);
	return (0);
}
