#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2016 // UTC year
#define YOTTA_BUILD_MONTH 11 // UTC month 1-12
#define YOTTA_BUILD_DAY 10 // UTC day 1-31
#define YOTTA_BUILD_HOUR 13 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 54 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 22 // UTC second 0-61
#define YOTTA_BUILD_UUID 1e0ded01-2912-47e1-ba8b-d75237ca4d6e // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID dea02877fcb990d0da07ab39f93c6818d4f01ea1 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION dea0287 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
