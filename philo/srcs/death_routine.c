/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/17 19:31:03 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	detach_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
		pthread_detach(table->threads[i++]);
}

static int	check_need_eat(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philo[i]->eat);
		if (table->philo[i]->eaten_times > 0 || table->philo[i]->eaten_times == -1)
		{
			pthread_mutex_unlock(&table->philo[i]->eat);
			return (1);
		}
		pthread_mutex_unlock(&table->philo[i]->eat);
		i++;
	}
	return (0);
}

static int	check_died(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philo[i]->eat);
		if (timestamp() - table->philo[i]->time_since_eat > \
				table->philo[i]->time_to_die && \
				table->philo[i]->eaten_times != 0)
		{
			pthread_mutex_unlock(&table->philo[i]->eat);
			table->alive = 0;
			pthread_mutex_unlock(&table->read);
			print_died(table->philo[i]);
			return (0);
		}
		pthread_mutex_unlock(&table->philo[i]->eat);
		i++;
	}
	return (i);
}

void	*death_routine(void	*args)
{
	t_table	*table;

	table = (t_table *)args;
	while (timestamp() < table->init_time)
		continue ;
	while (1)
	{
		pthread_mutex_lock(&table->read);
		if (!check_died(table))
			break ;
		pthread_mutex_unlock(&table->read);
		if (!check_need_eat(table))
			break ;
		usleep(100);
	}
	pthread_exit(NULL);
}
