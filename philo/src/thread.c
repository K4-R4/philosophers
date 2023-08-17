/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:05:36 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/17 12:52:09 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Set starting time of the simulation
int64_t	create_philo_threads(t_philo *philos, t_share *share, t_config *config)
{
	int64_t	i;

	i = 0;
	gettimeofday(&share->start, NULL);
	share->start.tv_sec++;
	while (i < config->nbr_philos)
	{
		philos[i].last_meal = share->start;
		if (pthread_create(&philos[i].thread, NULL,
				philo_life, &philos[i]) != 0)
			return (i);
		i++;
	}
	return (i);
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
