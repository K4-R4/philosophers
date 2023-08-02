/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:53:20 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/02 16:28:11 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_forks *forks, size_t n, bool mforks, bool bforks)
{
	if (mforks)
	{
		while (n--)
			pthread_mutex_destroy(&forks->mforks[n]);
		free(forks->mforks);
	}
	if (bforks)
		free(forks->bforks);
}

bool	init_forks(t_forks *forks, t_config *config)
{
	size_t	i;

	forks->mforks = malloc(sizeof (pthread_mutex_t) * config->nbr_of_philos);
	if (!forks->mforks)
		return (false);
	i = 0;
	while (i < config->nbr_of_philos)
	{
		if (pthread_mutex_init(&forks->mforks[i], NULL) != 0)
			break ;
		i++;
	}
	if (i < config->nbr_of_philos)
	{
		free_forks(forks, i, true, false);
		return (false);
	}
	forks->bforks = malloc(sizeof (bool) * config->nbr_of_philos);
	if (!forks->bforks)
	{
		free_forks(forks, i, true, false);
		return (false);
	}
	return (true);
}

t_philo	*malloc_philos(t_forks *forks, t_config *config)
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
		philos[i].forks = forks;
		philos[i].config = config;
		i++;
	}
	return (philos);
}
