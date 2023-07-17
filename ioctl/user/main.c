#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include "../common/cmd.h"

static char s_name[MAX_NAME_SIZE] = {0};
int main(int argc, char **argv)
{
    int fp;
    char *name = "hehe";
    if (argc == 2)
    {
        name = argv[1];
    }

    fp = open(DEV_NAME_FULL, 0);
    if (fp < 0)
    {
        printf("open %s failed.\n", DEV_NAME_FULL);
        exit(-1);
    }

    if (ioctl(fp, IOC_TEST_GET_NAME, s_name) != 0)
    {
        printf("IOC_TEST_GET_NAME failed.\n");
        exit(-1);
    }
    printf("name:%s\n", s_name);

    if (ioctl(fp, IOC_TEST_START, 0) != 0)
    {
        printf("IOC_TEST_START failed.\n");
        exit(-1);
    }

    if (ioctl(fp, IOC_TEST_SET_NAME, name) != 0)
    {
        printf("IOC_TEST_SET_NAME failed.\n");
        exit(-1);
    }
    while (1)
    {
        if (ioctl(fp, IOC_TEST_GET_NAME, s_name) != 0)
        {
            break;
        }
        printf("name:%s\n", s_name);
        sleep(5);
    }

    if (ioctl(fp, IOC_TEST_STOP, 0) != 0)
    {
        printf("IOC_TEST_STOP failed.\n");
        exit(-1);
    }

    close(fp);
    return 0;
}
