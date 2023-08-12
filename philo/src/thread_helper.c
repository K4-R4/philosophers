/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:53:02 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 11:04:51 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	monitor_philo_starvation(t_philo *philo,
		t_share *share, t_config *config)
{
	struct timeval	t;
	long long		cur_ms;
	long long		last_meal_ms;

	gettimeofday(&t, NULL);
	cur_ms = timeval_to_ms(&t) - timeval_to_ms(&share->start);
	pthread_mutex_lock(&philo->lock_last_meal);
	last_meal_ms = timeval_to_ms(&philo->last_meal)
		- timeval_to_ms(&share->start);
	if (cur_ms - last_meal_ms >= config->time_to_die)
	{
		print_philo_state(philo, M_DIED);
		pthread_mutex_lock(&share->lock_did_die);
		share->did_die = true;
		pthread_mutex_unlock(&share->lock_did_die);
		pthread_mutex_unlock(&philo->lock_last_meal);
		return (false);
	}
	pthread_mutex_unlock(&philo->lock_last_meal);
	return (true);
}

static bool	monitor_philo_satisfication(t_share *share, t_config *config)
{
	pthread_mutex_lock(&share->lock_nbr_satisfied_philos);
	if (share->nbr_satisfied_philos >= config->nbr_philos)
	{
		pthread_mutex_unlock(&share->lock_nbr_satisfied_philos);
		return (false);
	}
	pthread_mutex_unlock(&share->lock_nbr_satisfied_philos);
	return (true);
}

void	monitor(t_philo *philos, t_share *share, t_config *config)
{
	long long	i;

	while (true)
	{
		i = 0;
		while (i < config->nbr_philos)
		{
			if (!monitor_philo_starvation(&philos[i], share, config))
				return ;
			if (!monitor_philo_satisfication(share, config))
				return ;
			i++;
		}
	}
}
