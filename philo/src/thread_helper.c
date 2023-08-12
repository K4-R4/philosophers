/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:53:02 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 17:13:48 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	did_any_philo_die(t_philo *philo,
		t_share *share, t_config *config)
{
	struct timeval	t;
	long long		cur_ms;
	long long		last_meal_ms;

	gettimeofday(&t, NULL);
	cur_ms = timeval_to_ms(&t) - timeval_to_ms(&share->start);
	pthread_mutex_lock(&philo->lock_philo);
	last_meal_ms = timeval_to_ms(&philo->last_meal)
		- timeval_to_ms(&share->start);
	if (cur_ms - last_meal_ms >= config->time_to_die)
	{
		print_philo_state(philo, M_DIED);
		pthread_mutex_lock(&share->lock_share);
		share->did_die = true;
		pthread_mutex_unlock(&share->lock_share);
		pthread_mutex_unlock(&philo->lock_philo);
		return (true);
	}
	pthread_mutex_unlock(&philo->lock_philo);
	return (false);
}

void	monitor(t_philo *philos, t_share *share, t_config *config)
{
	long long	i;

	while (true)
	{
		i = 0;
		while (i < config->nbr_philos)
		{
			if (did_any_philo_die(&philos[i], share, config))
				return ;
			if (is_all_philo_satisfied(&philos[i]))
				return ;
			i++;
		}
	}
}
