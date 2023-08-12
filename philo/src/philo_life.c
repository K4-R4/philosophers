/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:40:21 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 09:51:04 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(t_philo *philo)
{
	print_philo_state(philo, M_SLEEPING);
	my_usleep(philo->config->time_to_sleep * 1000);
}

static void	philo_think(t_philo *philo)
{
	print_philo_state(philo, M_THINKING);
	my_usleep(500);
}

void	*philo_life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		if (did_philo_die(philo))
			return (NULL);
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
