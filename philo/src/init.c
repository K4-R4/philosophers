/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:53:20 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/15 22:12:28 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_share *share, int64_t n)
{
	while (n--)
		pthread_mutex_destroy(&share->forks[n]);
	free(share->forks);
}

static bool	init_share_helper(t_share *share)
{
	if (pthread_mutex_init(&share->lock_share, NULL) != 0)
		return (false);
	share->nbr_satisfied_philos = 0;
	share->did_die = false;
	return (true);
}

bool	init_share(t_share *share, t_config *config)
{
	int64_t	i;

	init_share_helper(share);
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
	int64_t	i;

	philos = malloc(sizeof (t_philo) * config->nbr_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < config->nbr_philos)
	{
		philos[i].id = i;
		philos[i].share = share;
		philos[i].config = config;
		philos[i].nbr_meals = 0;
		philos[i].is_satisfied = false;
		if (pthread_mutex_init(&philos[i].lock_philo, NULL) != 0)
		{
			free(philos);
			return (NULL);
		}
		i++;
	}
	return (philos);
}
