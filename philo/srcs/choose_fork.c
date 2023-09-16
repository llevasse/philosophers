/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:34:10 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/16 17:37:54 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	choose_higher(t_philo *buddy)
{
	while (buddy->right_buddy->fork.__data.__lock == 1)
	{
		continue ;
	//	usleep(10);
	//	if (!check_death(buddy, time, 0))
	//		return (0);
	}
	pthread_mutex_lock(&buddy->right_buddy->fork);
	print_fork(buddy, "has taken a fork", buddy->right_buddy->id);
	while (buddy->fork.__data.__lock == 1)
	{
		continue ;
	//	usleep(10);
	//	if (!check_death(buddy, time, 0))
	//		return ((void)pthread_mutex_unlock(&buddy->right_buddy->fork), 0);
	}
	pthread_mutex_lock(&buddy->fork);
	print_fork(buddy, "has taken a fork", buddy->id);
	return (1);
}

int	choose_fork(t_philo *buddy)
{
	if (buddy->id < buddy->right_buddy->id)
		return (choose_higher(buddy));
	while (buddy->fork.__data.__lock == 1)
	{
		continue ;
	//	usleep(10);
	//	if (!check_death(buddy, time, 0))
	//		return (0);
	}
	pthread_mutex_lock(&buddy->fork);
	print_fork(buddy, "has taken a fork", buddy->id);
	while (buddy->right_buddy->fork.__data.__lock == 1)
	{
		continue ;
	//	usleep(10);
	//	if (!check_death(buddy, time, 0))
	//		return ((void)pthread_mutex_unlock(&buddy->fork), 0);
	}
	pthread_mutex_lock(&buddy->right_buddy->fork);
	print_fork(buddy, "has taken a fork", buddy->right_buddy->id);
	return (1);
}
