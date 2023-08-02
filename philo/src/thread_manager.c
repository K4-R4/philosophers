/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:05:36 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/03 08:41:45 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_philo_state(t_philo *philo, t_message_type type)
{
	struct timeval	t;

	pthread_mutex_lock(&philo->share->printable);
	gettimeofday(&t, NULL);
	printf("%lld %zu ", t.tv_sec * 1000LL + t.tv_usec / 1000LL, philo->id + 1);
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
	size_t		right_fork_id;
	size_t		left_fork_id;

	philo = (t_philo *)arg;
	while (true)
	{
		left_fork_id = philo->id;
		right_fork_id = (philo->id + 1) % philo->config->nbr_of_philos;
		printf("left %zu, right %zu\n", left_fork_id, right_fork_id);
		pthread_mutex_lock(&philo->share->forks[my_min(right_fork_id, left_fork_id)]);
		print_philo_state(philo, TAKEN_FORK);
		pthread_mutex_lock(&philo->share->forks[my_max(right_fork_id, left_fork_id)]);
		print_philo_state(philo, TAKEN_FORK);
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
	size_t	i;

	i = 0;
	while (i < config->nbr_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_life, &philos[i]) != 0)
			return (false);
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
