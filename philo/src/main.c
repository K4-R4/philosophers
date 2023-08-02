/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:26:02 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/02 16:23:08 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		main(int argc, char **argv)
{
	t_config	config;
	t_forks		forks;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	if (!parse_args(&config, argc, argv))
		return (EXIT_FAILURE);
	if (!init_forks(&forks, &config))
		return (EXIT_FAILURE);
	philos = malloc_philos(&forks, &config);
	if (!philos)
		return (EXIT_FAILURE);
	create_philo_threads(philos, &config);
	join_philo_threads(philos, &config);
	return (EXIT_SUCCESS);
}
