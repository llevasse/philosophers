/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/04 19:00:51 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_death(t_philo *buddy)
{
	if (buddy->current_time.tv_usec - buddy->time_since_eating.tv_usec > \
		buddy->time_to_die)
	{
		print_died(buddy);
		buddy->table->died = 1;
	}	
}

void	ft_eat(t_philo *buddy)
{
	long	time;

	pthread_mutex_lock(&buddy->fork);
	pthread_mutex_lock(&buddy->right_buddy->fork);
	gettimeofday(&buddy->current_time, NULL);
	print_take_fork(buddy);
	print_take_fork(buddy);
	gettimeofday(&buddy->current_time, NULL);
	time = buddy->current_time.tv_usec + buddy->time_to_eat;
	gettimeofday(&buddy->time_since_eating, NULL);
	print_eat(buddy);
	while (buddy->current_time.tv_usec < time)
		gettimeofday(&buddy->current_time, NULL);
	buddy->eaten_times++;
	check_death(buddy);
	pthread_mutex_unlock(&buddy->fork);
	pthread_mutex_unlock(&buddy->right_buddy->fork);
}

void	ft_sleep(t_philo *buddy)
{
	long	time;

	time = buddy->current_time.tv_usec + buddy->time_to_eat;
	print_sleep(buddy);
	while (buddy->current_time.tv_usec < time)
		gettimeofday(&buddy->current_time, NULL);
	check_death(buddy);
}

void	*alive_routine(void	*args)
{
	t_philo	*buddy;

	buddy = (t_philo *)args;
	while (buddy->table->died == 0)
	{
		ft_eat(buddy);
		ft_sleep(buddy);
	}
	pthread_exit(NULL);
	return (NULL);
}
