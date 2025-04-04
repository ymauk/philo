/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:17:37 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/04 11:45:43 by ymauk            ###   ########.fr       */
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
	if (argv[1][0] == '1')
		return (one_philo(argv), 1);
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
}

void	create_philos(t_data *data)
{
	t_philos	*philo;
	t_philos	*current;
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
	if (data->philos)
	{
		current = data->philos;
		while (current->next)
			current = current->next;
		current->next = data->philos;
	}
}

void	clean_up(t_data *data)
{
	int			i;
	int			nbr_philos;

	i = 0;
	if (data->philos)
	{
		nbr_philos = data->nbr_of_philos;
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->check_dead_m);
		while (nbr_philos > i)
		{
			pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->philos[i].meal);
			i++;
		}
		free(data->philos);
		free(data->forks);
	}
}
