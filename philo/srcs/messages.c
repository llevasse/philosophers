/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:35:37 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/25 20:04:20 by llevasse         ###   ########.fr       */
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

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n * -1, fd);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd(n + '0', fd);
		else
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putchar_fd(n % 10 + '0', fd);
		}
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
