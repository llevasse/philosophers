/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/13 20:40:48 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_messages(t_philo *buddy, long long time, char *mess)
{
	pthread_mutex_lock(&buddy->table->write);
	if (!check_death(buddy, time))
		return ((void)pthread_mutex_unlock(&buddy->table->write));
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	printf("%lld %d %s\n", time, buddy->id + 1, mess);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_died(t_philo *buddy, long long time)
{
	pthread_mutex_lock(&buddy->table->write);
	pthread_mutex_lock(&buddy->table->read);
	buddy->is_alive = 0;
	buddy->table->alive = 0;
	pthread_mutex_unlock(&buddy->table->read);
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	printf("%lld %d\033[0;31m died\033[0m\n", time, buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}
