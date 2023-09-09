/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/09 17:12:21 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *buddy)
{
	long	time;

	pthread_mutex_lock(&buddy->table->read);
	if (buddy->table->alive == 0)
	{
		pthread_mutex_unlock(&buddy->table->read);
		return (0);
	}
	pthread_mutex_unlock(&buddy->table->read);
	time = timestamp() - buddy->time_since_eat;
	if (time > buddy->time_to_die)
		return ((void)print_died(buddy), 0);
	return (1);
}

static void	choose_fork(t_philo *buddy)
{
	int	i;
	if (buddy->id < buddy->right_buddy->id)
	{
		while (buddy->right_buddy->fork.__data.__lock == 1)
			i = check_death(buddy);
		if (!i)
			return ;
		pthread_mutex_lock(&buddy->right_buddy->fork);
		print_take_fork(buddy);
		while (buddy->fork.__data.__lock == 1)
			i = check_death(buddy);
		if (!i)
			return ((void)pthread_mutex_unlock(&buddy->right_buddy->fork));
		pthread_mutex_lock(&buddy->fork);
		print_take_fork(buddy);
	}
	else
	{
		while (buddy->fork.__data.__lock == 1)
			i = check_death(buddy);
		if (!i)
			return ;
		pthread_mutex_lock(&buddy->fork);
		print_take_fork(buddy);
		while (buddy->right_buddy->fork.__data.__lock == 1)
			i = check_death(buddy);
		if (!i)
			return ((void)pthread_mutex_unlock(&buddy->fork));
		pthread_mutex_lock(&buddy->right_buddy->fork);
		print_take_fork(buddy);
	}
}

int	ft_eat(t_philo *buddy)
{
	print_think(buddy);
	if (!check_death(buddy))
		return (0);
	choose_fork(buddy);
	if (!check_death(buddy))
		return (0);
	buddy->time_since_eat = timestamp();
	print_eat(buddy);
	wait_time(buddy, buddy->time_since_eat + buddy->time_to_eat);
	pthread_mutex_unlock(&buddy->fork);
	pthread_mutex_unlock(&buddy->right_buddy->fork);
	return (check_death(buddy));
}

int	ft_sleep(t_philo *buddy)
{
	long	time;

	if (!check_death(buddy))
		return (0);
	print_sleep(buddy);
	time = timestamp() + buddy->time_to_sleep;
	wait_time(buddy, time);
	return (check_death(buddy));
}

void	*alive_routine(void	*args)
{
	t_philo	*buddy;

	buddy = (t_philo *)args;
	while (buddy->table->read.__data.__lock == 1)
		;
	if (buddy->id % 2 != 0)
		usleep(1000 * buddy->table->nb_philo);
	buddy->time_since_eat = timestamp();
	while (42)
	{
		if (!ft_eat(buddy))
			break ;
		if (!ft_sleep(buddy))
			break ;
	}
	pthread_exit(NULL);
}
