/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:44:56 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/12 09:07:06 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timeval_to_ms(struct timeval *t)
{
	return (t->tv_sec * 1000LL + t->tv_usec / 1000LL);
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
