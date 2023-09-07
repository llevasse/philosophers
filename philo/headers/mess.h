/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mess.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:51:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/07 16:28:37 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESS_H
# define MESS_H

# define TOO_SMALL "Not enough arguments.\n"
# define TOO_SMALL_L 22
# define TOO_MANY "Too many arguments.\n"
# define TOO_MANY_L 20
# define BAD_NB_PHILO "Numbers of philosophers is not valid\n"
# define BAD_NB_PHILO_L 37
# define BAD_TIME_DIE "Time to die is not valid\n"
# define BAD_TIME_DIE_L 25
# define BAD_TIME_EAT "Time to eat is not valid\n"
# define BAD_TIME_EAT_L 25
# define BAD_TIME_SLEEP "Time to sleep is not valid\n"
# define BAD_TIME_SLEEP_L 27
# define BAD_NB_EAT "Numbers of time a philosophers must eat is not valid\n"
# define BAD_NB_EAT_L 53

void				print_take_fork(t_philo *buddy, int id);
void				print_release_fork(t_philo *buddy, int id);
void				print_eat(t_philo *buddy);
void				print_sleep(t_philo *buddy);
void				print_think(t_philo *buddy);
void				print_died(t_philo *buddy);

#endif
