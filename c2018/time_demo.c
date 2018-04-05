#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

/* 微妙级系统时间 timeval;
 * 秒级时间戳 time_t;
 * 指定格式时间 tm;
 * strftime() 将tm解析成字符串格式时间, strptime()将字符串格式转化为tm.
 */

int main(int argc, char const* argv[])
{
    time_t now;
    time(&now);
    printf("now:%ld\n", now);

    struct tm *tmp_time = localtime(&now);
    char s[100];
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", tmp_time);
    printf("%ld: %s\n", now, s);

    struct timeval tv;
    for (int i = 0; i < 5; i++) {
        gettimeofday(&tv, NULL);
        printf("%ld\t%d\n", tv.tv_sec, tv.tv_usec);
        sleep(1);
    }
    return 0;
}
