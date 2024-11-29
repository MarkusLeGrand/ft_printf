#include "ft_printf.h"

// Fonction auxiliaire pour afficher une chaîne
static void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

// Fonction auxiliaire pour afficher un nombre en hexadécimal
static void	ft_puthex(unsigned long num)
{
	if (num >= 16)
		ft_puthex(num / 16);
	write(1, &"0123456789abcdef"[num % 16], 1);
}

// Fonction pour calculer la longueur d'un nombre en hexadécimal
static int	ft_hex_len(unsigned long num)
{
	int	len;

	len = 1;
	while (num >= 16)
	{
		num /= 16;
		len++;
	}
	return (len);
}

int	ft_print_pointer(void *ptr)
{
	int	len;

	if (!ptr)
	{
		ft_putstr("(nil)");
		return (5); // Taille de "(nil)"
	}
	ft_putstr("0x"); // Affiche "0x"
	len = 2; // Compte "0x"
	ft_puthex((unsigned long)ptr); // Affiche l'adresse en hexadécimal
	len += ft_hex_len((unsigned long)ptr); // Ajoute la longueur de l'hexadécimal
	return (len);
}
