/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/01 22:43:12 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	can_eat(t_philo *buddy)
{
	pthread_mutex_lock(&buddy->left_buddy->fork);
	gettimeofday(&buddy->current_time, NULL);
	print_take_fork(buddy);
	pthread_mutex_lock(&buddy->right_buddy->fork);
	print_take_fork(buddy);
	return (1);
}

void	*alive_routine(void	*args)
{
	t_philo	*buddy;

	buddy = (t_philo *)args;
	if (can_eat(buddy))
	{
		usleep(buddy->time_to_eat);
		gettimeofday(&buddy->time_since_eating, NULL);
		pthread_mutex_unlock(&buddy->right_buddy->fork);
		pthread_mutex_unlock(&buddy->right_buddy->fork);
	}
	pthread_exit(NULL);
	return (NULL);
}
