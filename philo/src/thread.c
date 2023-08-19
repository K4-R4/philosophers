/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:05:36 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/19 12:38:02 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int64_t	create_odd_threads(t_philo *philos,
		t_share *share, t_config *config)
{
	int64_t	i;
	int64_t	philo_id;

	i = 0;
	philo_id = 0;
	while (i < config->nbr_philos)
	{
		philo_id = philo_id % config->nbr_philos;
		philos[philo_id].last_meal = share->start;
		philos[philo_id].next_meal = share->start;
		philos[philo_id].next_meal.tv_usec
			+= (config->time_to_eat / 2 * 1000) * i;
		if (pthread_create(&philos[philo_id].thread, NULL,
				philo_life, &philos[philo_id]) != 0)
			return (i);
		philo_id += 2;
		i++;
	}
	return (i);
}

static int64_t	create_even_threads(t_philo *philos,
		t_share *share, t_config *config)
{
	int64_t	i;

	i = 0;
	while (i < config->nbr_philos)
	{
		philos[i].last_meal = share->start;
		philos[i].next_meal = share->start;
		if (i % 2 == 1)
			philos[i].next_meal.tv_usec += (config->time_to_eat / 2 * 1000);
		if (pthread_create(&philos[i].thread, NULL,
				philo_life, &philos[i]) != 0)
			return (i);
		i++;
	}
	return (i);
}

int64_t	create_philo_threads(t_philo *philos, t_share *share, t_config *config)
{
	int64_t	i;

	gettimeofday(&share->start, NULL);
	share->start.tv_sec++;
	i = 0;
	if (config->nbr_philos % 2 == 1)
		i = create_odd_threads(philos, share, config);
	else
		i = create_even_threads(philos, share, config);
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
