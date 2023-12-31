/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mess.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:51:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/18 14:06:03 by llevasse         ###   ########.fr       */
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
# define MEM_ERR "Memory initialization error\n"
# define MEM_ERR_L 28 
# define MUT_ERR "Mutex initialization error\n"
# define MUT_ERR_L 27 
# define THR_ERR "Thread initialization error\n"
# define THR_ERR_L 28 
# define TJOIN_ERR "Thread join error\n"
# define TJOIN_ERR_L 18 

void				write_mem_err(void);
void				write_mut_err(void);
void				write_thread_err(void);
void				write_join_err(void);
char				*ft_itoa(int n);

void				print_died(t_philo *buddy);
void				print_messages(t_philo *buddy, char *mess);

#endif
