/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:32:39 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/14 21:07:01 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_valid_number(char *s)
{
	if (*s == '0')
		return (false);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (false);
		s++;
	}
	return (true);
}

static bool	do_overflow(int n, int ones_place)
{
	if (n > 0 && ones_place > INT_MAX - n * 10)
		return (true);
	return (false);
}

static bool	ascii_to_positive(int64_t *n, char *s)
{
	if (!is_valid_number(s))
		return (false);
	*n = 0;
	while (*s)
	{
		if (do_overflow(*n, *s - '0'))
			return (false);
		*n = *n * 10 + (*s - '0');
		s++;
	}
	return (true);
}

bool	parse_args(t_config *config, int argc, char **argv)
{
	if (!ascii_to_positive(&config->nbr_philos, argv[1]))
		return (false);
	if (!ascii_to_positive(&config->time_to_die, argv[2]))
		return (false);
	if (!ascii_to_positive(&config->time_to_eat, argv[3]))
		return (false);
	if (!ascii_to_positive(&config->time_to_sleep, argv[4]))
		return (false);
	if (argc == 5)
		config->nbr_meals = -1;
	if (argc == 6)
		if (!ascii_to_positive(&config->nbr_meals, argv[5]))
			return (false);
	return (true);
}
