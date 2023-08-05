/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:05:36 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/05 10:20:57 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_philo_state(t_philo *philo, t_message_type type)
{
	struct timeval	t;

	pthread_mutex_lock(&philo->share->printable);
	gettimeofday(&t, NULL);
	printf("%lld %lld ", t.tv_sec * 1000LL + t.tv_usec / 1000LL, philo->id + 1);
	if (type == TAKEN_FORK)
		printf("has taken a fork\n");
	if (type == EATING)
		printf("is eating\n");
	if (type == SLEEPING)
		printf("is sleeping\n");
	if (type == THINKING)
		printf("is thinking\n");
	if (type == DIED)
		printf("died\n");
	pthread_mutex_unlock(&philo->share->printable);
}

static void	*philo_life(void *arg)
{
	t_philo		*philo;
	long long		right_fork_id;
	long long		left_fork_id;

	philo = (t_philo *)arg;
	while (true)
	{
		left_fork_id = philo->id;
		right_fork_id = (philo->id + 1) % philo->config->nbr_philos;
		pthread_mutex_lock(&philo->share->forks[my_min(right_fork_id, left_fork_id)]);
		print_philo_state(philo, TAKEN_FORK);
		pthread_mutex_lock(&philo->share->forks[my_max(right_fork_id, left_fork_id)]);
		print_philo_state(philo, TAKEN_FORK);
		gettimeofday(&philo->last_meal, NULL);
		print_philo_state(philo, EATING);
		usleep(philo->config->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->share->forks[my_min(right_fork_id, left_fork_id)]);
		pthread_mutex_unlock(&philo->share->forks[my_max(right_fork_id, left_fork_id)]);
		print_philo_state(philo, SLEEPING);
		usleep(philo->config->time_to_sleep * 1000);
		print_philo_state(philo, THINKING);
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

void	detach_philo_threads(t_philo *philos, t_config *config)
{
	long long	i;

	i = 0;
	while (i < config->nbr_philos)
	{
		pthread_detach(philos[i].thread);
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
			cur_ms = t.tv_sec * 1000LL + t.tv_usec / 1000LL;
			last_meal_ms = philos[i].last_meal.tv_sec * 1000LL
				+ philos->last_meal.tv_usec / 1000LL;
			if (cur_ms - last_meal_ms >= config->time_to_die)
			{
				share->did_die = true;
				print_philo_state(&philos[i], DIED);
				return ;
			}
			i++;
		}
	}
}
