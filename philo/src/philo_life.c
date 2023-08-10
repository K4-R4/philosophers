/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:40:21 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/10 22:38:11 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_sleep(t_philo *philo)
{
	if (did_philo_die(philo))
		return (false);
	print_philo_state(philo, M_SLEEPING);
	usleep(philo->config->time_to_sleep * 1000);
	return (true);
}

static bool	philo_think(t_philo *philo)
{
	if (did_philo_die(philo))
		return (false);
	print_philo_state(philo, M_THINKING);
	usleep(500);
	return (true);
}

void	*philo_life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		if (!philo_think(philo))
			return (NULL);
		if (!philo_eat(philo))
			return (NULL);
		if (!philo_sleep(philo))
			return (NULL);
	}
	return (NULL);
}
