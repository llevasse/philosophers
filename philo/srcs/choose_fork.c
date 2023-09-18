/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:34:10 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/18 10:57:25 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	choose_higher(t_philo *buddy)
{
	pthread_mutex_lock(&buddy->right_buddy->fork);
	if (!check_death(buddy))
		return ((void)pthread_mutex_unlock(&buddy->right_buddy->fork), 0);
	print_fork(buddy, "has taken a fork", buddy->right_buddy->id);
	pthread_mutex_lock(&buddy->fork);
	if (!check_death(buddy))
	{
		pthread_mutex_unlock(&buddy->fork);
		return ((void)pthread_mutex_unlock(&buddy->right_buddy->fork), 0);
	}
	print_fork(buddy, "has taken a fork", buddy->id);
	return (1);
}

int	choose_fork(t_philo *buddy)
{
	if (buddy->id < buddy->right_buddy->id)
		return (choose_higher(buddy));
	pthread_mutex_lock(&buddy->fork);
	if (!check_death(buddy))
		return ((void)pthread_mutex_unlock(&buddy->fork), 0);
	print_fork(buddy, "has taken a fork", buddy->id);
	pthread_mutex_lock(&buddy->right_buddy->fork);
	if (!check_death(buddy))
	{
		pthread_mutex_unlock(&buddy->fork);
		return ((void)pthread_mutex_unlock(&buddy->right_buddy->fork), 0);
	}
	print_fork(buddy, "has taken a fork", buddy->right_buddy->id);
	return (1);
}
