# ft_printf

> Réimplémentation de la fonction `printf` de la libc en C, compilée sous forme de bibliothèque statique `libftprintf.a`.

![Langage C](https://img.shields.io/badge/langage-C-blue)
![École 42](https://img.shields.io/badge/école-42-black)

## À propos

`ft_printf` est un projet du tronc commun de l'école 42. L'objectif est de recoder `printf` sans utiliser la fonction originale : parser une chaîne de format, récupérer un nombre variable d'arguments avec `<stdarg.h>` et écrire le résultat sur la sortie standard avec le seul appel système `write`.

Comme la vraie fonction, `ft_printf` renvoie le nombre de caractères écrits.

```c
int ft_printf(const char *format, ...);
```

## Fonctionnalités

Conversions gérées (partie obligatoire du sujet) :

| Spécificateur | Type attendu      | Sortie                                         |
|---------------|-------------------|------------------------------------------------|
| `%c`          | `int` (caractère) | un caractère                                   |
| `%s`          | `char *`          | une chaîne (`(null)` si le pointeur est `NULL`) |
| `%p`          | `void *`          | adresse en hexadécimal préfixée `0x` (`(nil)` si `NULL`) |
| `%d` / `%i`   | `int`             | entier signé en base 10                        |
| `%u`          | `unsigned int`    | entier non signé en base 10                    |
| `%x` / `%X`   | `unsigned int`    | hexadécimal minuscule / majuscule              |
| `%%`          | —                 | le caractère `%`                               |

Les flags du bonus (`-`, `0`, `.`, `#`, `+`, espace, largeur de champ) ne sont pas implémentés.

## Compilation & utilisation

```bash
make        # compile libftprintf.a
make clean  # supprime les fichiers objets
make fclean # supprime les objets et la bibliothèque
make re     # recompile entièrement
```

Le Makefile compile avec `cc -Wall -Wextra -Werror` et archive les objets avec `ar rcs`.

Pour utiliser la bibliothèque dans un programme :

```bash
make
cc -Wall -Wextra -Werror main.c libftprintf.a -o test
./test
```

Avec le `main.c` fourni dans le dépôt :

```
Char: A
String: Hello, World!
Pointer: 0x1e240
Decimal: 42
Unsigned: 42
Hex (lower): ff
Hex (upper): FF
Percent: %
```

## Approche technique

Le code suit un découpage en trois niveaux, une fonction par responsabilité :

1. **`ft_printf`** initialise la `va_list` (`va_start` / `va_end`) et délègue le travail.
2. **`handle_format`** parcourt la chaîne caractère par caractère : le texte brut est écrit directement, et chaque `%` suivi d'un caractère déclenche une conversion. Le compteur de caractères écrits est cumulé au fil du parcours.
3. **`handle_conversion`** aiguille vers la fonction d'affichage adaptée selon le spécificateur, en extrayant l'argument avec le bon type via `va_arg`.

Points notables :

- **Une routine générique de conversion de base** : `ft_print_number_base(unsigned long long n, const char *base)` remplit un buffer local de 50 caractères en partant de la fin, puis l'écrit en un seul `write`. Elle sert à la fois pour `%u` (base `"0123456789"`), `%x` et `%X` (bases hexadécimales minuscule et majuscule) : ajouter une base ne demande qu'une nouvelle chaîne de chiffres.
- **`%d` / `%i`** passent par un `ft_itoa` interne qui travaille sur un `long` pour gérer correctement `INT_MIN`.
- **`%p`** convertit l'adresse en `unsigned long` et l'affiche récursivement en hexadécimal ; la longueur est calculée séparément pour renvoyer un compte exact.
- **Cas limites** : `%s` avec `NULL` affiche `(null)` et `%p` avec `NULL` affiche `(nil)`, comme la glibc.

## Structure du projet

```
ft_printf/
├── Makefile
├── ft_printf.h              # prototypes
├── ft_printf.c              # point d'entrée, gestion de la va_list
├── ft_handle_format.c       # parcours de la chaîne de format
├── ft_handle_conversion.c   # dispatch selon le spécificateur
├── ft_print_char.c          # %c
├── ft_print_string.c        # %s
├── ft_print_pointer.c       # %p
├── ft_print_int.c           # %d %i (itoa interne)
├── ft_print_unsigned.c      # %u
├── ft_print_hex.c           # %x %X
├── ft_utils.c               # ft_strlen, ft_print_number_base
└── main.c                   # programme de test
```

## Ce que j'ai appris

- Manipuler les **fonctions variadiques** en C (`va_list`, `va_start`, `va_arg`, `va_end`) et l'importance de lire chaque argument avec le bon type.
- Structurer un projet en **petites fonctions spécialisées** reliées par un dispatcher, plutôt qu'une seule fonction monolithique.
- Factoriser la conversion numérique avec une **fonction de base générique**.
- Produire une **bibliothèque statique** (`ar rcs`) et l'intégrer dans d'autres projets : ce `ft_printf` est réutilisé dans mes projets Minitalk et push_swap.
