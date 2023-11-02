
#include "./philosophers.h"

// check args all num
int ft_checkallnum(char **str)
{
    int i;
    i = 1;
    if (ft_atoi(str[1]) > 200)
        {
            printf("Input Error: more than 200 philo\n");
            exit(EXIT_FAILURE);
        }
    while (str[i])
    {
        if (!ft_isalldigit(str[i]))
        {
            printf("Input Error: not numeric\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return(0);
}
int main(int argc, char **argv)
{
    // fix paths for 5 or 6
    if (argc == 5)
    {
        // if (argc)
    }
    else
    {
        printf("Input Error: args number\n");
        return(EXIT_FAILURE);
    }
    ft_checkallnum(argv);
    // two paths design for 5 and 4 args
    (void) argv;
    return(EXIT_SUCCESS);
}