/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:26:20 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/04 01:06:38 by tkuramot         ###   ########.fr       */
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

typedef enum	e_message_type
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}				t_message_type;

typedef struct	s_config
{
	size_t	nbr_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	nbr_of_meals;
}				t_config;

typedef struct	s_share
{
	pthread_mutex_t	printable;
	pthread_mutex_t	*forks;
}				t_share;

typedef struct	s_philo
{
	size_t			id;
	size_t			nbr_of_meals;
	pthread_t		thread;
	t_share			*share;
	t_config		*config;
	struct timeval	birth;
	struct timeval	last_meal;
}				t_philo;

bool	parse_args(t_config *config, int argc, char **argv);
bool	init_share(t_share *share, t_config *config);
void	free_share(t_share *share, size_t n);
t_philo	*malloc_philos(t_share *share, t_config *config);
bool	create_philo_threads(t_philo *philos, t_config *config);;
void	join_philo_threads(t_philo *philos, t_config *config);
int		ft_atoi(const char *str);
size_t	my_min(size_t a, size_t b);
size_t	my_max(size_t a, size_t b);

#endif
