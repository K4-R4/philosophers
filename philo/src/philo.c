/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:40:21 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/19 10:44:51 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	sleep_until(&philo->share->start);
	while (true)
	{
		if (did_philo_die(philo) || is_all_philo_satisfied(philo))
			return (NULL);
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

bool	did_philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->share->lock_share);
	if (philo->share->did_die)
	{
		pthread_mutex_unlock(&philo->share->lock_share);
		return (true);
	}
	pthread_mutex_unlock(&philo->share->lock_share);
	return (false);
}

bool	is_all_philo_satisfied(t_philo *philo)
{
	pthread_mutex_lock(&philo->share->lock_share);
	if (philo->share->nbr_satisfied_philos >= philo->config->nbr_philos)
	{
		pthread_mutex_unlock(&philo->share->lock_share);
		return (true);
	}
	pthread_mutex_unlock(&philo->share->lock_share);
	return (false);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_philo);
	gettimeofday(&philo->last_meal, NULL);
	print_philo_state(philo, M_EATING);
	pthread_mutex_unlock(&philo->lock_philo);
}
