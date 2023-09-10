/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:58:11 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/10 10:48:54 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!is_args_valid(argc, argv))
		return (1);
	table = init_table(argv);
	if (!table)
		return (1);
	table->nb_rounds = -1;
	if (argc == 6)
		table->nb_rounds = ft_atoi(argv[5]);
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->read, NULL);
	pthread_mutex_init(&table->alive, NULL);
	create_threads(table);
	if (table->alive.__data.__lock == 1)
		pthread_mutex_unlock(&table->alive);
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->alive);
	pthread_mutex_destroy(&table->read);
	free_table(table);
	return (0);
}
