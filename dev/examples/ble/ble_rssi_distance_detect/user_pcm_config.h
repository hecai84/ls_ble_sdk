#ifndef _USER_PCM_CONFIG_H_
#define _USER_PCM_CONFIG_H_
#define PCM_SOURCE_BASE 0x20000
#define LOCK_PCM_START_ADDR PCM_SOURCE_BASE
#define LOCK_PCM_LEN 0x35B0
#define UNLOCK_PCM_START_ADDR (PCM_SOURCE_BASE + LOCK_PCM_LEN)
#define UNLOCK_PCM_LEN (0x6F70 - LOCK_PCM_LEN)
#define SPEAKER_IO_0 PA08
#define SPEAKER_IO_1 PA09

#endif