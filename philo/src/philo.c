/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:03:25 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/27 20:02:32 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitoring;

	if (argc == 5 || argc == 6)
	{
		if (parsing(argc, argv, &data))
			return (0);
		data.start_time = get_current_time();
		create_threads(&data);
		pthread_create(&monitoring, NULL, monitoring_routine, &data);
		join_threads(&data);
		pthread_join(monitoring, NULL);
		clean_up(&data);
	}
	else
		error_handling(&data, ERROR_1);
	return (0);
}

int	all_eaten(t_data *data)
{
	int	i;
	int	value;

	i = 0;
	value = check_mutex_var(&data->philos[0], 4);
	pthread_mutex_lock(&data->philos->meal);
	if (data->nbr_philo_eat == -1)
		return (pthread_mutex_unlock(&data->philos->meal), 0);
	pthread_mutex_unlock(&data->philos->meal);
	while (value > i)
	{
		pthread_mutex_lock(&data->philos->meal);
		if (data->philos[i].has_eaten < data->nbr_philo_eat)
		{
			pthread_mutex_unlock(&data->philos->meal);
			return (0);
		}
		i++;
		pthread_mutex_unlock(&data->philos->meal);
	}
	pthread_mutex_lock(&data->snacks_m);
	data->check_snacks = 1;
	pthread_mutex_unlock(&data->snacks_m);
	return (1);
}

int	check_mutex_var(t_philos *philo, int check)
{
	if (check == 1 || check == 2)
		return (check_mutex_1(philo, check));
	else if (check == 3 || check == 4)
		return (check_mutex_2(philo, check));
	else
		return (0);
}

int	check_mutex_1(t_philos *philo, int check)
{
	int	temp_var;

	temp_var = 0;
	if (check == 1)
	{
		pthread_mutex_lock(&philo->data->check_dead_m);
		temp_var = philo->data->check_dead;
		pthread_mutex_unlock(&philo->data->check_dead_m);
		return (temp_var);
	}
	else
	{
		pthread_mutex_lock(&philo->data->snacks_m);
		temp_var = philo->data->check_snacks;
		pthread_mutex_unlock(&philo->data->snacks_m);
		return (temp_var);
	}
}

int	check_mutex_2(t_philos *philo, int check)
{
	int	temp_var;

	temp_var = 0;
	if (check == 3)
	{
		pthread_mutex_lock(&philo->meal);
		temp_var = philo->has_eaten;
		pthread_mutex_unlock(&philo->meal);
		return (temp_var);
	}
	else
	{
		pthread_mutex_lock(&philo->data->nbr_p_m);
		temp_var = philo->data->nbr_of_philos;
		pthread_mutex_unlock(&philo->data->nbr_p_m);
		return (temp_var);
	}
}
