/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szverhov <szverhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:54:24 by szverhov          #+#    #+#             */
/*   Updated: 2017/10/30 12:15:13 by szverhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_SERVER_H
# define MAIN_SERVER_H

# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <unistd.h>

# define MYPORT "3433"
# define BACKLOG 3

typedef struct	s_m
{
	struct sockaddr_storage	their_addr;
	socklen_t				addr_size;
	struct addrinfo			hints;
	struct addrinfo			*res;
	int						sockfd;
	int						new_fd;
	char					buff[100000];
	char					**files;
	int						i;
	int						count_players;
	char					**clients_ip;
	char					*my_ip;
	fd_set					set;
	struct timeval			timeout;
	int						rv;
}				t_m;

typedef struct	s_sdtc
{
	int				i;
	int				status;
	struct addrinfo	hints;
	struct addrinfo	*res;
	int				sockfd;
	char			*res_str;
}				t_sdtc;

void			ft_add_num_sz(char *ip, char **res, int *adds);
char			*ft_make_serv_ip_sz(char *ip);
char			*ft_get_ip_sz();
char			*ft_get_client_ip_sz(char **files, int num_file);
int				ft_allready_send_sz(char **clients_ip, int *i);
int				ft_atoi_sz(char *str);
int				ft_sl_sz(char *str);
void			ft_reall_sz(char **str, char *tmp);
int				ft_strcmp_sz(const char *s1, const char *s2);
char			*ft_sub_str_sz(char *str, char end);
void			ft_creat_file_sz(char *buf);
int				ft_remove_name_sz(char *buf);
void			ft_start_war_sz(char **files);
void			ft_asm_sz(char **files);
void			ft_execute_asm_and_start_sz(char **files);
void			ft_send_inner_sz(t_sdtc *v, char **clients_ip);
void			ft_send_data_to_clients_sz(char **files, char **clients_ip);
int				ft_check_args_sz(int argc, char **argv, int *count_players);
char			*ft_free_return_zero(char **str);
void			ft_rm_rf_cors(char **names);

#endif
