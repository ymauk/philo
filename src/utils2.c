/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:31:34 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/11 15:10:25 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	checking_death(t_data *data, int i)
{
	print_message(&data->philos[i], "died");
	pthread_mutex_lock(&data->check_dead_m);
	data->check_dead = 1;
	pthread_mutex_unlock(&data->check_dead_m);
}
