/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/15 22:00:52 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *buddy, long long time, int from_mess)
{
	int	alive;

	time = timestamp(buddy->curr_time) - buddy->time_since_eat;
	alive = 1;
	pthread_mutex_lock(&buddy->table->read);
	if (buddy->table->alive == 0)
	{
		pthread_mutex_unlock(&buddy->table->read);
		return (0);
	}
	if (time > buddy->time_to_die)
	{
		buddy->table->alive = 0;
		alive = 0;
	}
	pthread_mutex_unlock(&buddy->table->read);
	if (!alive)
		print_died(buddy, time, from_mess);
	return (alive);
}

int	ft_eat(t_philo *buddy, long long time)
{
	if (choose_fork(buddy, time))
	{
		buddy->time_since_eat = timestamp(buddy->curr_time);
		print_messages(buddy, time, "\033[0;32mis eating\033[0m");
		wait_time(buddy, buddy->time_since_eat + buddy->time_to_eat, time);
		pthread_mutex_unlock(&buddy->right_buddy->fork);
		pthread_mutex_unlock(&buddy->fork);
//		print_fork(buddy, time, "has released a fork", buddy->right_buddy->id);
//		print_fork(buddy, time, "has released a fork", buddy->id);
		if (buddy->eaten_times != -1)
			buddy->eaten_times--;
	}
	else
		return (0);
	return (check_death(buddy, time, 0));
}

int	ft_sleep(t_philo *buddy, long long time)
{
	print_messages(buddy, time, "\033[0;33mis sleeping\033[0m");
	time = timestamp(buddy->curr_time) + buddy->time_to_sleep;
	wait_time(buddy, time, time);
	return (check_death(buddy, time, 0));
}

void	*alive_routine(void	*args)
{
	t_philo		*buddy;
	long long	time;

	buddy = (t_philo *)args;
	time = buddy->table->init_time /*+ (buddy->id / 10)*/;
	buddy->time_since_eat = time;
	buddy->init_time = time;
	while (timestamp(buddy->curr_time) < time)
		usleep(10);
	if (buddy->id % 2 == 0)
		ft_sleep(buddy, time);
	while (1)
	{
		
		if (!ft_eat(buddy, time))
			break ;
		if (buddy->eaten_times == 0)
			break ;
		if (!ft_sleep(buddy, time))
			break ;
		if (!check_death(buddy, time, 0))
			break ;
		print_messages(buddy, time, "is thinking");
	}
	pthread_exit(NULL);
}
