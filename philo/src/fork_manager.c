/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:53:20 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/02 14:11:18 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_forks(t_status *status, t_config *config)
{
	size_t	i;

	status->forks = malloc(sizeof (pthread_mutex_t) * config->nbr_of_philos);
	if (!status->forks)
		return (false);
	i = 0;
	while (i < config->nbr_of_philos)
	{
		if (pthread_mutex_init(&status->forks[i], NULL) != 0)
			break ;
		i++;
	}
	if (i < config->nbr_of_philos)
	{
		while (i--)
			pthread_mutex_destroy(&status->forks[i]);
		return (false);
	}
	return (true);
}
