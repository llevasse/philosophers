/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/07 16:56:46 by llevasse         ###   ########.fr       */
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
		return (print_died(buddy), 0);
	return (1);
}

static pthread_mutex_t	*choose_fork(t_philo *buddy, int *id)
{
	while (check_death(buddy))
	{
		if (buddy->fork.__data.__lock == 0)
		{
			pthread_mutex_lock(&buddy->fork);
			print_take_fork(buddy, buddy->id);
			*id = buddy->id;
			return (&buddy->fork);
		}
		if (buddy->left_buddy->fork.__data.__lock == 0)
		{
			pthread_mutex_lock(&buddy->left_buddy->fork);
			print_take_fork(buddy, buddy->left_buddy->id);
			*id = buddy->left_buddy->id;
			return (&buddy->left_buddy->fork);
		}
		if (buddy->right_buddy->fork.__data.__lock == 0)
		{
			pthread_mutex_lock(&buddy->right_buddy->fork);
			print_take_fork(buddy, buddy->right_buddy->id);
			*id = buddy->right_buddy->id;
			return (&buddy->right_buddy->fork);
		}
	}
	return (NULL);
}

int	ft_eat(t_philo *buddy)
{
	long			time;
	pthread_mutex_t	*left_fork;
	int				left_id;
	pthread_mutex_t	*right_fork;
	int				right_id;

	print_think(buddy);
	if (!check_death(buddy))
		return (0);
	left_fork = choose_fork(buddy, &left_id);
	if (!left_fork)
		return (0);
	right_fork = choose_fork(buddy, &right_id);
	if (!right_fork)
		return ((void)pthread_mutex_unlock(left_fork), 0);
	buddy->time_since_eat = timestamp();
	time = buddy->time_since_eat + buddy->time_to_eat;
	print_eat(buddy);
	wait_time(buddy, time);
	pthread_mutex_unlock(left_fork);
	print_release_fork(buddy, left_id);
	pthread_mutex_unlock(right_fork);
	print_release_fork(buddy, right_id);
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
		usleep(1000);
	buddy->time_since_eat = timestamp();
	while (42)
	{
		if (!ft_eat(buddy))
			break ;
		buddy->eaten_times++;
		if (!ft_sleep(buddy))
			break ;
	}
	pthread_exit(NULL);
}
