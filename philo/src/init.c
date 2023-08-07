/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:53:20 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/07 20:28:27 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_share *share, long long n)
{
	if (share)
	{
		while (n--)
			pthread_mutex_destroy(&share->forks[n]);
		free(share->forks);
	}
}

bool	init_share(t_share *share, t_config *config)
{
	long long	i;

	gettimeofday(&share->start, NULL);
	if (pthread_mutex_init(&share->printable, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&share->lock_did_die, NULL) != 0)
		return (false);
	share->did_die = false;
	share->forks = malloc(sizeof (pthread_mutex_t) * config->nbr_philos);
	if (!share->forks)
		return (false);
	i = 0;
	while (i < config->nbr_philos)
	{
		if (pthread_mutex_init(&share->forks[i], NULL) != 0)
			break ;
		i++;
	}
	if (i < config->nbr_philos)
	{
		free_forks(share, i);
		return (false);
	}
	return (true);
}

t_philo	*malloc_philos(t_share *share, t_config *config)
{
	t_philo		*philos;
	long long		i;

	philos = malloc(sizeof (t_philo) * config->nbr_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < config->nbr_philos)
	{
		philos[i].id = i;
		philos[i].share = share;
		philos[i].config = config;
		if (pthread_mutex_init(&philos[i].lock_last_meal, NULL) != 0)
		{
			free(philos);
			return (NULL);
		}
		i++;
	}
	return (philos);
}
