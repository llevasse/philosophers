/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/12 15:35:58 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_take_fork(t_philo *buddy, pthread_mutex_t *fork, long long time)
{
	pthread_mutex_lock(fork);
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	while (buddy->table->write.__data.__lock == 1)
		usleep(100);
	pthread_mutex_lock(&buddy->table->write);
	if (!check_death(buddy, time))
		return ;
	printf("%lld %d has taken a fork\n", time, buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_eat(t_philo *buddy, long long time)
{
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	while (buddy->table->write.__data.__lock == 1)
		usleep(100);
	pthread_mutex_lock(&buddy->table->write);
	if (!check_death(buddy, time))
		return ;
	printf("%lld %d\033[0;32m is eating\033[0m\n", time, buddy->id + 1);
	pthread_mutex_lock(&buddy->table->read);
	buddy->eaten_times++;
	pthread_mutex_unlock(&buddy->table->read);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_sleep(t_philo *buddy, long long time)
{
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	while (buddy->table->write.__data.__lock == 1)
		usleep(100);
	pthread_mutex_lock(&buddy->table->write);
	if (!check_death(buddy, time))
		return ;
	printf("%lld %d\033[0;33m is sleeping\033[0m\n", time, buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_think(t_philo *buddy, long long time)
{
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	while (buddy->table->write.__data.__lock == 1)
		usleep(100);
	pthread_mutex_lock(&buddy->table->write);
	if (!check_death(buddy, time))
		return ;
	printf("%lld %d is thinking\n", time, buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_died(t_philo *buddy, long long time)
{
	pthread_mutex_lock(&buddy->table->read);
	buddy->is_alive = 0;
	buddy->table->alive = 0;
	pthread_mutex_unlock(&buddy->table->read);
	if (buddy->table->write.__data.__lock == 0)
		pthread_mutex_lock(&buddy->table->write);
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	printf("%lld %d\033[0;31m died\033[0m\n", time, buddy->id + 1);
	if (buddy->table->write.__data.__lock == 1)
		pthread_mutex_unlock(&buddy->table->write);
}
