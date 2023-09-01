/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/01 12:36:32 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	can_eat(t_philo *buddy)
{
	pthread_mutex_lock(&buddy->left_buddy->fork);
	gettimeofday(&buddy->current_time, NULL);
	ft_putnbr_fd(buddy->table->init_time.tv_usec - buddy->current_time.tv_usec, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" has taken a fork\n", 1);
	pthread_mutex_lock(&buddy->right_buddy->fork);
	ft_putnbr_fd(buddy->table->init_time.tv_usec - buddy->current_time.tv_usec, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(buddy->id, 1);
	ft_putstr_fd(" has taken a fork\n", 1);
	return (1);
}

void	*alive_routine(void	*args)
{
	t_philo	*buddy;

	buddy = (t_philo *)args;
	print_philo(buddy);
	if (can_eat(buddy))
	{
		usleep(buddy->time_to_eat);
		gettimeofday(&buddy->time_since_eating, NULL);
	}
	pthread_exit(NULL);
	return (NULL);
}
