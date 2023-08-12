/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:26:02 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 13:03:08 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

__attribute__((destructor))
static void destructor() {
    system("leaks -q philo");
}

void	free_all(t_philo *philos, t_share *share)
{
	free(philos);
	free(share->forks);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_share		share;
	t_philo		*philos;

	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	if (!parse_args(&config, argc, argv))
		return (EXIT_FAILURE);
	if (!init_share(&share, &config))
		return (EXIT_FAILURE);
	philos = malloc_philos(&share, &config);
	if (!philos)
		return (EXIT_FAILURE);
	if (!create_philo_threads(philos, &config))
		return (EXIT_FAILURE);
	monitor(philos, &share, &config);
	if (config.nbr_philos == 1)
		detach_philo_threads(philos, &config);
	else
		join_philo_threads(philos, &config);
	free_all(philos, &share);
	return (EXIT_SUCCESS);
}
