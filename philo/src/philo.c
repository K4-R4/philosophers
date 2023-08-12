/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:40:21 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 11:50:08 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(t_philo *philo)
{
	print_philo_state(philo, M_SLEEPING);
	my_usleep(philo->config->time_to_sleep * 1000);
}

static void	philo_think(t_philo *philo)
{
	print_philo_state(philo, M_THINKING);
	my_usleep(500);
}

void	*philo_life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
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
	pthread_mutex_lock(&philo->share->lock_did_die);
	if (philo->share->did_die)
	{
		pthread_mutex_unlock(&philo->share->lock_did_die);
		return (true);
	}
	pthread_mutex_unlock(&philo->share->lock_did_die);
	return (false);
}

bool	is_all_philo_satisfied(t_philo *philo)
{
	pthread_mutex_lock(&philo->share->lock_nbr_satisfied_philos);
	if (philo->share->nbr_satisfied_philos >= philo->config->nbr_philos)
	{
		pthread_mutex_unlock(&philo->share->lock_nbr_satisfied_philos);
		return (true);
	}
	pthread_mutex_unlock(&philo->share->lock_nbr_satisfied_philos);
	return (false);
}
