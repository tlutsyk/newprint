/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 14:39:48 by tlutsyk           #+#    #+#             */
/*   Updated: 2017/12/25 14:39:50 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

/*
*** after outputs spec -> defoult struct flags
*/

void	ft_defolt_struct(t_struct *flags)
{
	flags->min_size = -1;
	flags->presizion = -1;
	flags->print_size = 0;
	flags->space = -1;
	flags->plus = '\0';
	flags->minus = '\0';
	flags->zero = '\0';
	flags->sharp = 0;
	flags->mod_size = '\0';
	flags->count_nb = 0;
	flags->char_costil = '\0';
	flags->size = 0;
	flags->src = NULL;
}

/*
*** when i find a spec start modul.functions
*/

void 	ft_print_argument(char format, va_list ap, t_struct *flags)
{
	if (format == 's')
		ft_print_s(ap, flags, 0);
	if ((format == 'c' || format == '%') && (flags->char_costil = format))
		ft_start_read_c('\0', ap, flags);
	if (format == 'p')
		ft_print_p(ap, flags);
	if (format == 'S')
		ft_unic_string(ap, flags);
	if (format == 'C')
		ft_print_unicode_char(ap, flags);
	if (format == 'd' || format == 'i')
		ft_print_integer(ap, flags);
	if (format == 'D')
		ft_print_big_integer(ap, flags);
	if (format == 'o' || format == 'O')
		ft_print_o(ap, flags, format);
	if (format == 'u')
		ft_undigit(ap, flags);
	if (format == 'U')
		ft_un_big_digit(ap, flags);
	if (format == 'x' || format == 'X')
		ft_print_x(ap, flags, format);
}


int ft_read_nbsize_flags(char *format, t_struct *flags)
{
	int a;

	a = 1;
	if (*format == 'z' && (a = 1))
		flags->mod_size = 'z';
	else if (*format == 'j' && flags->mod_size != 'z' && (a = 1))
		flags->mod_size = 'j';
	else if (*format == 'l' && *(format + 1) == 'l' && \
		flags->mod_size != 'j' && flags->mod_size != 'z' && (a = 2))
		flags->mod_size = 'L';
	else if (*format == 'l' && flags->mod_size != 'L' && \
		flags->mod_size != 'j' && flags->mod_size != 'z' && (a = 1))
		flags->mod_size = 'l';
	else if (*format == 'h' && *(format + 1) != 'h' &&\
		flags->mod_size != 'l' && flags->mod_size != 'L' \
		&& flags->mod_size != 'j' && flags->mod_size != 'z' && (a = 1))
		flags->mod_size = 'h';
	else if (*format == 'h' && *(format + 1) == 'h' &&\
		flags->mod_size != 'h'&& flags->mod_size != 'l' \
		&& flags->mod_size != 'L' && flags->mod_size != 'j'\
		 && flags->mod_size != 'z' && (a = 2))
		flags->mod_size = 'H';
	return(a);
}

/*
*** read spec and write them to struct 
*/

void	ft_write_to_struct_mod_flags(char mod, t_struct *flags)
{
	if (mod == ' ')
			flags->space = 1;
		if (mod == '#')
			flags->sharp = 1;
		if (mod == '-')
			flags->minus = '-';
		if (mod == '+')
			flags->plus = '+';
}

int		ft_read_spec(char *format, t_struct *flags)
{
	int index;

	index = 0;
	while (format[index] != '\0' && !(SPEC_PER(format[index])))
	{	
		if (FLAGS(format[index]))
		{
			ft_write_to_struct_mod_flags(format[index], flags);
			index++;
		}
		if (format[index] == '0' && ++index)
			flags->zero = '0';
		if (ft_isdigit(format[index]))
			flags->min_size = flags->min_size > ft_atoi(&format[index]) ? flags->min_size : ft_atoi(&format[index]);
		while (ft_isdigit(format[index]))
			index++;
		if (format[index] == '.' && ft_isdigit(format[index + 1]))
			flags->presizion = ft_atoi(&format[++index]);
		if (format[index] == '.' && !(ft_isdigit(format[index + 1])) && ++index)
			flags->presizion = 0;
		while (ft_isdigit(format[index]))
			index++;
		if (FLAGS_SIZE(format[index]))
			index += ft_read_nbsize_flags(&format[index], flags);
		if ((format[index] == '\0') || ((INCORRECT_FORMAT(format[index]))))
			break ;
	}
	return (index);
}


void	ft_start_read_c(char format, va_list ap, t_struct *flags)
{
	char alpha;

	if (flags->mod_size == 'l')
	{
		ft_print_unicode_char(ap, flags);
		return ;
	}
	if (format != '\0')
		alpha = format;
	else 
		alpha = va_arg(ap, int);
	ft_print_c(alpha, flags);
}

/*
*** one loop to read my format string
*/

int 	ft_read_spec_start(char *format, va_list ap, t_struct *flags)
{
	int index = 0;

	index = ft_read_spec(format, flags);
	if (INCORRECT_FORMAT(format[index]))
		ft_start_read_c(format[index], ap, flags);
	else if (SPEC_PER(format[index]))
	{
		if (format[index] == '%')
			ft_start_read_c('%', ap, flags);
		else
			ft_print_argument(format[index], ap, flags);
	}
	ft_defolt_struct(flags);
	return (index);

}

void	ft_start_read(char *format, va_list ap, t_struct *flags)
{
	int index = 0;
	while (*format != '\0' && flags->un_costil == 1)
	{
		while (*format && *format != '%' && ++(flags->write_count))
			ft_putchar(*format++);
		if (*format == '%' && format++)
		{
			if (*format == '\0')
				return ;
			else
			{
				index = ft_read_spec_start(format, ap, flags);
				if (*(format + index) == '\0')
					return ;
				else
					format = format + index + 1;
			}
		}
	}
}

/*
*** inizial struct and inizial va_arg
*/

int		ft_printf(const char *format, ...)
{
	t_struct flags;
	flags.write_count = 0;
	flags.un_costil = 1;
	va_list ap;
	va_start(ap, format);
	ft_defolt_struct(&flags);
	if (*format == '\0')
		return (0);
	ft_start_read((char *)format, ap, &flags);
	va_end(ap);
	if (flags.un_costil == -1)
		return (-1);
	return (flags.write_count);
}
