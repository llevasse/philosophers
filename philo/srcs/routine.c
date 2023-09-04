/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/04 22:33:47 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_death(t_philo *buddy)
{
	long	time;

	gettimeofday(&buddy->current_time, NULL);
	time = buddy->current_time.tv_usec - buddy->time_since_eating.tv_usec;
//	pthread_mutex_lock(&buddy->table->write);
//	ft_putstr_fd("\033[0;33m", 1);
//	ft_putnbr_fd(time , 1);
//	ft_putstr_fd(" ", 1);
//	ft_putnbr_fd(buddy->id, 1);
//	ft_putstr_fd(" time since eating\n", 1);
//	ft_putstr_fd("\033[0m", 1);
//	pthread_mutex_unlock(&buddy->table->write);
	if (time > buddy->time_to_die)
	{
		print_died(buddy);
		buddy->is_alive = 0;
	}	
}

void	ft_eat(t_philo *buddy)
{
	long	time;

	pthread_mutex_lock(&buddy->fork);
	pthread_mutex_lock(&buddy->right_buddy->fork);
	gettimeofday(&buddy->current_time, NULL);
	print_take_fork(buddy);
	gettimeofday(&buddy->current_time, NULL);
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

	time = buddy->current_time.tv_usec + buddy->time_to_sleep;
	print_sleep(buddy);
	while (buddy->current_time.tv_usec < time)
		gettimeofday(&buddy->current_time, NULL);
	check_death(buddy);
}

void	*alive_routine(void	*args)
{
	t_philo	*buddy;

	buddy = (t_philo *)args;
	while (buddy->is_alive == 1)
	{
		ft_eat(buddy);
		if (buddy->is_alive == 0)
			break ;
		ft_sleep(buddy);
		if (buddy->is_alive == 0)
			break ;
		gettimeofday(&buddy->current_time, NULL);
		print_think(buddy);
	}
	pthread_exit(NULL);
	return (NULL);
}
