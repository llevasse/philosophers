/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/04 16:56:59 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		gettimeofday(&table->current_time, NULL);
		if (table->philo[i]->current_time.tv_usec - table->philo[i]->time_since_eating.tv_usec < \
			table->philo[i]->time_to_die)
			return (1);
		i++;
	}
	return (0);
}

void	*death_routine(void	*args)
{
	t_table	*table;

	table = (t_table *)args;
	while (table->died == 0)
	{
		if (!check_death(table))
			usleep(table->philo[0]->time_to_die);
		else
			table->died = 1;
	}
	pthread_exit(NULL);
	return (NULL);
}
