/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:40:21 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 11:02:29 by tkuramot         ###   ########.fr       */
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
		if (did_philo_die(philo))
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

void	print_philo_state(t_philo *philo, char *message)
{
	struct timeval	t;

	pthread_mutex_lock(&philo->share->lock_print);
	if (did_philo_die(philo))
	{
		pthread_mutex_unlock(&philo->share->lock_print);
		return ;
	}
	gettimeofday(&t, NULL);
	printf("%lld %lld ", timeval_to_ms(&t)
		- timeval_to_ms(&philo->share->start), philo->id + 1);
	printf("%s", message);
	pthread_mutex_unlock(&philo->share->lock_print);
}
