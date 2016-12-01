#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2016 // UTC year
#define YOTTA_BUILD_MONTH 11 // UTC month 1-12
#define YOTTA_BUILD_DAY 30 // UTC day 1-31
#define YOTTA_BUILD_HOUR 14 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 38 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 26 // UTC second 0-61
#define YOTTA_BUILD_UUID 27319485-3ed1-46a7-b296-c77f5cc3bcbd // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID 5511c22f5725dda44494c0c937dff267d6ceb21b // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION 5511c22 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
