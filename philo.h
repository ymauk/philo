/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:35:42 by ymauk             #+#    #+#             */
/*   Updated: 2024/09/17 15:14:44 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

//colours
# define B "\033[0;34m"
# define P "\033[0;35m"
# define R "\033[0;31m"
# define G "\033[0;32m"
# define DC "\033[0;39m"
# define Y "\033[0;33m"

typedef struct s_data
{
	int	nbr_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_philo_eat;
	int	nbr_forks;
}t_data;

//parsing
void	input_data(int argc, char **argv, t_data *data);
void	parsing(int argc, char **argv);
void	fill_struct(int argc, char **argv, t_data *data);

//philo

//utils
int		ft_atoi(const char *str);
void	error_handling(char *msg);

//error message
# define ERROR_1 R "Invalid number of arguments\n" DC
# define ERROR_2 R "Invalid input found\n" DC

#endif