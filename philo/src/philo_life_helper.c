/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:42:57 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 09:52:20 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pick_up_forks(t_philo *philo, long long right_fork_id, long long left_fork_id)
{
	pthread_mutex_lock(&philo->share->forks[my_min(right_fork_id, left_fork_id)]);
	print_philo_state(philo, M_TAKEN_FORK);
	pthread_mutex_lock(&philo->share->forks[my_max(right_fork_id, left_fork_id)]);
	print_philo_state(philo, M_TAKEN_FORK);
}

static void	drop_forks(t_philo *philo, long long right_fork_id, long long left_fork_id)
{
	pthread_mutex_unlock(&philo->share->forks[my_max(right_fork_id, left_fork_id)]);
	pthread_mutex_unlock(&philo->share->forks[my_min(right_fork_id, left_fork_id)]);
}

void	philo_eat(t_philo *philo)
{
	long long	right_fork_id;
	long long	left_fork_id;

	left_fork_id = philo->id;
	right_fork_id = (philo->id + 1) % philo->config->nbr_philos;
	pick_up_forks(philo, right_fork_id, left_fork_id);
	update_last_meal_time(philo);
	my_usleep(philo->config->time_to_eat * 1000);
	drop_forks(philo, right_fork_id, left_fork_id);
	philo->nbr_meals++;
	pthread_mutex_lock(&philo->share->lock_nbr_of_satisfied_philos);
	pthread_mutex_unlock(&philo->share->lock_nbr_of_satisfied_philos);
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

	pthread_mutex_lock(&philo->share->printable);
	if (did_philo_die(philo))
	{
		pthread_mutex_unlock(&philo->share->printable);
		return ;
	}
	gettimeofday(&t, NULL);
	printf("%lld %lld ", timeval_to_ms(&t) - timeval_to_ms(&philo->share->start), philo->id + 1);
	printf("%s", message);
	pthread_mutex_unlock(&philo->share->printable);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_last_meal);
	gettimeofday(&philo->last_meal, NULL);
	print_philo_state(philo, M_EATING);
	pthread_mutex_unlock(&philo->lock_last_meal);
}
