/*
** serveur.h for server.h in /home/zellou_i/rendu/PSU_2013_myftp
** 
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
** 
** Started on  Sat Apr 12 16:40:14 2014 ilyas zelloufi
** Last update Sun Apr 13 20:56:46 2014 ilyas zelloufi
*/

#ifndef			SERVEUR_H__
# define		SERVEUR_H__
# define		TRUE	1
# define		FALSE	0
# define		SIZE	300

# include		"file.h"

typedef struct		s_cmd
{
  char			*cmd;
  int			(*fptr)(int, char *);
}			t_cmd;

int			my_server(int, char *);
int			my_put(int, char *);
int			my_get(int, char *);
int			my_ls(int, char *);
int			my_pwd(int, char *);
int			count_word(char *, char);
char			**my_str_to_wordtab(char *, char);
void			my_exit(char *);

#endif			/* !SERVEUR_H__ */
