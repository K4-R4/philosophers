/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:40:21 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/07 22:39:17 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_eat(t_philo *philo)
{
	long long	right_fork_id;
	long long	left_fork_id;

	if (did_philo_die(philo))
		return (false);
	left_fork_id = philo->id;
	right_fork_id = (philo->id + 1) % philo->config->nbr_philos;
	pthread_mutex_lock(&philo->share->forks[my_min(right_fork_id, left_fork_id)]);
	print_philo_state(philo, M_TAKEN_FORK);
	pthread_mutex_lock(&philo->share->forks[my_max(right_fork_id, left_fork_id)]);
	print_philo_state(philo, M_TAKEN_FORK);
	update_last_meal_time(philo);
	if (did_philo_die(philo))
	{
		pthread_mutex_unlock(&philo->share->forks[my_max(right_fork_id, left_fork_id)]);
		pthread_mutex_unlock(&philo->share->forks[my_min(right_fork_id, left_fork_id)]);
		return (false);
	}
	usleep(philo->config->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->share->forks[my_max(right_fork_id, left_fork_id)]);
	pthread_mutex_unlock(&philo->share->forks[my_min(right_fork_id, left_fork_id)]);
	return (true);
}

static bool	philo_sleep(t_philo *philo)
{
	if (did_philo_die(philo))
		return (false);
	print_philo_state(philo, M_SLEEPING);
	usleep(philo->config->time_to_sleep * 1000);
	return (true);
}

static bool	philo_think(t_philo *philo)
{
	if (did_philo_die(philo))
		return (false);
	print_philo_state(philo, M_THINKING);
	return (true);
}

void	*philo_life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		if (!philo_eat(philo))
			return (NULL);
		if (!philo_sleep(philo))
			return (NULL);
		if (!philo_think(philo))
			return (NULL);
	}
	return (NULL);
}
