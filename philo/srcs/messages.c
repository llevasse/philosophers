/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/05 00:03:09 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_take_fork(t_philo *buddy)
{
	pthread_mutex_lock(&buddy->table->write);
	ft_putnbr_fd(buddy->current_time.tv_usec - buddy->table->init_time.tv_usec, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" has taken a fork\n", 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_eat(t_philo *buddy)
{
	pthread_mutex_lock(&buddy->table->write);
	ft_putnbr_fd(buddy->current_time.tv_usec - buddy->table->init_time.tv_usec, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" is eating\n", 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_sleep(t_philo *buddy)
{
	pthread_mutex_lock(&buddy->table->write);
	ft_putnbr_fd(buddy->current_time.tv_usec - buddy->table->init_time.tv_usec, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" is sleeping\n", 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_think(t_philo *buddy)
{
	pthread_mutex_lock(&buddy->table->write);
	ft_putnbr_fd(buddy->current_time.tv_usec - buddy->table->init_time.tv_usec, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" is thinking\n", 1);
	pthread_mutex_unlock(&buddy->table->write);
}

void	print_died(t_philo *buddy)
{
	pthread_mutex_lock(&buddy->table->write);
	ft_putnbr_fd(buddy->current_time.tv_usec - buddy->table->init_time.tv_usec, 1);
	ft_putstr_fd(" \033[0;31m", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" died\033[0m\n", 1);
	pthread_mutex_unlock(&buddy->table->write);
}
