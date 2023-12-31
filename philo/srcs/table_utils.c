/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:35:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 23:00:22 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_commun_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->write, NULL))
		return (write_mut_err(), free_table(table), 0);
	return (1);
}

t_table	*init_table(char **argv)
{
	t_table	*table;
	int		i;

	i = 0;
	table = malloc(sizeof(struct s_table));
	if (!table)
		return (write_mem_err(), NULL);
	set_table_null(table);
	table->nb_philo = ft_atoi(argv[1]);
	if (!init_commun_mutex(table))
		return (NULL);
	table->philo = init_philo(table->nb_philo, argv, table);
	if (!table->philo)
		return (free_table(table), NULL);
	table->philo[table->nb_philo] = 0;
	table->threads = malloc(sizeof(pthread_t) * (table->nb_philo + 1));
	if (!table->threads)
	{
		pthread_mutex_destroy(&table->write);
		return (write_mem_err(), free_table(table), NULL);
	}
	while (i < table->nb_philo)
		set_neighboor(table, i++);
	return (table);
}

void	set_table_null(t_table *table)
{
	table->philo = NULL;
	table->threads = NULL;
}

void	free_table(t_table *table)
{
	int	i;

	if (table->philo)
	{
		i = 0;
		while (table->philo[i])
		{
			while (table->philo[i]->fork.__data.__lock == 1)
				;
			pthread_mutex_destroy(&table->philo[i]->fork);
			free(table->philo[i++]);
		}
		free(table->philo);
	}
	if (table->threads)
		free(table->threads);
	free(table);
}
