/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/18 14:05:41 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_messages(t_philo *buddy, char *mess)
{
	long long	time;

	pthread_mutex_lock(&buddy->table->write);
	time = timestamp() - buddy->init_time;
	if (time >= 999999)
		time = 999999;
	if (!check_death(buddy))
		return ((void)pthread_mutex_unlock(&buddy->table->write));
	printf("%lld %d %s\n", time, buddy->id, mess);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_died(t_philo *buddy)
{
	long long	time;

	time = timestamp() - buddy->init_time;
	pthread_mutex_lock(&buddy->table->write);
	if (time >= 999999)
		time = 999999;
	printf("%lld %d \033[0;31mdied\033[0m\n", time, buddy->id);
	usleep(150);
	pthread_mutex_unlock(&buddy->table->write);
}
