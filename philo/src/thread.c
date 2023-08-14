/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:05:36 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/14 21:06:48 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	create_philo_threads(t_philo *philos, t_config *config)
{
	int64_t	i;

	i = 0;
	while (i < config->nbr_philos)
	{
		gettimeofday(&philos[i].last_meal, NULL);
		if (pthread_create(&philos[i].thread, NULL,
				philo_life, &philos[i]) != 0)
			return (i);
		i++;
	}
	return (i);
}

void	detach_philo_threads(t_philo *philos, t_config *config)
{
	int64_t	i;

	i = 0;
	while (i < config->nbr_philos)
	{
		pthread_detach(philos[i].thread);
		i++;
	}
}

void	join_philo_threads(t_philo *philos, int64_t nbr_created_threads)
{
	int64_t	i;

	i = 0;
	while (i < nbr_created_threads)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
