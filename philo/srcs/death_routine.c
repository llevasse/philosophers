/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/10 10:41:40 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_eat_times(t_table *table)
{
	int	i;

	i = 0;
	if (table->nb_rounds == -1)
		return (1);
	pthread_mutex_lock(&table->write);
	while (i < table->nb_philo)
	{
		if (table->philo[i]->eaten_times < table->nb_rounds)
			break ;
		i++;
	}
	if (i == table->nb_philo)
		i = 0;
	else
		i = 1;
	pthread_mutex_unlock(&table->write);
	return (i);
}

void	*death_routine(void	*args)
{
	t_table	*table;

	table = (t_table *)args;
	while (1)
	{
		if (table->alive.__data.__lock == 0)
		{
			if (check_eat_times(table) == 0 && table->alive.__data.__lock == 0)
				pthread_mutex_lock(&table->alive);
		}
		if (table->alive.__data.__lock == 1)
			break ;
	}
	pthread_exit(NULL);
	return (NULL);
}
