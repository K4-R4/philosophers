/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:26:20 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/02 16:23:24 by tkuramot         ###   ########.fr       */
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

typedef struct	s_config
{
	size_t			nbr_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			nbr_of_meals;
}				t_config;

typedef struct	s_forks
{
	pthread_mutex_t	*mforks;
	bool			*bforks;
}				t_forks;

typedef struct	s_philo
{
	int			id;
	pthread_t	thread;
	t_forks		*forks;
	t_config	*config;
}				t_philo;

bool	parse_args(t_config *config, int argc, char **argv);
bool	init_forks(t_forks *forks, t_config *config);
void	free_forks(t_forks *forks, size_t n, bool mforks, bool bforks);
bool	create_philo_threads(t_philo *philos, t_config *config);;
void	join_philo_threads(t_philo *philos, t_config *config);
t_philo	*malloc_philos(t_forks *forks, t_config *config);
int		ft_atoi(const char *str);
size_t	my_min(size_t a, size_t b);
size_t	my_max(size_t a, size_t b);

#endif
