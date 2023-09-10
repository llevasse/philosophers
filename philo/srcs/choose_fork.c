/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:34:10 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/10 15:57:17 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	choose_higher(t_philo *buddy, long long time)
{
	while (buddy->right_buddy->fork.__data.__lock == 1)
	{
		usleep(5);
		if (!check_death(buddy, time))
			return (0);
	}
	pthread_mutex_lock(&buddy->right_buddy->fork);
	print_take_fork(buddy, time);
	while (buddy->fork.__data.__lock == 1)
	{
		usleep(5);
		if (!check_death(buddy, time))
			return ((void)pthread_mutex_unlock(&buddy->right_buddy->fork), 0);
	}
	pthread_mutex_lock(&buddy->fork);
	print_take_fork(buddy, time);
	return (1);
}

int	choose_fork(t_philo *buddy, long long time)
{
	if (buddy->id < buddy->right_buddy->id)
		return (choose_higher(buddy, time));
	while (buddy->fork.__data.__lock == 1)
	{
		usleep(5);
		if (!check_death(buddy, time))
			return (0);
	}
	pthread_mutex_lock(&buddy->fork);
	print_take_fork(buddy, time);
	while (buddy->right_buddy->fork.__data.__lock == 1)
	{
		usleep(5);
		if (!check_death(buddy, time))
			return ((void)pthread_mutex_unlock(&buddy->fork), 0);
	}
	pthread_mutex_lock(&buddy->right_buddy->fork);
	print_take_fork(buddy, time);
	return (1);
}
