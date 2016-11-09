#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2016 // UTC year
#define YOTTA_BUILD_MONTH 11 // UTC month 1-12
#define YOTTA_BUILD_DAY 9 // UTC day 1-31
#define YOTTA_BUILD_HOUR 13 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 36 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 20 // UTC second 0-61
#define YOTTA_BUILD_UUID 2bd10e08-6342-418e-95c6-24ce88c77886 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID c6c81146b84a7933bc44598b4310a9e92e08c447 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION c6c8114 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
