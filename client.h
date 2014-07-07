/*
** client.h for client in /home/zellou_i/rendu/PSU_2013_myftp
** 
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
** 
** Started on  Sat Apr 12 15:18:19 2014 ilyas zelloufi
** Last update Sun Apr 13 18:33:22 2014 ilyas zelloufi
*/

#ifndef CLIENT_H__
# define CLIENT_H__

# define TRUE	1
# define FALSE	0
# define SIZE	300

int		do_client(int);
char		*epur_str(char *);
int		send_file(int, char *);
int		receive_file(int, char *);
char		**my_str_to_wordtab(char *, char);
int		count_word(char *, char);
void		my_exit(char *);

#endif /* CLIENT_H__ */
