/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:53:20 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/02 18:00:54 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_share *share, size_t n)
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
	size_t	i;

	share->forks = malloc(sizeof (pthread_mutex_t) * config->nbr_of_philos);
	if (!share->forks)
		return (false);
	i = 0;
	while (i < config->nbr_of_philos)
	{
		if (pthread_mutex_init(&share->forks[i], NULL) != 0)
			break ;
		i++;
	}
	if (i < config->nbr_of_philos)
	{
		free_forks(share, i);
		return (false);
	}
	return (true);
}

t_philo	*malloc_philos(t_share *share, t_config *config)
{
	t_philo		*philos;
	size_t		i;

	philos = malloc(sizeof (t_philo) * config->nbr_of_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < config->nbr_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].share = share;
		philos[i].config = config;
		i++;
	}
	return (philos);
}
