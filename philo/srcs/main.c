/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:58:11 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/08 11:25:22 by llevasse         ###   ########.fr       */
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
	create_threads(table);
	free_table(table);
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->read);
	return (0);
}
