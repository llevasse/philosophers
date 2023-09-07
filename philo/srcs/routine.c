/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/07 11:03:57 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *buddy)
{
	long	time;

	pthread_mutex_lock(&buddy->table->write);
	if (buddy->table->alive == 0)
	{
		pthread_mutex_unlock(&buddy->table->write);
		return (0);
	}
	pthread_mutex_unlock(&buddy->table->write);
	time = timestamp() - buddy->time_since_eat;
	if (time > buddy->time_to_die)
		return (print_died(buddy), 0);
	return (1);
}

static pthread_mutex_t	*choose_fork(t_philo *buddy)
{
	while (check_death(buddy))
	{
		if (buddy->fork.__data.__lock == 0)
		{
			pthread_mutex_lock(&buddy->fork);
			return (&buddy->fork);
		}
		if (buddy->left_buddy->fork.__data.__lock == 0)
		{
			pthread_mutex_lock(&buddy->left_buddy->fork);
			return (&buddy->left_buddy->fork);
		}
		if (buddy->right_buddy->fork.__data.__lock == 0)
		{
			pthread_mutex_lock(&buddy->right_buddy->fork);
			return (&buddy->right_buddy->fork);
		}
	}
	return (NULL);
}

int	ft_eat(t_philo *buddy)
{
	long	time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	print_think(buddy);
	if (!check_death(buddy))
		return (0);
	left_fork = choose_fork(buddy);
	if (!left_fork)
		return (0);
	print_take_fork(buddy);
	right_fork = choose_fork(buddy);
	if (!right_fork)
		return ((void)pthread_mutex_unlock(left_fork), 0);
	print_take_fork(buddy);
	buddy->time_since_eat = timestamp();
	time = buddy->time_since_eat + buddy->time_to_eat;
	print_eat(buddy);
	wait_time(buddy, time);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	buddy->eaten_times++;
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
	if (buddy->id % 2 == 0)
		usleep(1000000);
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
