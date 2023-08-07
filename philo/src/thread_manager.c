/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:05:36 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/07 20:34:26 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static long long	timeval_to_ms(struct timeval *t)
{
	return (t->tv_sec * 1000LL + t->tv_usec / 1000LL);
}

static void	print_philo_state(t_philo *philo, char *message)
{
	struct timeval	t;

	pthread_mutex_lock(&philo->share->lock_did_die);
	if (philo->share->did_die)
	{
		pthread_mutex_unlock(&philo->share->lock_did_die);
		return ;
	}
	pthread_mutex_unlock(&philo->share->lock_did_die);
	pthread_mutex_lock(&philo->share->printable);
	gettimeofday(&t, NULL);
	printf("%lld %lld ", timeval_to_ms(&t) - timeval_to_ms(&philo->share->start), philo->id + 1);
	printf("%s", message);
	pthread_mutex_unlock(&philo->share->printable);
}

static void	*philo_life(void *arg)
{
	t_philo		*philo;
	long long	right_fork_id;
	long long	left_fork_id;

	philo = (t_philo *)arg;
	left_fork_id = philo->id;
	right_fork_id = (philo->id + 1) % philo->config->nbr_philos;
	while (true)
	{
		pthread_mutex_lock(&philo->share->lock_did_die);
		if (philo->share->did_die)
		{
			pthread_mutex_unlock(&philo->share->lock_did_die);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->share->lock_did_die);
		pthread_mutex_lock(&philo->share->forks[my_min(right_fork_id, left_fork_id)]);
		print_philo_state(philo, M_TAKEN_FORK);
		pthread_mutex_lock(&philo->share->forks[my_max(right_fork_id, left_fork_id)]);
		print_philo_state(philo, M_TAKEN_FORK);
		pthread_mutex_lock(&philo->lock_last_meal);
		gettimeofday(&philo->last_meal, NULL);
		print_philo_state(philo, M_EATING);
		pthread_mutex_unlock(&philo->lock_last_meal);
		usleep(philo->config->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->share->forks[my_min(right_fork_id, left_fork_id)]);
		pthread_mutex_unlock(&philo->share->forks[my_max(right_fork_id, left_fork_id)]);
		print_philo_state(philo, M_SLEEPING);
		usleep(philo->config->time_to_sleep * 1000);
		print_philo_state(philo, M_THINKING);
	}
	return (NULL);
}

bool	create_philo_threads(t_philo *philos, t_config *config)
{
	long long	i;

	i = 0;
	while (i < config->nbr_philos)
	{
		gettimeofday(&philos[i].last_meal, NULL);
		if (pthread_create(&philos[i].thread, NULL, philo_life, &philos[i]) != 0)
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

void	monitor(t_philo *philos, t_share *share, t_config *config)
{
	long long i;
	struct timeval	t;
	long long		cur_ms;
	long long		last_meal_ms;

	while (true)
	{
		i = 0;
		while (i < config->nbr_philos)
		{
			gettimeofday(&t, NULL);
			cur_ms = timeval_to_ms(&t) - timeval_to_ms(&share->start);
			pthread_mutex_lock(&philos[i].lock_last_meal);
			last_meal_ms = timeval_to_ms(&philos[i].last_meal) - timeval_to_ms(&share->start);
			if (cur_ms - last_meal_ms >= config->time_to_die)
			{
				print_philo_state(&philos[i], M_DIED);
				pthread_mutex_lock(&share->lock_did_die);
				share->did_die = true;
				pthread_mutex_unlock(&share->lock_did_die);
				pthread_mutex_unlock(&philos[i].lock_last_meal);
				return ;
			}
			pthread_mutex_unlock(&philos[i].lock_last_meal);
			i++;
		}
	}
}
