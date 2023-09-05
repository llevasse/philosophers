/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/05 20:53:34 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_take_fork(t_philo *buddy)
{
	long	time;
//	if (!check_death(buddy))
//		return ;
	pthread_mutex_lock(&buddy->table->write);
	time = timestamp() - buddy->init_time;
	printf("%ld %d has taken a fork\n", time, buddy->id);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_release_fork(t_philo *buddy)
{
//	if (!check_death(buddy))
//		return ; 
	pthread_mutex_lock(&buddy->table->write);
	ft_putnbr_fd(timestamp() - buddy->init_time, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" has released a fork\n", 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_eat(t_philo *buddy)
{
	long	time;
//	if (!check_death(buddy))
//		return ;
	pthread_mutex_lock(&buddy->table->write);
	time = buddy->time_since_eat - buddy->init_time;
	printf("%ld %d is eating\n", time, buddy->id);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_sleep(t_philo *buddy)
{
	long	time;
//	if (!check_death(buddy))
//		return ;
	pthread_mutex_lock(&buddy->table->write);
	time = timestamp() - buddy->init_time;
	printf("%ld %d is sleeping\n", time, buddy->id);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_think(t_philo *buddy)
{
	long	time;
//	if (!check_death(buddy))
//		return ;
	pthread_mutex_lock(&buddy->table->write);
	time = timestamp() - buddy->init_time;
	printf("%ld %d is thinking\n", time, buddy->id);
	pthread_mutex_unlock(&buddy->table->write);

}

void	print_died(t_philo *buddy)
{
	long	time;

	pthread_mutex_lock(&buddy->table->write);
	buddy->is_alive = 0;
	buddy->table->alive = 0;
	time = timestamp() - buddy->init_time;
	printf("%ld %d\033[0;31m died\033[0m\n", time, buddy->id);
	pthread_mutex_unlock(&buddy->table->write);
}
