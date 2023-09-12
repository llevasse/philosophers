/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/12 16:41:05 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_take_fork(t_philo *buddy, pthread_mutex_t *fork, long long time)
{
	pthread_mutex_lock(fork);
	while (buddy->table->write.__data.__lock == 1)
		usleep(100);
	pthread_mutex_lock(&buddy->table->write);
	printf("write lock l21 (Philo %d)\n", buddy->id + 1);
	if (!check_death(buddy, time))
		return ;
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	printf("%lld %d has taken a fork\n", time, buddy->id + 1);
	printf("write unlock l28 (Philo %d)\n", buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_eat(t_philo *buddy, long long time)
{
	while (buddy->table->write.__data.__lock == 1)
		usleep(100);
	pthread_mutex_lock(&buddy->table->write);
	printf("write lock l37 (Philo %d)\n", buddy->id + 1);
	if (!check_death(buddy, time))
		return ;
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	printf("%lld %d\033[0;32m is eating\033[0m\n", time, buddy->id + 1);
	pthread_mutex_lock(&buddy->table->read);
	printf("read lock l45 (Philo %d)\n", buddy->id + 1);
	buddy->eaten_times++;
	printf("read unlock l47 (Philo %d)\n", buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->read);
	printf("write unlock l49 (Philo %d)\n", buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_sleep(t_philo *buddy, long long time)
{
	while (buddy->table->write.__data.__lock == 1)
		usleep(100);
	pthread_mutex_lock(&buddy->table->write);
	printf("write lock l58 (Philo %d)\n", buddy->id + 1);
	if (!check_death(buddy, time))
		return ;
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	printf("%lld %d\033[0;33m is sleeping\033[0m\n", time, buddy->id + 1);
	printf("write unlock l65 (Philo %d)\n", buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_think(t_philo *buddy, long long time)
{
	while (buddy->table->write.__data.__lock == 1)
		usleep(100);
	pthread_mutex_lock(&buddy->table->write);
	printf("write lock l74 (Philo %d)\n", buddy->id + 1);
	if (!check_death(buddy, time))
		return ;
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	printf("%lld %d is thinking\n", time, buddy->id + 1);
	printf("write unlock l81 (Philo %d)\n", buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_died(t_philo *buddy, long long time)
{
//	if (buddy->table->write.__data.__lock == 0)
//	{	
		pthread_mutex_lock(&buddy->table->write);
	printf("write lock l90 (Philo %d)\n", buddy->id + 1);
//	}
	pthread_mutex_lock(&buddy->table->read);
	printf("read lock l93 (Philo %d)\n", buddy->id + 1);
	buddy->is_alive = 0;
	buddy->table->alive = 0;
	printf("read unlock l96 (Philo %d)\n", buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->read);
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	printf("%lld %d\033[0;31m died\033[0m\n", time, buddy->id + 1);
//	if (buddy->table->write.__data.__lock == 1)
//	{
	printf("write unlock l104 (Philo %d)\n", buddy->id + 1);
		pthread_mutex_unlock(&buddy->table->write);
//	}
}
