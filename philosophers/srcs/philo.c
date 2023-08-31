/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:27:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/31 22:51:20 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_philo(t_table *table, int id)
{
	printf("philo id : %d\n", table->philo[id]->id);
	printf("philo time to die : %d\n", table->philo[id]->time_to_die);
	printf("philo time to eat : %d\n", table->philo[id]->time_to_eat);
	printf("philo time to sleep : %d\n", table->philo[id]->time_to_sleep);
	printf("philo left buddy id : %d\n", table->philo[id]->left_buddy->id);
	printf("philo right buddy id : %d\n", table->philo[id]->right_buddy->id);
}

t_philo **init_philo(int max_id)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(struct s_philo *) * (max_id + 1));
	if (!philo)
		return (NULL);
	while (i < max_id)
	{
		philo[i] = malloc(sizeof(struct s_philo));
		if (!philo[i++])
			break ;
		philo[i] = NULL;
	}
	if (i-- < max_id)
	{
		while (i >= 0)
			free(philo[i--]);
		free(philo);
		philo = 0;
		return (0);
	}
	return (philo);

}

void	set_philo(char **argv, t_table *table, int buddy_id)
{
	int		right_id;
	int		left_id;

	left_id = buddy_id - 1;
	right_id = buddy_id + 1;
	if (buddy_id == 0)
		left_id = ft_atoi(argv[1]) - 1;
	if (buddy_id == ft_atoi(argv[1]) - 1)
		right_id = 0;
	table->philo[buddy_id]->id = buddy_id;
	table->philo[buddy_id]->time_to_die = ft_atoi(argv[2]);
	table->philo[buddy_id]->time_to_eat = ft_atoi(argv[3]);
	table->philo[buddy_id]->time_to_sleep = ft_atoi(argv[4]);
	table->philo[buddy_id]->eaten_times = 0;
	table->philo[buddy_id]->left_buddy = table->philo[left_id];
	table->philo[buddy_id]->right_buddy = table->philo[right_id];
}
