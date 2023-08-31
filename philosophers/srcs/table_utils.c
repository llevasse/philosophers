/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:35:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/31 16:40:50 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_table	*init_table(char **argv)
{
	t_table *table;

	table = malloc(sizeof(struct s_table));
	if (!table)
		return (NULL);
	table->philo = malloc(sizeof(struct s_philo) * ft_atoi_ullong(argv[1]) + 1);
	if (!table->philo)
		return (free(table), NULL);
	table->threads = malloc(sizeof(pthread_t) * ft_atoi_ullong(argv[1]) + 1);
	if (!table->philo)
		return (free(table->philo), free(table), NULL);
	return (table);
}

void	free_table(t_table *table)
{
	free(table->philo);
	free(table->threads);
	free(table);
}
