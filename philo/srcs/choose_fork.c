/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:34:10 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/14 22:34:58 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	choose_higher(t_philo *buddy, long long time)
{
	pthread_mutex_lock(&buddy->right_buddy->fork);
	print_fork(buddy, time, "has taken a fork", buddy->right_buddy->id);
	if (!check_death(buddy, time, 0))
		return ((void)pthread_mutex_unlock(&buddy->right_buddy->fork), 0);
	pthread_mutex_lock(&buddy->fork);
	print_fork(buddy, time, "has taken a fork", buddy->id);
	return (1);
}

int	choose_fork(t_philo *buddy, long long time)
{
	if (buddy->id < buddy->right_buddy->id)
		return (choose_higher(buddy, time));
	pthread_mutex_lock(&buddy->fork);
	print_fork(buddy, time, "has taken a fork", buddy->id);
	if (!check_death(buddy, time, 0))
		return ((void)pthread_mutex_unlock(&buddy->fork), 0);
	pthread_mutex_lock(&buddy->right_buddy->fork);
	print_fork(buddy, time, "has taken a fork", buddy->right_buddy->id);
	return (1);
}
