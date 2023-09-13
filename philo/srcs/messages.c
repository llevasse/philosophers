/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/13 21:13:05 by llevasse         ###   ########.fr       */
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
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	pthread_mutex_lock(&buddy->table->write);
	if (time >= 999999)
		time = 999999;
	printf("%lld %d\033[0;31m died\033[0m\n", time, buddy->id + 1);
	pthread_mutex_unlock(&buddy->table->write);
}
