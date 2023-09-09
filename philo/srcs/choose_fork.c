/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:34:10 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/09 21:35:19 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	choose_higher(t_philo *buddy, long long time)
{
	while (buddy->right_buddy->fork.__data.__lock == 1)
	{
		if (!check_death(buddy, time))
			return ;
	}
	pthread_mutex_lock(&buddy->right_buddy->fork);
	print_take_fork(buddy, time);
	while (buddy->fork.__data.__lock == 1)
	{
		if (!check_death(buddy, time))
			return ((void)pthread_mutex_unlock(&buddy->right_buddy->fork));
	}
	pthread_mutex_lock(&buddy->fork);
	print_take_fork(buddy, time);
}

void	choose_fork(t_philo *buddy, long long time)
{
	if (buddy->id < buddy->right_buddy->id)
		return ((void)choose_higher(buddy, time));
	while (buddy->fork.__data.__lock == 1)
	{
		if (!check_death(buddy, time))
			return ;
	}
	pthread_mutex_lock(&buddy->fork);
	print_take_fork(buddy, time);
	while (buddy->right_buddy->fork.__data.__lock == 1)
	{
		if (!check_death(buddy, time))
			return ((void)pthread_mutex_unlock(&buddy->fork));
	}
	pthread_mutex_lock(&buddy->right_buddy->fork);
	print_take_fork(buddy, time);
}

