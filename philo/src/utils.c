/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:44:56 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 09:50:35 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timeval_to_ms(struct timeval *t)
{
	return (t->tv_sec * 1000LL + t->tv_usec / 1000LL);
}

long long	timeval_to_micro(struct timeval *t)
{
	return (t->tv_sec * 1000000LL + t->tv_usec);
}

void	my_usleep(long long usec)
{
	struct timeval	t1;
	struct timeval	t2;

	gettimeofday(&t1, NULL);
	while (true)
	{
		gettimeofday(&t2, NULL);
		if (timeval_to_micro(&t2) - timeval_to_micro(&t1) >= usec)
			return ;
	}
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
