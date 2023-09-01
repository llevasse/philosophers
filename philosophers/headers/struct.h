/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:45:10 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/01 23:08:29 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "philosophers.h"

typedef struct s_philo {
	struct timeval	current_time;
	int				is_alive;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	struct timeval	time_since_eating;
	int				time_to_sleep;
	struct timeval	time_since_sleeping;
	int				eaten_times;
	int				succes;
	pthread_mutex_t	fork;
	struct s_philo	*left_buddy;
	struct s_philo	*right_buddy;
	struct s_table	*table;
}	t_philo;

typedef struct s_table {
	struct timeval	init_time;
	int				nb_philo;
	int				nb_rounds;	//one round is ended when each philo eated at least once.
	pthread_t		*threads;
	pthread_mutex_t	write;
	t_philo			**philo;
}	t_table;

#endif
