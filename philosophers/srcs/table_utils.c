/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:35:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/31 22:32:12 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_table	*init_table(char **argv)
{
	t_table *table;
	int	i;
	int	id;

	i = 0;
	table = malloc(sizeof(struct s_table));
	if (!table)
		return (NULL);
	set_table_null(table);
	id = ft_atoi(argv[1]);
	table->philo = init_philo(id);
	if (!table->philo)
		return (free_table(table), NULL);
	table->philo[id] = 0;
	table->threads = malloc(sizeof(pthread_t) * (id + 1));
	if (!table->threads)
		return (free_table(table), NULL);
	while (i < id)
		set_philo(argv, table, i++);
	print_philo(table, 0);
	return (table);
}

void	set_table_null(t_table *table)
{
	table->philo = NULL;
	table->threads = NULL;
}

void	free_table(t_table *table)
{
	if (table->philo)
		free(table->philo);
	if (table->threads)
		free(table->threads);
	free(table);
}
