/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:35:42 by ymauk             #+#    #+#             */
/*   Updated: 2024/11/26 16:50:07 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

//colours
# define B "\033[0;34m"
# define P "\033[0;35m"
# define R "\033[0;31m"
# define G "\033[0;32m"
# define DC "\033[0;39m"
# define Y "\033[0;33m"

typedef struct s_data
{
	struct s_philos	*philos;
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_philo_eat;
	size_t			start_time;
	int				check_dead;
	pthread_mutex_t	check_dead_m;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philos
{
	struct s_data	*data;
	struct s_philos	*next;
	int				id_philo;
	int				has_eaten;
	size_t			last_meal;
	pthread_t		thread;
}	t_philos;


//parsing
void	parsing(int argc, char **argv, t_data *data);
void	checking_input(int argc, char **argv);
void	fill_struct(int argc, char **argv, t_data *data);
void	create_philos(t_data *data);

//philo
int		main(int argc, char **argv);
void	print_philos(t_philos *head, int nbr_of_philos); //rausmachen
void	debug_philos_list(t_philos *philos, int nbr_of_philos); //rausmachen

//utils
int		ft_atoi(const char *str);
void	error_handling(char *msg);
void	ft_lstadd_back_ph(t_philos **lst, t_philos *new);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);

//routine
void	*start_routine(void *arg);
void	create_threads(t_data *data);
void	join_threads(t_data *data);

//messages
void	thinking(void *arg);
void	eating(void *arg);
void	take_forks(void *arg);
void	putdown_forks(void *arg);
void	sleep(void *arg);

//error message
# define ERROR_1 R "Invalid number of arguments\n" DC
# define ERROR_2 R "Invalid input found\n" DC
# define ERROR_3 R "Allocation of Memory has failed" DC

#endif