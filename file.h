/*
** file.h for file in /home/zellou_i/rendu/PSU_2013_myftp
** 
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
** 
** Started on  Sun Apr 27 17:49:56 2014 ilyas zelloufi
** Last update Sun Apr 27 17:49:58 2014 ilyas zelloufi
*/

#ifndef			FILE_H__
# define		FILE_H__

# define		SIZE	300

typedef struct		s_file
{
  FILE			*fd;
  int			f;
  unsigned long	      	size_file;
  char			buff[SIZE];
  unsigned long		sent;
  char			size[60];
  int			i;
  int			ret;
}			t_file;

#endif			/* FILE_H__ */
