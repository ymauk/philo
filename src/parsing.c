/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:17:37 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/03 10:21:21 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	parsing(int argc, char **argv, t_data *data)
{
	if (argc == 5 || argc == 6)
	{
		checking_input(argc, argv);
		fill_struct(argc, argv, data);
		create_philos(data);
	}
	else
		error_handling(ERROR_1);
}

void	checking_input(int argc, char **argv)
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
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philos);
	if (!philo)
		error_handling(ERROR_3);
	while (data->nbr_of_philos > i)
	{
		philo[i].id_philo = i + 1;
		// philo[i].last_meal = philo->data->start_time;
		philo[i].data = data;
		philo[i].next = NULL;
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&philo[i].meal, NULL);
		ft_lstadd_back_ph(&data->philos, &philo[i]);
		i++;
	}
	// pthread_mutex_init(&data->check_dead_m, NULL);
	pthread_mutex_init(&data->print, NULL);
	if (data->philos)
	{
		current = data->philos;
		while (current->next)
			current = current->next;
		current->next = data->philos;
	}
}

// void	clean_up(t_data *data)
// {
// 	int	i;

// 	while (data->nbr_of_philos > i)
// 	{
// 		pthread_mutex_destroy(&data->forks[i]);
// 		pthread_mutex_destroy(&philo[i].meal_mutex);

// 	}
// }
