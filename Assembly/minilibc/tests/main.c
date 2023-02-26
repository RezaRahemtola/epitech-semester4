/*
** EPITECH PROJECT, 2023
** tests
** File description:
** $DESCRIPTION
*/

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

int main(void)
{
    if (strlen("") != 0 || strlen("Reza") != 4) {
        return 1;
    }
    if (strchr("Reza", 'y') != NULL || strlen(strchr("Reza", 'z')) != 2) {
        return 2;
    }

    if (strrchr("Reza", 'y') != NULL || strlen(strrchr("Reza", 'z')) != 2 || strcmp(strrchr("Hello", 'l'), "lo") != 0 || strcmp(strrchr("Hello", 'o'), "o") != 0 || strcmp(strrchr("Hoellou", '\0'), "") || strcmp(strrchr("", '\0'), "")) {
        return 3;
    }

    char m_str[10] = {'\0' * 10};
    if (strcmp(memset(m_str, 'a', 5), "aaaaa") != 0 || strcmp(memset(m_str, 'b', 1), "baaaa") != 0) {
        return 4;
    }
    if (strcmp(memcpy(m_str, "cde", 2), "cdaaa") != 0) {
        return 5;
    }

    if (strcmp("ABC", "AB") != 67 || strcmp("ABA", "ABZ") != -25 || strcmp("ABJ", "ABC") != 7) {
        return 6;
    }
    if (strncmp("ABC", "AB", 3) != 67 || strncmp("ABC", "AB", 2) != 0) {
        return 7;
    }
    if (strcasecmp("Reza", "Reza") != 0 || strcasecmp("rEzA", "REZa") != 0 || strcasecmp("reza1", "rezaa") == 0 || strcasecmp("ReZaSm", "reza") != 115) {
        return 8;
    }

    char mm_str[100] = "Samplestring12";
    memmove(mm_str + 8, mm_str, 10);
    if (strcmp(mm_str, "SamplestSamplestri") != 0) {
        return 9;
    }

    char str_str[9] = "Haystack";
    if (strcmp(strstr(str_str, ""), str_str) != 0 || strcmp(strstr(str_str, "k"), "k") != 0 || strcmp(strstr(str_str, "Haystack"), "Haystack") != 0 || strcmp(strstr(str_str, "ays"), "aystack") != 0) {
        return 10;
    }

    char pbrk_str[9] = "Haystack";
    if (strcmp(strpbrk(pbrk_str, "ry"), "ystack") != 0 || strpbrk(pbrk_str, "") != NULL || strpbrk(pbrk_str, "zxTp") != NULL || strcmp(strpbrk(pbrk_str, "ta"), "aystack") != 0) {
        return 11;
    }

    char cspn_str[9] = "Haystack";
    if (strcspn(cspn_str, "") != 8 || strcspn(cspn_str, "xncY") != 6 || strcspn(cspn_str, cspn_str) != 0) {
        return 12;
    }

    // Bonuses:
    if (index("Reza", 'y') != NULL || strlen(index("Reza", 'z')) != 2) {
        return 13;
    }
    if (rindex("Reza", 'y') != NULL || strlen(rindex("Reza", 'z')) != 2 || strcmp(rindex("Hello", 'l'), "lo") != 0 || strcmp(rindex("Hello", 'o'), "o") != 0 || strcmp(rindex("Hoellou", 'o'), "ou")) {
        return 14;
    }

    printf("Its working!\n");
}
