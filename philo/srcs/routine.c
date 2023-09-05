/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/05 09:11:42 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *buddy)
{
	long	time;

	gettimeofday(&buddy->current_time, NULL);
	time = buddy->current_time.tv_usec - buddy->time_since_eating.tv_usec;
	pthread_mutex_lock(&buddy->table->write);
	if (buddy->table->died == 1)
	{
		pthread_mutex_unlock(&buddy->table->write);
		return (0);
	}
//	ft_putstr_fd("\033[0;33m", 1);
//	ft_putnbr_fd(time , 1);
//	ft_putstr_fd(" ", 1);
//	ft_putnbr_fd(buddy->id, 1);
//	ft_putstr_fd(" time since eating\n", 1);
//	ft_putstr_fd("\033[0m", 1);
	pthread_mutex_unlock(&buddy->table->write);
	if (time > buddy->time_to_die)
		return (print_died(buddy), 0);
	return (1);
}

void	wait_time(t_philo *buddy, long time)
{
	while (buddy->current_time.tv_usec < time && buddy->table->died == 0)
		gettimeofday(&buddy->current_time, NULL);
}

int	ft_eat(t_philo *buddy)
{
	long	time;

	if (buddy->table->died)
		return (!buddy->table->died);
	pthread_mutex_lock(&buddy->right_buddy->fork);
	print_take_fork(buddy);
	pthread_mutex_lock(&buddy->left_buddy->fork);
	print_take_fork(buddy);
	gettimeofday(&buddy->current_time, NULL);
	time = buddy->current_time.tv_usec + buddy->time_to_eat;
	gettimeofday(&buddy->time_since_eating, NULL);
	print_eat(buddy);
	wait_time(buddy, time);
	pthread_mutex_unlock(&buddy->left_buddy->fork);
//	print_release_fork(buddy);
	pthread_mutex_unlock(&buddy->right_buddy->fork);
//	print_release_fork(buddy);
	buddy->eaten_times++;
	return (!buddy->table->died);
}

int	ft_sleep(t_philo *buddy)
{
	long	time;

	if (buddy->table->died)
		return (!buddy->table->died);
	time = buddy->current_time.tv_usec + buddy->time_to_sleep;
	print_sleep(buddy);
	wait_time(buddy, time);
	return (!buddy->table->died);
}

void	*alive_routine(void	*args)
{
	t_philo	*buddy;

	buddy = (t_philo *)args;
	gettimeofday(&buddy->time_since_eating, NULL);
	while (42)
	{
		if (!ft_eat(buddy))
			break ;
		if (!ft_sleep(buddy))
			break ;
		gettimeofday(&buddy->current_time, NULL);
		print_think(buddy);
	}
	pthread_exit(NULL);
}
