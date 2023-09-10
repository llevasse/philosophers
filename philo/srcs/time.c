/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:02:56 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/10 18:39:59 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timestamp(struct timeval tv)
{
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_time(t_philo *buddy, long wait_time, long long time)
{
	while (timestamp(buddy->curr_time) < wait_time && \
			check_death(buddy, time))
		usleep(10);
}
