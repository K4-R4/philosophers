/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:26:02 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/02 14:14:31 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		main(int argc, char **argv)
{
	t_config	config;
	t_status	status;

	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	if (!parse_args(&config, argc, argv))
		return (EXIT_FAILURE);
	if (!init_forks(&status, &config))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
