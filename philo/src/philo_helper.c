/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:42:57 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 11:41:40 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_last_meal);
	gettimeofday(&philo->last_meal, NULL);
	print_philo_state(philo, M_EATING);
	pthread_mutex_unlock(&philo->lock_last_meal);
}

static void	pick_up_forks(t_philo *philo, long long r_fork, long long l_fork)
{
	pthread_mutex_lock(&philo->share->forks[my_min(r_fork, l_fork)]);
	print_philo_state(philo, M_TAKEN_FORK);
	pthread_mutex_lock(&philo->share->forks[my_max(r_fork, l_fork)]);
	print_philo_state(philo, M_TAKEN_FORK);
}

static void	drop_forks(t_philo *philo, long long r_fork, long long l_fork)
{
	pthread_mutex_unlock(&philo->share->forks[my_max(r_fork, l_fork)]);
	pthread_mutex_unlock(&philo->share->forks[my_min(r_fork, l_fork)]);
}

void	philo_eat(t_philo *philo)
{
	long long	r_fork;
	long long	l_fork;

	l_fork = philo->id;
	r_fork = (philo->id + 1) % philo->config->nbr_philos;
	pick_up_forks(philo, r_fork, l_fork);
	update_last_meal_time(philo);
	my_usleep(philo->config->time_to_eat * 1000);
	drop_forks(philo, r_fork, l_fork);
	philo->nbr_meals++;
	if (philo->nbr_meals >= philo->config->nbr_meals)
	{
		pthread_mutex_lock(&philo->share->lock_nbr_satisfied_philos);
		if (!philo->is_satisfied)
			philo->share->nbr_satisfied_philos++;
		philo->is_satisfied = true;
		pthread_mutex_unlock(&philo->share->lock_nbr_satisfied_philos);
	}
	pthread_mutex_lock(&philo->share->lock_nbr_satisfied_philos);
	pthread_mutex_unlock(&philo->share->lock_nbr_satisfied_philos);
}
