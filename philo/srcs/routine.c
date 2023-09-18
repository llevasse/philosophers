/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/18 10:46:26 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *buddy)
{
	pthread_mutex_lock(&buddy->save);
	if (buddy->alive == 0)
	{
		pthread_mutex_unlock(&buddy->save);
		return (0);
	}
	pthread_mutex_unlock(&buddy->save);
	return (1);
}

int	ft_eat(t_philo *buddy)
{
	if (choose_fork(buddy))
	{
		pthread_mutex_lock(&buddy->save);
		buddy->time_since_eat = timestamp();
		if (buddy->eaten_times != -1)
			buddy->eaten_times--;
		pthread_mutex_unlock(&buddy->save);
		print_messages(buddy, "\033[0;32mis eating\033[0m");
		wait_time(buddy, buddy->time_since_eat + buddy->time_to_eat);
		pthread_mutex_unlock(&buddy->right_buddy->fork);
		pthread_mutex_unlock(&buddy->fork);
	}
	else
		return (0);
	return (check_death(buddy));
}

int	ft_sleep(t_philo *buddy)
{
	long long	time;

	time = timestamp() + buddy->time_to_sleep;
	print_messages(buddy, "\033[0;33mis sleeping\033[0m");
	wait_time(buddy, time);
	return (check_death(buddy));
}

void	*alive_routine(void	*args)
{
	t_philo		*buddy;

	buddy = (t_philo *)args;
	while (timestamp() < buddy->init_time)
		continue;
	if (buddy->id % 2 == 0)
		ft_sleep(buddy);
	while (check_death(buddy))
	{
		if (!ft_eat(buddy))
			break ;
		if (buddy->eaten_times == 0)
			break ;
		if (!ft_sleep(buddy))
			break ;
		print_messages(buddy, "is thinking");
	}
	pthread_exit(NULL);
}
