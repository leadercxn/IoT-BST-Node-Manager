/* Copyright (c) 2018 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "util.h"

TEST_GROUP(util)
{
    void setup()
    {
        // printf("util test start...\n");
    }
    void teardown()
    {
        // printf("util test stop...\n");
    }
};

TEST(util, util_singleton_process)
{
    #define PID_FILE "/var/run/sdk_linux_app.pid"

    int rc = 0;

    printf("util_singleton_process_test may run with sudo in ubuntu\n");

    rc = util_singleton_process(PID_FILE);
    CHECK_EQUAL(rc, 0);

    rc = util_singleton_process(PID_FILE);
    CHECK_EQUAL(rc, -1);
}

TEST(util, hexstr_verify)
{
    char hexstr1[]="1122334455667788";
    char hexstr2[]="122334455667788";
    char hexstr3[]="122334455667788p";

    CHECK(hexstr_verify(hexstr1));
    CHECK(!hexstr_verify(hexstr2));
    CHECK(!hexstr_verify(hexstr3));
}

TEST(util, hexstr_decode)
{
    char hexstr[]="1122334455667788";
    uint8_t expected[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    uint8_t result[128] = {0};
    size_t n = 0;

    n = hexstr_decode(hexstr, result);

    CHECK_EQUAL(n, strlen(hexstr)/2);
    MEMCMP_EQUAL(expected, result, sizeof(expected));
}

TEST(util, hexstr_decode_invalid)
{
    char hexstr[]="122334y455667788";
    uint8_t expected[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t result[128] = {0};
    size_t n = 0;

    n = hexstr_decode(hexstr, result);

    CHECK_EQUAL(n, 0);
    MEMCMP_EQUAL(expected, result, sizeof(expected));
}

TEST(util, hexstr_decode_empty)
{
    char hexstr[]="";
    uint8_t expected[] = {0x00};
    uint8_t result[128] = {0};
    size_t n = 0;

    n = hexstr_decode(hexstr, result);

    CHECK_EQUAL(n, 0);
    MEMCMP_EQUAL(expected, result, sizeof(expected));
}

TEST(util, util_strsplit_null)
{
    int rc = 0;
    char *argv[4] = {0};
    int argc = 0;
    char str[]="111,222,333";

    rc = util_strsplit(str, ',', NULL, &argc, 3);
    CHECK_EQUAL(rc, -1);

    rc = util_strsplit(str, ',', argv, NULL, 3);
    CHECK_EQUAL(rc, -1);

    rc = util_strsplit(str, ',', argv, &argc, 0);
    CHECK_EQUAL(rc, -1);
}

TEST(util, util_strsplit_split)
{
    int rc = 0;
    char *argv[4] = {0};
    int argc = 0;

    char str[]="111,222,333";
    rc = util_strsplit(str, ',', argv, &argc, 3);
    CHECK_EQUAL(rc, 0);
    CHECK_EQUAL(argc, 3);
    STRCMP_EQUAL(argv[0], "111");
    STRCMP_EQUAL(argv[1], "222");
    STRCMP_EQUAL(argv[2], "333");

    char str2[]="111,222";
    rc = util_strsplit(str2, ',', argv, &argc, 3);
    CHECK_EQUAL(rc, 0);
    CHECK_EQUAL(argc, 2);
    STRCMP_EQUAL(argv[0], "111");
    STRCMP_EQUAL(argv[1], "222");
}

TEST(util, util_strsplit_maxnum)
{
    int rc = 0;
    char *argv[4] = {0};
    int argc = 0;

    char str[]="111,222,333,444";
    rc = util_strsplit(str, ',', argv, &argc, 3);
    CHECK_EQUAL(rc, 0);
    CHECK_EQUAL(argc, 3);
    STRCMP_EQUAL(argv[0], "111");
    STRCMP_EQUAL(argv[1], "222");
    STRCMP_EQUAL(argv[2], "333,444");
}

TEST(util, util_strsplit_empty)
{
    int rc = 0;
    char *argv[4] = {0};
    int argc = 0;

    char str[]="111,,,,";
    rc = util_strsplit(str, ',', argv, &argc, 3);
    CHECK_EQUAL(rc, 0);
    CHECK_EQUAL(argc, 3);
    STRCMP_EQUAL(argv[0], "111");
    STRCMP_EQUAL(argv[1], "");
    STRCMP_EQUAL(argv[2], ",,");

    char str2[]=",111,,,,";
    rc = util_strsplit(str2, ',', argv, &argc, 3);
    CHECK_EQUAL(rc, 0);
    CHECK_EQUAL(argc, 3);
    STRCMP_EQUAL(argv[0], "");
    STRCMP_EQUAL(argv[1], "111");
    STRCMP_EQUAL(argv[2], ",,,");

    char str3[]=",,";
    rc = util_strsplit(str3, ',', argv, &argc, 3);
    CHECK_EQUAL(rc, 0);
    CHECK_EQUAL(argc, 3);
    STRCMP_EQUAL(argv[0], "");
    STRCMP_EQUAL(argv[1], "");
    STRCMP_EQUAL(argv[2], "");
}
