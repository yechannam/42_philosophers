/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:03:03 by yecnam            #+#    #+#             */
/*   Updated: 2023/02/21 18:10:03 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_info
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				flag;
	int				finish_eating;
	long long		start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}	t_info;

typedef struct s_philo
{
	int				num;
	int				right;
	int				left;
	int				count_eat;
	int				eating_end;
	long long		last_eat;
	struct s_info	*info;
	pthread_t		thread;
}	t_philo;

int			free_fork(t_info *info);
int			free_philo_fork(t_philo **philo, t_info *info);
void		thread_init(t_info *info, t_philo *philo);
int			fork_init(t_info *info);
int			info_init(int argc, char **argv, t_info *info);
int			philo_init(t_philo **philo, t_info *info);
void		*thread_ing(void *data);
long long	ft_gettime(void);
void		print_state(t_philo philo, t_info info, char *msg);

#endif