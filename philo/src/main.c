/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:26:02 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/02 20:42:49 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		main(int argc, char **argv)
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
	create_philo_threads(philos, &config);
	join_philo_threads(philos, &config);
	return (EXIT_SUCCESS);
}
