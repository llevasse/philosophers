/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:58:11 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/04 16:59:05 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table *table;

	if (!is_args_valid(argc, argv))
		return (1);
	table = init_table(argv);
	if (!table)
		return (1);
	pthread_mutex_init(&table->write, NULL);
	create_threads(table);
	if (table->died == 1)
		return (0);
	free_table(table);
	return (0);
}
