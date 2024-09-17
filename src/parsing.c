/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:17:37 by ymauk             #+#    #+#             */
/*   Updated: 2024/09/17 15:17:59 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	input_data(int argc, char **argv, t_data *data)
{
	if (argc == 5 || argc == 6)
	{
		parsing(argc, argv);
		fill_struct(argc, argv, data);
	}
	else
		error_handling(ERROR_1);
}

void	parsing(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (i < 5 && argv[i][0] == '0')
				error_handling(ERROR_2);
			if (argv[i][j] < '0' || argv[i][j] > '9')
				error_handling(ERROR_2);
			j++;
		}
		i++;
	}
}

void	fill_struct(int argc, char **argv, t_data *data)
{
	data->nbr_philo = ft_atoi(argv[1]);
	data->nbr_forks = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_philo_eat = ft_atoi(argv[5]);
}
