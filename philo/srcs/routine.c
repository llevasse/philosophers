/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/10 12:44:18 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *buddy, long long time)
{
	pthread_mutex_lock(&buddy->table->read);
	if (buddy->table->alive == 0)
	{
		pthread_mutex_unlock(&buddy->table->read);
		return (0);
	}
	pthread_mutex_unlock(&buddy->table->read);
	time = timestamp(buddy->table->curr_time) - buddy->time_since_eat;
	if (time > buddy->time_to_die)
		return ((void)print_died(buddy, time), 0);
	return (1);
}

int	ft_eat(t_philo *buddy, long long time)
{
	print_think(buddy, time);
	if (choose_fork(buddy, time))
	{
		buddy->time_since_eat = timestamp(buddy->table->curr_time);
		print_eat(buddy, time);
		wait_time(buddy, buddy->time_since_eat + buddy->time_to_eat, time);
		pthread_mutex_unlock(&buddy->fork);
		pthread_mutex_unlock(&buddy->right_buddy->fork);
	}
	return (check_death(buddy, time));
}

int	ft_sleep(t_philo *buddy, long long time)
{
	time = timestamp(buddy->table->curr_time) + buddy->time_to_sleep;
	print_sleep(buddy, time);
	wait_time(buddy, time, time);
	return (check_death(buddy, time));
}

void	*alive_routine(void	*args)
{
	t_philo		*buddy;
	long long	time;

	buddy = (t_philo *)args;
	time = 0;
	while (buddy->table->read.__data.__lock == 1)
		;
	if (buddy->id % 2 != 0)
		usleep(1000 * buddy->table->nb_philo);
	buddy->time_since_eat = timestamp(buddy->table->curr_time);
	while (42)
	{
		if (!ft_eat(buddy, time))
			break ;
		if (!ft_sleep(buddy, time))
			break ;
	}
	pthread_exit(NULL);
}
