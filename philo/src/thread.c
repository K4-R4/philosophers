/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:05:36 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 11:03:27 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	create_philo_threads(t_philo *philos, t_config *config)
{
	long long	i;

	i = 0;
	while (i < config->nbr_philos)
	{
		gettimeofday(&philos[i].last_meal, NULL);
		if (pthread_create(&philos[i].thread, NULL,
				philo_life, &philos[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}

void	join_philo_threads(t_philo *philos, t_config *config)
{
	long long	i;

	i = 0;
	while (i < config->nbr_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
