/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:26:02 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/19 10:12:16 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philos, t_share *share)
{
	free_forks(share, philos[0].config->nbr_philos);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_share		share;
	t_philo		*philos;
	int64_t		nbr_created_threads;

	if ((argc != 5 && argc != 6) || !parse_args(&config, argc, argv)
		|| !init_share(&share, &config))
		return (EXIT_FAILURE);
	philos = malloc_philos(&share, &config);
	if (!philos)
		return (EXIT_FAILURE);
	nbr_created_threads = create_philo_threads(philos, &share, &config);
	if (nbr_created_threads != config.nbr_philos)
	{
		pthread_mutex_lock(&share.lock_share);
		share.did_die = true;
		pthread_mutex_unlock(&share.lock_share);
	}
	monitor(philos, &share, &config);
	join_philo_threads(philos, nbr_created_threads);
	free_all(philos, &share);
	return (EXIT_SUCCESS);
}
