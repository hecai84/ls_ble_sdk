#ifndef LSPCM_H_
#define LSPCM_H_
#include <stdint.h>

void PCM_init(uint8_t pcm_out_pin1, uint8_t pcm_out_pin2, uint32_t pcm_image_base);
void PCM_DeInit(void);
void PCM_Out_Start(void);
void PCM_Out_Stop(void);
void PCM_update_config(uint32_t offset, uint32_t size);
#endif
