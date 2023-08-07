/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:42:57 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/07 21:43:17 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	did_philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->share->lock_did_die);
	if (philo->share->did_die)
	{
		pthread_mutex_unlock(&philo->share->lock_did_die);
		return (true);
	}
	pthread_mutex_unlock(&philo->share->lock_did_die);
	return (false);
}

void	print_philo_state(t_philo *philo, char *message)
{
	struct timeval	t;

	if (did_philo_die(philo))
		return ;
	pthread_mutex_lock(&philo->share->printable);
	gettimeofday(&t, NULL);
	printf("%lld %lld ", timeval_to_ms(&t) - timeval_to_ms(&philo->share->start), philo->id + 1);
	printf("%s", message);
	pthread_mutex_unlock(&philo->share->printable);
}
