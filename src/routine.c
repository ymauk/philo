/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:11:00 by ymauk             #+#    #+#             */
/*   Updated: 2024/11/27 18:24:50 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_threads(t_data *data)
{
	t_philos	*cur_ph;
	int			i;

	cur_ph = data->philos;
	i = 0;
	while (data->nbr_of_philos > i)
	{
		pthread_create(&cur_ph->thread, NULL, start_routine, (void *)cur_ph);
		cur_ph = cur_ph->next;
		i++;
	}
}

void	join_threads(t_data *data)
{
	t_philos	*cur_ph;
	int			i;

	cur_ph = data->philos;
	i = 0;
	while (data->nbr_of_philos > i)
	{
		pthread_join(cur_ph->thread, NULL);
		cur_ph = cur_ph->next;
		i++;
	}
}

void	*start_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	// while (1)
	// {
	// 	pthread_mutex_lock(&philo->data->start);
	// 	if (philo->data->start_simulation)
	// 	{
	// 		pthread_mutex_unlock(&philo->data->start);
	// 		break;
	// 	}
	// 	pthread_mutex_unlock(&philo->data->start);
	// 	usleep(100); // Kurze Pause, um CPU-Last zu reduzieren
	// // }
	// if (philo->id_philo % 2 == 0)
	// 	ft_usleep(philo->data->time_to_eat / 2);
	while (!philo->data->check_dead
		&& philo->has_eaten != philo->data->nbr_philo_eat)
	{
		thinking((void *) philo);
		// ft_usleep(1000);
		take_forks((void *) philo);
		eating((void *) philo);
		putdown_forks((void *) philo);
		go_sleep((void *) philo);
	}
	return (NULL);
}

void	print_message(t_philos *philo, const char *status)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%zu %d %s\n", get_current_time()
		- philo->data->start_time, philo->id_philo, status);
	pthread_mutex_unlock(&philo->data->print);
}

// void	*monitoring_routine(void *arg)
// {
// 	t_data	*data;
// 	int		i;

// 	i = 0;
// 	data = (t_data *)arg;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&data->philos[i].meal_mutex);
// 		while (data->nbr_of_philos > i)
// 		{
// 			if (get_current_time() - data->philos[i].last_meal
// 				> data->time_to_die)
// 			{
// 				printf("%zu %d has taken a fork\n", get_current_time()
// 					- data->start_time, data->philos[i].id_philo);
// 				data->check_dead = 1;
// 				pthread_mutex_unlock(&data->philos[i].meal_mutex);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&data->philos[i].meal_mutex);
// 			i++;
// 		}
// 		ft_usleep(1000);
// 	}
// 	return (NULL);
// }
