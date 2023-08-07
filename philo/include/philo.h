/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:26:20 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/07 20:12:44 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define M_TAKEN_FORK "has taken a fork\n"
#define M_EATING "is eating\n"
#define M_SLEEPING "is sleeping\n"
#define M_THINKING "is thinking\n"
#define M_DIED "died\n"

typedef struct	s_config
{
	long long	nbr_philos;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	nbr_of_meals;
}				t_config;

typedef struct	s_share
{
	pthread_mutex_t	printable;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_did_die;
	bool			did_die;
	long long		nbr_satisfied_philos;
	struct timeval	start;
}				t_share;

typedef struct	s_philo
{
	long long			id;
	long long			nbr_meals;
	pthread_t		thread;
	t_share			*share;
	t_config		*config;
	pthread_mutex_t	lock_last_meal;
	struct timeval	last_meal;
}				t_philo;

bool	parse_args(t_config *config, int argc, char **argv);
bool	init_share(t_share *share, t_config *config);
void	free_share(t_share *share, long long n);
t_philo	*malloc_philos(t_share *share, t_config *config);
bool	create_philo_threads(t_philo *philos, t_config *config);;
void	join_philo_threads(t_philo *philos, t_config *config);
void	monitor(t_philo *philos, t_share *share, t_config *config);
int		ft_atoi(const char *str);
long long	my_min(long long a, long long b);
long long	my_max(long long a, long long b);

#endif
