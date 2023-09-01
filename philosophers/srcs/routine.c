/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/02 00:09:29 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *buddy)
{
	pthread_mutex_lock(&buddy->left_buddy->fork);
	gettimeofday(&buddy->current_time, NULL);
	print_take_fork(buddy);
	pthread_mutex_lock(&buddy->right_buddy->fork);
	print_take_fork(buddy);
	gettimeofday(&buddy->current_time, NULL);
	print_eat(buddy);
	usleep(buddy->time_to_eat);
	buddy->eaten_times++;
	gettimeofday(&buddy->time_since_eating, NULL);
	pthread_mutex_unlock(&buddy->left_buddy->fork);
	pthread_mutex_unlock(&buddy->right_buddy->fork);
}

void	ft_sleep(t_philo *buddy)
{
	gettimeofday(&buddy->current_time, NULL);
	print_sleep(buddy);
	usleep(buddy->time_to_sleep);
}

void	*alive_routine(void	*args)
{
	t_philo	*buddy;

	buddy = (t_philo *)args;
	while (buddy->is_alive)
	{
		ft_eat(buddy);
		ft_sleep(buddy);
	}
	pthread_exit(NULL);
	return (NULL);
}
