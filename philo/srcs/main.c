/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:58:11 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/13 15:30:50 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	if (!is_args_valid(argc, argv))
		return (1);
	table = init_table(argv);
	if (!table)
		return (1);
	table->nb_rounds = -1;
	i = 0;
	if (argc == 6)
	{
		while (table->philo[i])
			table->philo[i++]->eaten_times = ft_atoi(argv[5]);
	}
	if (pthread_mutex_init(&table->write, NULL))
		return (write_mut_err(), free_table(table), 12);
	if (pthread_mutex_init(&table->read, NULL))
		return (write_mut_err(), free_table(table), 12);
	create_threads(table);
	free_table(table);
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->read);
	return (0);
}
