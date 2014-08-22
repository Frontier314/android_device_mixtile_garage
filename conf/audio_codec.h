/*
** Copyright 2008, The Android Open-Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef ANDROID_AUDIO_CODEC_H
#define ANDROID_AUDIO_CODEC_H

namespace android_audio_legacy {

typedef struct AudioMixer_tag {
    const char *ctl;
    const int   val;
} AudioMixer;

//  codec mixer settings
//  : These settings depend on your sound codec driver.
//  : You have to modify.
//
const AudioMixer device_out_SPK[] = {
#if defined (USES_I2S_AUDIO) || defined (USES_PCM_AUDIO)
    {"Right Output Mixer PCM Playback Switch", 1},
    {"Left Output Mixer PCM Playback Switch", 1},      
    {"Playback Volume", 254},           // 0 - 255
    {"Headphone Playback Volume", 0},   // 0 - 127
    {"Speaker Playback Volume", 127},   // 0 - 127
//    {"Speaker DC Volume", 5},           // 0 - 5
//    {"Speaker AC Volume", 5},           // 0 - 5
#elif defined(USES_SPDIF_AUDIO)
#endif
    {NULL, NULL}
};
const AudioMixer device_out_RCV[] = {
    {NULL, NULL}
};
const AudioMixer device_out_RING_SPK[] = {
    {NULL, NULL}
};
const AudioMixer device_out_RING_NO_MIC[] = {
    {NULL, NULL}
};
const AudioMixer device_out_HP_NO_MIC[] = {
    {"Right Output Mixer PCM Playback Switch", 1},
    {"Left Output Mixer PCM Playback Switch", 1},      
    {"Playback Volume", 254},             // 0 - 255
    {"Headphone Playback Volume", 127},   // 0 - 127
    {"Speaker Playback Volume", 0},       // 0 - 127
    {NULL, NULL}
};
const AudioMixer device_out_RING_HP[] = {
    {NULL, NULL}
};
const AudioMixer device_out_HP[] = {
    {"Right Output Mixer PCM Playback Switch", 1},
    {"Left Output Mixer PCM Playback Switch", 1},      
    {"Playback Volume", 254},             // 0 - 255
    {"Headphone Playback Volume", 127},   // 0 - 127
    {"Speaker Playback Volume", 0},       // 0 - 127
    {NULL, NULL}
};
const AudioMixer device_out_RING_SPK_HP[] = {
    {NULL, NULL}
};
const AudioMixer device_out_SPK_HP[] = {
    {NULL, NULL}
};
const AudioMixer device_out_BT[] = {
    {NULL, NULL}
};
const AudioMixer device_out_OFF[] = {
    {"Right Output Mixer PCM Playback Switch", 0},
    {"Left Output Mixer PCM Playback Switch", 0},      
    {NULL, NULL}
};

const AudioMixer device_voice_RCV[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_SPK[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_TTY_VCO[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_TTY_HCO[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_TTY_FULL[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_HP_NO_MIC[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_HP[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_BT[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_OFF[] = {
    {NULL, NULL}
};

#ifdef HTPC-EXYNOS4X12
  const AudioMixer device_input_Main_Mic[] = {
  #if defined (USES_I2S_AUDIO) || defined (USES_PCM_AUDIO)
      {"Capture Volume", 63},
      {"Capture Switch", 1},
      {"Left ADC Volume", 200},
      {"Right ADC Volume", 0},
      {"ADC High Pass Filter Switch", 1},
      {"Right Boost Mixer RINPUT2 Switch", 0},
      {"Right Boost Mixer RINPUT3 Switch", 0},
      {"Right Boost Mixer RINPUT1 Switch", 0},
      {"Left Boost Mixer LINPUT2 Switch", 0},
      {"Left Boost Mixer LINPUT3 Switch", 0},
      {"Left Boost Mixer LINPUT1 Switch", 1},
      {"Left Input Mixer Boost Switch", 1},
      {"Right Input Mixer Boost Switch", 0},
      {"ADC PCM Capture Volume", 127},
      {"ADC PATH", 1},    
  #elif defined(USES_SPDIF_AUDIO)
  #endif
      {NULL, NULL}
  };
  const AudioMixer device_input_Hands_Free_Mic[] = {
      {"Capture Volume", 63},
      {"Capture Switch", 1},
      {"Left ADC Volume", 0},
      {"Right ADC Volume", 230},
      {"ADC High Pass Filter Switch", 1},
      {"Right Boost Mixer RINPUT2 Switch", 0},
      {"Right Boost Mixer RINPUT3 Switch", 0},
      {"Right Boost Mixer RINPUT1 Switch", 0},
      {"Left Boost Mixer LINPUT2 Switch", 1},
      {"Left Boost Mixer LINPUT3 Switch", 0},
      {"Left Boost Mixer LINPUT1 Switch", 0},
      {"Left Input Mixer Boost Switch", 1},
      {"Right Input Mixer Boost Switch", 0},
      {"ADC PCM Capture Volume", 127},
      {"ADC PATH", 1},    
      {NULL, NULL}
  };
#else
  const AudioMixer device_input_Main_Mic[] = {
  #if defined (USES_I2S_AUDIO) || defined (USES_PCM_AUDIO)
      {"Capture Volume", 63},
      {"Capture Switch", 1},
      {"Left ADC Volume", 200},
      {"Right ADC Volume", 0},
      {"ADC High Pass Filter Switch", 1},
      {"Right Boost Mixer RINPUT2 Switch", 0},
      {"Right Boost Mixer RINPUT3 Switch", 0},
      {"Right Boost Mixer RINPUT1 Switch", 0},
      {"Left Boost Mixer LINPUT2 Switch", 1},
      {"Left Boost Mixer LINPUT3 Switch", 0},
      {"Left Boost Mixer LINPUT1 Switch", 1},
      {"Left Input Mixer Boost Switch", 1},
      {"Right Input Mixer Boost Switch", 0},
      {"ADC PCM Capture Volume", 127},
      {"ADC PATH", 1},    
  #elif defined(USES_SPDIF_AUDIO)
  #endif
      {NULL, NULL}
  };
  const AudioMixer device_input_Hands_Free_Mic[] = {
      {"Capture Volume", 63},
      {"Capture Switch", 1},
      {"Left ADC Volume", 0},
      {"Right ADC Volume", 230},
      {"ADC High Pass Filter Switch", 1},
      {"Right Boost Mixer RINPUT2 Switch", 1},
      {"Right Boost Mixer RINPUT3 Switch", 0},
      {"Right Boost Mixer RINPUT1 Switch", 1},
      {"Left Boost Mixer LINPUT2 Switch", 0},
      {"Left Boost Mixer LINPUT3 Switch", 0},
      {"Left Boost Mixer LINPUT1 Switch", 0},
      {"Left Input Mixer Boost Switch", 0},
      {"Right Input Mixer Boost Switch", 1},
      {"ADC PCM Capture Volume", 127},
      {"ADC PATH", 2},    
      {NULL, NULL}
  };
#endif /*HTPC-S5PV310*/

const AudioMixer device_input_BT_Sco_Mic[] = {
//    {"Capture Volume", 63},
//    {"Capture Switch", 1},
//    {"ADC PCM Capture Volume", 127},
//    {"Left ADC Volume", 200},
//    {"Right ADC Volume", 200},
//    {"Right Boost Mixer RINPUT1 Switch", 1},
//    {"Right Boost Mixer RINPUT2 Switch", 0},
//    {"Right Boost Mixer RINPUT3 Switch", 1},
//    {"Left Boost Mixer LINPUT1 Switch", 1},
//    {"Left Boost Mixer LINPUT2 Switch", 0},
//    {"Left Boost Mixer LINPUT3 Switch", 1},
//    {"Left Input Mixer Boost Switch", 1},
//    {"Right Input Mixer Boost Switch", 1},
    {NULL, NULL}
};
const AudioMixer device_input_MIC_OFF[] = {
    {"Capture Volume", 0},
    {"Capture Switch", 0},
    {"Left ADC Volume", 0},
    {"Right ADC Volume", 0},
    {"ADC High Pass Filter Switch", 0},
    {"Right Boost Mixer RINPUT1 Switch", 0},
    {"Right Boost Mixer RINPUT2 Switch", 0},
    {"Right Boost Mixer RINPUT3 Switch", 0},
    {"Left Boost Mixer LINPUT1 Switch", 0},
    {"Left Boost Mixer LINPUT2 Switch", 0},
    {"Left Boost Mixer LINPUT3 Switch", 0},
    {"Left Input Mixer Boost Switch", 0},
    {"Right Input Mixer Boost Switch", 0},
    {"ADC PCM Capture Volume", 0},
    {NULL, NULL}
};


}; // namespace android

#endif //ANDROID_AUDIO_CODEC_H
