/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/07 16:29:46 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_take_fork(t_philo *buddy, int id)
{
	long long	time;
	int			i;

	if (!check_death(buddy))
		return ;
	i = 0;
	pthread_mutex_lock(&buddy->table->write);
	time = timestamp() - buddy->table->init_time;
	printf("%lld %d has taken a fork (id %d)\n", time, buddy->id, id);
	printf("fork id available :");
	while (i < buddy->table->nb_philo)
	{
		if (buddy->table->philo[i]->fork.__data.__lock == 0)
			printf(" %d", i);
		i++;
	}
	printf("\n");
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_release_fork(t_philo *buddy, int id)
{
	long long	time;
	int			i;

	if (!check_death(buddy))
		return ;
	i = 0;
	pthread_mutex_lock(&buddy->table->write);
	time = timestamp() - buddy->table->init_time;
	printf("%lld %d has released a fork (id %d)\n", time, buddy->id, id);
	printf("fork id available :");
	while (i < buddy->table->nb_philo)
	{
		if (buddy->table->philo[i]->fork.__data.__lock == 0)
			printf(" %d", i);
		i++;
	}
	printf("\n");
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_eat(t_philo *buddy)
{
	long long	time;
	if (!check_death(buddy))
		return ;
	pthread_mutex_lock(&buddy->table->write);
	time = buddy->time_since_eat - buddy->table->init_time;
	printf("%lld %d is eating\n", time, buddy->id);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_sleep(t_philo *buddy)
{
	long long	time;
	if (!check_death(buddy))
		return ;
	pthread_mutex_lock(&buddy->table->write);
	time = timestamp() - buddy->table->init_time;
	printf("%lld %d is sleeping\n", time, buddy->id);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_think(t_philo *buddy)
{
	long long	time;
	if (!check_death(buddy))
		return ;
	pthread_mutex_lock(&buddy->table->write);
	time = timestamp() - buddy->table->init_time;
	printf("%lld %d is thinking\n", time, buddy->id);
	pthread_mutex_unlock(&buddy->table->write);

}

void	print_died(t_philo *buddy)
{
	long long	time;

	pthread_mutex_lock(&buddy->table->read);
	buddy->is_alive = 0;
	buddy->table->alive = 0;
	pthread_mutex_unlock(&buddy->table->read);
	pthread_mutex_lock(&buddy->table->write);
	time = timestamp() - buddy->table->init_time;
	printf("%lld %d\033[0;31m died\033[0m\n", time, buddy->id);
	pthread_mutex_unlock(&buddy->table->write);
}
