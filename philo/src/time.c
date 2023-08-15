/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:44:56 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/15 22:10:17 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	timeval_to_ms(struct timeval *t)
{
	return (t->tv_sec * 1000LL + t->tv_usec / 1000LL);
}

static int64_t	timeval_to_microsec(struct timeval *t)
{
	return (t->tv_sec * 1000000LL + t->tv_usec);
}

void	sleep_until(struct timeval *t1)
{
	struct timeval	t2;

	while (true)
	{
		gettimeofday(&t2, NULL);
		if (timeval_to_microsec(t1) - timeval_to_microsec(&t2) < 0)
			break ;
	}
}

void	my_usleep(int64_t usec)
{
	struct timeval	t1;
	struct timeval	t2;

	gettimeofday(&t1, NULL);
	while (true)
	{
		gettimeofday(&t2, NULL);
		if (timeval_to_microsec(&t2) - timeval_to_microsec(&t1) >= usec)
			return ;
	}
}
