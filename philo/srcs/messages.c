/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/15 22:03:41 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_messages(t_philo *buddy, long long time, char *mess)
{
	pthread_mutex_lock(&buddy->table->write);
	//if (!check_death(buddy, time, 1))
	//	return ((void)pthread_mutex_unlock(&buddy->table->write));
	time = timestamp(buddy->curr_time) - buddy->init_time;
	if (time >= 999999)
		time = 999999;
	dprintf(buddy->fd, "%lld %d %s\n", time, buddy->id, mess);
	dprintf(buddy->table->fd, "%lld %d %s\n", time, buddy->id, mess);
	if (DEBUG)
		printf("%lld %d %s\n", time, buddy->id, mess);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_fork(t_philo *buddy, long long time, char *mess, int id)
{
	pthread_mutex_lock(&buddy->table->write);
	//if (!check_death(buddy, time, 1))
	//	return ((void)pthread_mutex_unlock(&buddy->table->write));
	time = timestamp(buddy->curr_time) - buddy->init_time;
	if (time >= 999999)
		time = 999999;
	dprintf(buddy->fd, "%lld %d %s (%d)\n", time, buddy->id, mess, id);
	dprintf(buddy->table->fd, "%lld %d %s (%d)\n", time, buddy->id, mess, id);
	if (DEBUG)
		printf("%lld %d %s (%d)\n", time, buddy->id, mess, id);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_died(t_philo *buddy, long long time, int from_print)
{
	time = timestamp(buddy->curr_time) - buddy->init_time;
	if (!from_print)
		pthread_mutex_lock(&buddy->table->write);
	if (time >= 999999)
		time = 999999;
	dprintf(buddy->fd, "%lld %d \033[0;31mdied\033[0m\n", time, buddy->id);
	dprintf(buddy->table->fd, "%lld %d \033[0;31mdied\033[0m\n", time, buddy->id);
	if (DEBUG)
		printf("%lld %d \033[0;31mdied\033[0m\n", time, buddy->id);
	if (!from_print)
		pthread_mutex_unlock(&buddy->table->write);
//	pthread_exit(NULL);
}
