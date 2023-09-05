/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/05 13:42:54 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *buddy)
{
	long	time;

	gettimeofday(&buddy->current_time, NULL);
	time = buddy->current_time.tv_usec - buddy->time_since_eating.tv_usec;
	pthread_mutex_lock(&buddy->table->write);
	if (buddy->table->alive == 0)
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
	while (buddy->current_time.tv_usec < time && check_death(buddy))
		gettimeofday(&buddy->current_time, NULL);
}

static int	get_fork(t_philo *buddy, pthread_mutex_t *fork)
{
	while (fork->__data.__lock == 1 && buddy->table->alive == 1)	
	{
		if (check_death(buddy) == 0)
			return (0);
	}
	pthread_mutex_lock(fork);
	print_take_fork(buddy);
	return (1);
}

static pthread_mutex_t	*choose_fork(t_philo *buddy)
{
	while (1)
	{
		if (buddy->left_buddy->fork.__data.__lock == 0)
		{
			get_fork(buddy, &buddy->left_buddy->fork);
			return (&buddy->left_buddy->fork);
		}
		else if (buddy->fork.__data.__lock == 0)
		{
			get_fork(buddy, &buddy->fork);
			return (&buddy->fork);
		}
		else if (buddy->right_buddy->fork.__data.__lock == 0)
		{
			get_fork(buddy, &buddy->right_buddy->fork);
			return (&buddy->right_buddy->fork);
		}
	}

}

int	ft_eat(t_philo *buddy)
{
	long	time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	if (buddy->table->alive == 0)
		return (buddy->table->alive);
	left_fork = choose_fork(buddy);
	right_fork = choose_fork(buddy);
	gettimeofday(&buddy->current_time, NULL);
	time = buddy->current_time.tv_usec + buddy->time_to_eat;
	print_eat(buddy);
	wait_time(buddy, time);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	buddy->eaten_times++;
	return (buddy->table->alive);
}

int	ft_sleep(t_philo *buddy)
{
	long	time;

	check_death(buddy);
	if (buddy->table->alive == 0)
		return (buddy->table->alive);
	print_sleep(buddy);
	time = buddy->current_time.tv_usec + buddy->time_to_sleep;
	wait_time(buddy, time);
	return (buddy->table->alive);
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
