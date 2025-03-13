/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:11:47 by kcsajka           #+#    #+#             */
/*   Updated: 2025/03/12 12:51:16 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdint.h>
# ifndef MAX_PHILOS
#  define MAX_PHILOS 200
# endif
# define MFORK  "has taken fork" // TODO
# define MEAT   "is eating"
# define MSLEEP "is sleeping"
# define MTHINK "is thinking"
# define MDIED  "died"

// Allowed functions: 
//   memset, printf, malloc, free, write, usleep, gettimeofday
//   pthread_create, pthread_detach, pthread_join
//   pthread_mutex_init, pthread_mutex_destroy,
//   pthread_mutex_lock, pthread_mutex_unlock

struct	s_table;

typedef struct s_philo
{
	pthread_t		tid;
	struct s_table	*table;
	int				id;
	int				eating;
	uint64_t		lastmeal;
	int				mealcount;
	int				done;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	lock;
}	t_philo;

typedef struct s_table
{
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
	int				init;
	uint64_t		start_time;
	int				dead;
	int				pcount;
	uint64_t		ttdie;
	uint64_t		tteat;
	uint64_t		ttsleep;
	int				nmeals;
	pthread_mutex_t	lock;
	pthread_mutex_t	msg_lock;
}	t_table;

int			init_table(t_table *table, char **args, int argc);
int			init_philo(t_philo *philo, t_table *table, int id);

void		*philosopher(void *phptr);
void		*barbouille(void *phptr);
int			eat(t_philo *philo, uint64_t tteat);

int			atoi_check(char *str, int *ptr);
void		msg(t_philo *philo, char *msg);
uint64_t	get_time(void);
void		precise_sleep(uint64_t t);

#endif
