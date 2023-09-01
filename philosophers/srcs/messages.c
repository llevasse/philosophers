/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/01 22:44:48 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_take_fork(t_philo *buddy)
{
	ft_putnbr_fd(buddy->current_time.tv_usec - buddy->table->init_time.tv_usec, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" has taken a fork\n", 1);
}

void	print_eat(t_philo *buddy)
{
	ft_putnbr_fd(buddy->current_time.tv_usec - buddy->table->init_time.tv_usec, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" is eating\n", 1);
}

void	print_sleep(t_philo *buddy)
{
	ft_putnbr_fd(buddy->current_time.tv_usec - buddy->table->init_time.tv_usec, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" is sleeping\n", 1);
}

void	print_think(t_philo *buddy)
{
	ft_putnbr_fd(buddy->current_time.tv_usec - buddy->table->init_time.tv_usec, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" is thinking\n", 1);
}

void	print_died(t_philo *buddy)
{
	ft_putnbr_fd(buddy->current_time.tv_usec - buddy->table->init_time.tv_usec, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" died\n", 1);
}
