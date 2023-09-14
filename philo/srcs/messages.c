/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/14 10:02:10 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_messages(t_philo *buddy, long long time, char *mess)
{
	pthread_mutex_lock(&buddy->table->write);
	if (!check_death(buddy, time, 1))
		return ((void)pthread_mutex_unlock(&buddy->table->write));
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (time >= 999999)
		time = 999999;
	printf("%lld %d %s\n", time, buddy->id + 1, mess);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_died(t_philo *buddy, long long time, int from_print)
{
	time = timestamp(buddy->curr_time) - buddy->table->init_time;
	if (!from_print)
		pthread_mutex_lock(&buddy->table->write);
	if (time >= 999999)
		time = 999999;
	printf("%lld %d\033[0;31m died\033[0m\n", time, buddy->id + 1);
	if (!from_print)
		pthread_mutex_unlock(&buddy->table->write);
}
