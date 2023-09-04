/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/04 22:30:57 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (table->philo[i]->is_alive == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	detach_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
		pthread_detach(table->threads[i++]);
}

void	*death_routine(void	*args)
{
	t_table	*table;

	table = (t_table *)args;
	while (table->died == 0)
	{
		if (check_death(table))
			break ;
	}
	detach_threads(table);
	pthread_exit(NULL);
	return (NULL);
}
