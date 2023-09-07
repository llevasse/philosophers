/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:25:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/07 15:22:11 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//static int	check_death(t_table *table)
//{
//	int	i;
//
//	i = 0;
//	while (i < table->nb_philo)
//	{
//		if (table->philo[i]->is_alive == 0)
//			return (1);
//		i++;
//	}
//	return (0);
//}

void	detach_threads(t_table *table)
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
	while (1)
	{
		pthread_mutex_lock(&table->read);
		if (table->alive == 0)
		{
			pthread_mutex_unlock(&table->read);
//			detach_threads(table);
			break ;
		}
		pthread_mutex_unlock(&table->read);
	}
	pthread_exit(NULL);
	return (NULL);
}
