/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/04 16:24:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *buddy)
{
	pthread_mutex_lock(&buddy->left_buddy->fork);
	pthread_mutex_lock(&buddy->right_buddy->fork);
	gettimeofday(&buddy->current_time, NULL);
	print_take_fork(buddy);
	print_take_fork(buddy);
	gettimeofday(&buddy->current_time, NULL);
	print_eat(buddy);
	usleep(buddy->time_to_eat);
	gettimeofday(&buddy->time_since_eating, NULL);
	buddy->eaten_times++;
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
	if (buddy->id % 2 == 0)
		usleep(1);
	while (buddy->table->died == 0)
	{
		ft_eat(buddy);
		ft_sleep(buddy);
		gettimeofday(&buddy->current_time, NULL);
		if (buddy->current_time.tv_usec - buddy->time_since_eating.tv_usec < \
			buddy->time_to_die)
		{
			print_died(buddy);
//			buddy->table->died = 1;
		}
	}
	pthread_exit(NULL);
	return (NULL);
}
