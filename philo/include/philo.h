/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:26:20 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/15 22:20:56 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define M_TAKEN_FORK "has taken a fork\n"
# define M_EATING "is eating\n"
# define M_SLEEPING "is sleeping\n"
# define M_THINKING "is thinking\n"
# define M_DIED "died\n"

typedef struct s_config
{
	int64_t	nbr_philos;
	int64_t	time_to_die;
	int64_t	time_to_eat;
	int64_t	time_to_sleep;
	int64_t	nbr_meals;
}	t_config;

typedef struct s_share
{
	pthread_mutex_t	lock_share;
	pthread_mutex_t	*forks;
	bool			did_die;
	int64_t		nbr_satisfied_philos;
	struct timeval	start;
}	t_share;

typedef struct s_philo
{
	pthread_mutex_t	lock_philo;
	int64_t		id;
	int64_t		nbr_meals;
	pthread_t		thread;
	bool			is_satisfied;
	t_share			*share;
	t_config		*config;
	struct timeval	last_meal;
}	t_philo;

bool		parse_args(t_config *config, int argc, char **argv);
bool		init_share(t_share *share, t_config *config);
void		free_forks(t_share *share, int64_t n);
t_philo		*malloc_philos(t_share *share, t_config *config);
int64_t		create_philo_threads(t_philo *philos, t_share *share, t_config *config);
void		join_philo_threads(t_philo *philos, int64_t nbr_created_threads);
void		monitor(t_philo *philos, t_share *share, t_config *config);
void		*philo_life(void *arg);
void		philo_eat(t_philo *philo);
void		update_last_meal_time(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
bool		did_philo_die(t_philo *philo);
bool		is_all_philo_satisfied(t_philo *philo);
void		print_philo_state(t_philo *philo, char *message);
int64_t		timeval_to_ms(struct timeval *t);
void		sleep_until(struct timeval *t1);
int64_t		my_min(int64_t a, int64_t b);
int64_t		my_max(int64_t a, int64_t b);
void		my_usleep(int64_t usec);

#endif
