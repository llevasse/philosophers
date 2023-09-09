/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/09 21:00:04 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_take_fork(t_philo *buddy, long long time)
{
	if (!check_death(buddy, time))
		return ;
	pthread_mutex_lock(&buddy->table->write);
	printf("%lld %d has taken a fork\n", 
		timestamp() - buddy->table->init_time, buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_eat(t_philo *buddy, long long time)
{
	if (!check_death(buddy, time))
		return ;
	pthread_mutex_lock(&buddy->table->write);
	printf("%lld %d\033[0;32m is eating\033[0m\n", 
		timestamp() - buddy->table->init_time, buddy->id + 1);
	buddy->eaten_times++;
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_sleep(t_philo *buddy, long long time)
{
	if (!check_death(buddy, time))
		return ;
	pthread_mutex_lock(&buddy->table->write);
	printf("%lld %d\033[0;33m is sleeping\033[0m\n", 
		timestamp() - buddy->table->init_time, buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_think(t_philo *buddy, long long time)
{
	if (!check_death(buddy, time))
		return ;
	pthread_mutex_lock(&buddy->table->write);
	printf("%lld %d is thinking\n", 
		timestamp() - buddy->table->init_time, buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_died(t_philo *buddy, long long time)
{
	pthread_mutex_lock(&buddy->table->read);
	buddy->is_alive = 0;
	buddy->table->alive = 0;
	pthread_mutex_unlock(&buddy->table->read);
	pthread_mutex_lock(&buddy->table->write);
	printf("%lld %d\033[0;31m died\033[0m\n", 
		timestamp() - buddy->table->init_time, buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
	(void)time;
}
