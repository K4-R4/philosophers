/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:05:36 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/02 16:36:05 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_work(void *arg)
{
	t_philo		*philo;
	size_t		right_fork_id;
	size_t		left_fork_id;

	philo = (t_philo *)arg;
	while (true)
	{
		right_fork_id = philo->id;
		left_fork_id = (philo->id + 1) % philo->config->nbr_of_philos;
		pthread_mutex_lock(&philo->forks->mforks[my_min(right_fork_id, left_fork_id)]);
		pthread_mutex_lock(&philo->forks->mforks[my_max(right_fork_id, left_fork_id)]);
		usleep(philo->config->time_to_eat);
		printf("philo %d is eating\n", philo->id);
		pthread_mutex_unlock(&philo->forks->mforks[my_min(right_fork_id, left_fork_id)]);
		pthread_mutex_unlock(&philo->forks->mforks[my_max(right_fork_id, left_fork_id)]);
		usleep(philo->config->time_to_sleep);
		printf("philo %d is sleeping\n", philo->id);
	}
	return (NULL);
}

bool	create_philo_threads(t_philo *philos, t_config *config)
{
	size_t	i;

	i = 0;
	while (i < config->nbr_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, thread_work, &philos[i]) != 0)
			return (false);
		printf("called\n");
		i++;
	}
	return (true);
}

void	join_philo_threads(t_philo *philos, t_config *config)
{
	size_t	i;

	i = 0;
	while (i < config->nbr_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
