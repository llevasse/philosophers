/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:27:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/10 19:19:00 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	add_philo_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(
				&table->threads[i], NULL, &alive_routine, table->philo[i]))
			return (0);
		i++;
	}
	return (1);
}

void	create_threads(t_table *table)
{
	int	i;

	table->init_time = timestamp(table->curr_time) + (table->philo[0]->time_to_sleep * 2);
	pthread_mutex_lock(&table->read);
	add_philo_thread(table);
	pthread_mutex_unlock(&table->read);
	if (pthread_create(&table->death, NULL, &death_routine, table))
		return ;
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_join(table->threads[i], NULL))
			return ;
		i++;
	}
	if (pthread_join(table->death, NULL))
		return ;
}

t_philo	**init_philo(int max_id, char **argv, t_table *table)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(struct s_philo *) * (max_id + 1));
	if (!philo)
		return (write_mem_err(), NULL);
	while (i < max_id)
	{
		philo[i] = set_philo(argv, table, i);
		if (!philo[i++])
			break ;
		philo[i] = NULL;
	}
	if (i-- < max_id)
	{
		while (i >= 0)
		{
			pthread_mutex_destroy(&philo[i]->fork);
			free(philo[i--]);
		}
		return (free(philo), NULL);
	}
	return (philo);
}

t_philo	*set_philo(char **argv, t_table *table, int buddy_id)
{
	t_philo	*philo;

	philo = malloc(sizeof(struct s_philo));
	if (!philo)
		return (write_mem_err(), NULL);
	philo->is_alive = 1;
	philo->id = buddy_id;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->eaten_times = 0;
	if (pthread_mutex_init(&philo->fork, NULL))
		return (write_mut_err(), free(philo), NULL);
	philo->table = table;
	return (philo);
}

void	set_neighboor(t_table *table, int buddy_id)
{
	int	right_id;
	int	left_id;

	left_id = buddy_id - 1;
	right_id = buddy_id + 1;
	if (buddy_id == 0)
		left_id = table->nb_philo - 1;
	if (buddy_id == table->nb_philo - 1)
		right_id = 0;
	table->philo[buddy_id]->left_buddy = table->philo[left_id];
	table->philo[buddy_id]->right_buddy = table->philo[right_id];
}
