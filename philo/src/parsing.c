/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:17:37 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/27 15:47:03 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	parsing(int argc, char **argv, t_data *data)
{
	if (checking_input(data, argc, argv))
		return (1);
	fill_struct(argc, argv, data);
	create_philos(data);
	return (0);
}

int	checking_input(t_data *data, int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (i < 6 && argv[i][0] == '0')
				return (error_handling(data, ERROR_2), 1);
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (error_handling(data, ERROR_2), 1);
			j++;
		}
		i++;
	}
	return (0);
}

void	fill_struct(int argc, char **argv, t_data *data)
{
	data->nbr_of_philos = ft_atoi(argv[1]);
	data->time_to_die = (size_t)ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_philo_eat = ft_atoi(argv[5]);
	else
		data->nbr_philo_eat = -1;
	data->check_dead = 0;
	data->start_time = 0;
	data->philos = NULL;
	data->forks = NULL;
	data->check_snacks = 0;
}

void	create_philos(t_data *data)
{
	t_philos	*philo;
	int			i;

	i = 0;
	philo = malloc((sizeof(t_philos) * data->nbr_of_philos));
	if (!philo)
		error_handling(data, ERROR_3);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philos);
	if (!data->forks)
		error_handling(data, ERROR_3);
	while (data->nbr_of_philos > i)
	{
		philo[i].id_philo = i + 1;
		philo[i].data = data;
		philo[i].next = NULL;
		philo[i].has_eaten = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&philo[i].meal, NULL);
		ft_lstadd_back_ph(&data->philos, &philo[i]);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->check_dead_m, NULL);
	pthread_mutex_init(&data->snacks_m, NULL);
	create_philos2(data);
}

void	create_philos2(t_data *data)
{
	t_philos	*current;

	if (data->philos)
	{
		current = data->philos;
		while (current->next)
			current = current->next;
		current->next = data->philos;
	}
}
