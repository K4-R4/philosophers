/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:44:42 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 11:51:40 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_state(t_philo *philo, char *message)
{
	struct timeval	t;

	pthread_mutex_lock(&philo->share->lock_print);
	if (did_philo_die(philo) || is_all_philo_satisfied(philo))
	{
		pthread_mutex_unlock(&philo->share->lock_print);
		return ;
	}
	gettimeofday(&t, NULL);
	printf("%lld %lld ", timeval_to_ms(&t)
		- timeval_to_ms(&philo->share->start), philo->id + 1);
	printf("%s", message);
	pthread_mutex_unlock(&philo->share->lock_print);
}

long long	my_min(long long a, long long b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

long long	my_max(long long a, long long b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
