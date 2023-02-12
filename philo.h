/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:03:03 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/12 14:55:55 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	int	num;
	int	last_eat;
}	t_philo;

typedef struct s_info
{
	int		argc;
	char	**argv;
	int		philo_num;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		must_eat;
	int		start_time;
}	t_info;

#endif