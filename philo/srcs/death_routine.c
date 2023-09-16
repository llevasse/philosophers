/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/17 00:48:42 by llevasse         ###   ########.fr       */
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

static int	check_died(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (timestamp() - table->philo[i]->time_since_eat > table->philo[i]->time_to_die)
		{
			print_died(table->philo[i]);
			return (0);
		}
		i++;
	}
	return (i);
}

void	*death_routine(void	*args)
{
	t_table	*table;

	table = (t_table *)args;
	while (1)
	{
		pthread_mutex_lock(&table->read);
		if (table->alive == 1)
			table->alive = check_died(table);
		if (table->alive == 0)
		{
			pthread_mutex_unlock(&table->read);
			break ;
		}
		pthread_mutex_unlock(&table->read);
		usleep(100);
	}
	pthread_exit(NULL);
	return (NULL);
}
