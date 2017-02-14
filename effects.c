/*
 *  Copyright (c) 2009 Tomasz Moń <desowin@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; under version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses>.
 */

#include "gdigi.h"
#include "gui.h"
#include "effects.h"
#include "gdigi_xml.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

static gchar *wave_labels[] = {
    "Tri",
    "Sine",
    "Square",
    NULL,
};

static gchar *whammy_labels[] = {
    "OctUp",
    "2OctUp",
    "2ndDn",
    "Rv2nd",
    "4thDn",
    "OctDn",
    "2OctDn",
    "DivBmb",
    "M3>Ma3",
    "2ndMa3",
    "3rd4th",
    "4th5th",
    "5thOct",
    "HOctUp",
    "HOctDn",
    "OctU>D",
    NULL,
};

static gchar *ips_shift_labels[] = {
    "Oct Dn",
    "7th Dn",
    "6th Dn",
    "5th Dn",
    "4th Dn",
    "3rd Dn",
    "2nd Dn",
    "2nd Up",
    "3rd Up",
    "4th Up",
    "5th Up",
    "6th Up",
    "7th Up",
    "Oct Up",
    NULL,
};

static gchar *ips_key_labels[] = {
    "E",
    "F",
    "Gb",
    "G",
    "Ab",
    "A",
    "Bb",
    "B",
    "C",
    "Db",
    "D",
    "Eb",
    NULL,
};

static gchar *ips_scale_labels[] = {
    "Major",
    "Minor",
    "Dorian",
    "Mixolydian",
    "Lydian",
    "HMinor",
    NULL,
};

static gchar *on_off_labels[] = {
    "Off",
    "On",
    NULL,
};

static gchar *odd_even_labels[] = {
    "Odd",
    "Even",
    NULL,
};

static gchar *chorus_vibrato_labels[] = {
    "Chorus",
    "Vibrato",
    NULL,
};

static gchar *hp_lp_labels[] = {
    "HP",
    "LP",
    NULL,
};

static gchar *loose_tight_labels[] = {
    "Loose",
    "Tight",
    NULL,
};

static gchar *pickup_type_labels[] = {
    "SC>HB",
    "HB>SC",
    NULL,
};

static gchar *fast_medium_slow_labels[] = {
    "Fast",
    "Medium",
    "Slow",
    NULL,
};

static gchar *comp_ratio_labels[] = {
    "1.2:1",
    "1.5:1",
    "1.8:1",
    "2.0:1",
    "2.5:1",
    "3:1",
    "4:1",
    "5:1",
    "8:1",
    "10:1",
    "20:1",
    "Inf:1",
    NULL,
};

static gchar *eq_bandwidth_labels[] = {
    "Wide",
    "Medium",
    "Narrow",
    NULL,
};

static gchar *eq_low_freq_labels[] = {
    "60Hz",
    "63Hz",
    "67Hz",
    "71Hz",
    "75Hz",
    "80Hz",
    "85Hz",
    "90Hz",
    "95Hz",
    "100Hz",
    "106Hz",
    "112Hz",
    "118Hz",
    "125Hz",
    "132Hz",
    "140Hz",
    "150Hz",
    "160Hz",
    "170Hz",
    "180Hz",
    "190Hz",
    "200Hz",
    "212Hz",
    "224Hz",
    "236Hz",
    "250Hz",
    "265Hz",
    "280Hz",
    "300Hz",
    "315Hz",
    "335Hz",
    "355Hz",
    "375Hz",
    "400Hz",
    "425Hz",
    "450Hz",
    "475Hz",
    "500Hz",
    NULL,
};

static gchar *eq_mid_freq_labels[] = {
    "300Hz",
    "315Hz",
    "335Hz",
    "355Hz",
    "375Hz",
    "400Hz",
    "425Hz",
    "450Hz",
    "475Hz",
    "500Hz",
    "530Hz",
    "560Hz",
    "600Hz",
    "630Hz",
    "670Hz",
    "710Hz",
    "750Hz",
    "800Hz",
    "850Hz",
    "900Hz",
    "950Hz",
    "1kHz",
    "1.06kHz",
    "1.12kHz",
    "1.18kHz",
    "1.25kHz",
    "1.32kHz",
    "1.4kHz",
    "1.5kHz",
    "1.6kHz",
    "1.7kHz",
    "1.8kHz",
    "1.9kHz",
    "2kHz",
    "2.12kHz",
    "2.24kHz",
    "2.36kHz",
    "2.5kHz",
    "2.65kHz",
    "2.8kHz",
    "3kHz",
    "3.15kHz",
    "3.35kHz",
    "3.55kHz",
    "3.75kHz",
    "4kHz",
    NULL,
};

static gchar *eq_high_freq_labels[] = {
    "2kHz",
    "2.12kHz",
    "2.24kHz",
    "2.36kHz",
    "2.5kHz",
    "2.65kHz",
    "2.8kHz",
    "3kHz",
    "3.15kHz",
    "3.35kHz",
    "3.55kHz",
    "3.75kHz",
    "4kHz",
    "4.25kHz",
    "4.5kHz",
    "4.75kHz",
    "5kHz",
    "5.3kHz",
    "5.6kHz",
    "6kHz",
    "6.3kHz",
    "6.7kHz",
    "7.1kHz",
    "7.5kHz",
    "8kHz",
    NULL,
};

static gchar *amp_channel_labels[] = {
    "1",
    "2",
    "Warped",
    NULL,
};

static gchar *rhold_labels[] = {
    "RHold",
    NULL,
};

static gchar *delay_mult_labels[] = {
    "Half",
    "Quarter",
    "Dot Eighth",
    "Eighth",
    "3 Quarter",
    NULL,
};

static EffectValues values_1_2_warp = {
    .min = 0.0, .max = 2.0,
    .type = VALUE_TYPE_LABEL,
    .labels = amp_channel_labels,
};

static EffectValues values_a_b = {
    .min = 0.0, .max = 2.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_0_to_99 = {
    .min = 0.0, .max = 99.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_0_to_255 = {
    .min = 0.0, .max = 255.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_0_to_29 = {
    .min = 0.0, .max = 29.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_1_to_4 = {
    .min = 0.0, .max = 3.0,
    .type = VALUE_TYPE_OFFSET,
    .offset = 1,
};

static EffectValues values_warp_0_to_98 = {
    .min = 0.0, .max = 98.0,
    .type = VALUE_TYPE_OFFSET,
    .offset = 1,
};

static EffectValues values_0_to_1 = {
    .min = 0.0, .max = 1.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_0_to_9 = {
    .min = 0.0, .max = 9.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_0_to_49 = {
    .min = 0.0, .max = 49.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_0_to_15 = {
    .min = 0.0, .max = 15.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_0_to_20 = {
    .min = 0.0, .max = 20.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_m12_to_12_semitones = {
    /** \todo make this display properly (display range -12.0 to 12.0 semitones) */
    .min = 0.0, .max = 48.0, .type = VALUE_TYPE_PLAIN,
/*    .type = VALUE_TYPE_SUFFIX | VALUE_TYPE_OFFSET,
    .suffix = "semitones", .offset = -12, */
};

static EffectValues values_m24_to_24_step2 = {
    .min = 0.0, .max = 24.0,
    .type = VALUE_TYPE_OFFSET | VALUE_TYPE_STEP,
    .offset = -12, .step = 2.0,
};

static EffectValues values_m24_to_24 = {
    .min = 0.0, .max = 48.0,
    .type = VALUE_TYPE_OFFSET,
    .offset = -24,
};

static EffectValues values_m12_to_24 = {
    .min = 0.0, .max = 36.0,
    .type = VALUE_TYPE_OFFSET,
    .offset = -12,
};

static EffectValues values_comp_ratio = {
    .min = 0.0, .max = 12.0,
    .type = VALUE_TYPE_LABEL,
    .labels = comp_ratio_labels,
};

static EffectValues values_fast_medium_slow = {
    .min = 0.0, .max = 2.0,
    .type = VALUE_TYPE_LABEL,
    .labels = fast_medium_slow_labels,
};

static EffectValues values_eq_db = {
    .min = 0.0, .max = 24.0,
    .type = VALUE_TYPE_SUFFIX | VALUE_TYPE_OFFSET,
    .suffix = "dB", .offset = -12,
};

static EffectValues values_db_boost = {
    .min = 0.0, .max = 24.0,
    .type = VALUE_TYPE_SUFFIX,
    .suffix = "dB",
};

static EffectValues values_eq_bass_hz = {
    .min = 0.0, .max = 250.0,
    .type = VALUE_TYPE_SUFFIX | VALUE_TYPE_OFFSET,
    .suffix = "hz", .offset = 50,
};

static EffectValues values_eq_mid_hz = {
    .min = 0.0, .max = 4700.0,
    .type = VALUE_TYPE_OFFSET,
    .offset = 300,
};

static EffectValues values_eq_treb_hz = {
    .min = 0.0, .max = 7500.0,
    .type = VALUE_TYPE_OFFSET,
    .offset = 500,
};

static EffectValues values_eq_bandwidth = {
    .min = 0.0, .max = 2.0,
    .type = VALUE_TYPE_LABEL,
    .labels = eq_bandwidth_labels,
};

static EffectValues values_eq_low_freq = {
    .min = 0.0, .max = 37.0,
    .type = VALUE_TYPE_LABEL,
    .labels = eq_low_freq_labels,
};

static EffectValues values_eq_mid_freq = {
    .min = 0.0, .max = 45.0,
    .type = VALUE_TYPE_LABEL,
    .labels = eq_mid_freq_labels,
};

static EffectValues values_eq_high_freq = {
    .min = 0.0, .max = 24.0,
    .type = VALUE_TYPE_LABEL,
    .labels = eq_high_freq_labels,
};

static EffectValues values_200hz_to_1_5khz = {
    /** \todo make this display properly (display range 200 Hz to 1.5 kHz) */
    .min = 0.0, .max = 130.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_waveform = {
    .min = 0.0, .max = 2.0,
    .type = VALUE_TYPE_LABEL,
    .labels = wave_labels,
};

static EffectValues values_balance = {
    /** \todo make this display properly */
    0.0, 198.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_synth_talk_release = {
    /** \todo make last value display properly */
    0.0, 100.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_whammy_amount = {
    .min = 0.0, .max = 15.0,
    .type = VALUE_TYPE_LABEL,
    .labels = whammy_labels,
};

static EffectValues values_ips_shift = {
    .min = 0.0, .max = 13.0,
    .type = VALUE_TYPE_LABEL,
    .labels = ips_shift_labels,
};

static EffectValues values_ips_key = {
    .min = 0.0, .max = 11.0,
    .type = VALUE_TYPE_LABEL,
    .labels = ips_key_labels,
};

static EffectValues values_ips_scale = {
    .min = 0.0, .max = 5.0,
    .type = VALUE_TYPE_LABEL,
    .labels = ips_scale_labels,
};

static EffectValues values_predelay_time = {
    .min = 0.0, .max = 19.0,
    .type = VALUE_TYPE_SUFFIX | VALUE_TYPE_OFFSET,
    .suffix = "ms", .offset = 1,
};

static EffectValues values_delay_time_extra = {
    /* display as 1.0 sec (99) to 5.0 sec (139) */
    .min = 99.0, .max = 139.0,
    .type = VALUE_TYPE_SUFFIX | VALUE_TYPE_OFFSET |
            VALUE_TYPE_STEP | VALUE_TYPE_DECIMAL,
    .suffix = "sec", .offset = -89,
    .step = 0.1, .decimal = 1,
};

static EffectValues values_delay_time = {
    /* 0 to 139, extended by values_delay_time_extra */
    .min = 0.0, .max = 98.0,
    .type = VALUE_TYPE_SUFFIX | VALUE_TYPE_OFFSET |
            VALUE_TYPE_STEP | VALUE_TYPE_EXTRA,
    .suffix = "ms", .offset = 1,
    .step = 10.0, .extra = &values_delay_time_extra,
};

static EffectValues values_delay_time_110_870 = {
    .min = 0.0, .max = 760.0,
    .type = VALUE_TYPE_SUFFIX | VALUE_TYPE_OFFSET,
    .suffix = "ms", .offset = 110,
};

static EffectValues values_delay_time_0_2000 = {
    /** \todo make this display properly */
    0.0, 2000.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_delay_time_0_4650 = {
    /** \todo make this display properly */
    0.0, 4650.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_delay_time_0_4990 = {
    /** \todo make this display properly */
    0.0, 4990.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_delay_time_0_5000 = {
    /** \todo make this display properly */
    0.0, 5000.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_delay_repeats_extra = {
    .min = 100.0, .max = 100.0,
    .type = VALUE_TYPE_LABEL,
    .labels = rhold_labels,
};

static EffectValues values_delay_repeats = {
    /* 0 to 100, extended by values_delay_repeats_extra */
    .min = 0.0, .max = 99.0,
    .type = VALUE_TYPE_EXTRA,
    .extra = &values_delay_repeats_extra,
};

static EffectValues values_delay_thresh = {
    /** \todo make last value display properly */
    0.0, 100.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_delay_repeat_rate_24_310 = {
    .min = 0.0, .max = 286.0,
    .type = VALUE_TYPE_SUFFIX | VALUE_TYPE_OFFSET,
    .suffix = "ms", .offset = 24,
};

static EffectValues values_delay_spread_0_49 = {
    /** \todo make this display properly */
    0.0, 49.0, .type = VALUE_TYPE_PLAIN,
};

static EffectValues values_delay_mult = {
    .min = 2176.0, .max = 2180.0,
    .type = VALUE_TYPE_LABEL,
    .labels = delay_mult_labels,
};

EffectValues values_on_off = {
    .min = 0.0, .max = 1.0,
    .type = VALUE_TYPE_LABEL,
    .labels = on_off_labels,
};

EffectValues values_posid = {
    .type = VALUE_TYPE_POSID,
};

static EffectValues values_odd_even = {
    .min = 0.0, .max = 1.0,
    .type = VALUE_TYPE_LABEL,
    .labels = odd_even_labels,
};

static EffectValues values_chorus_vibrato = {
    .min = 0.0, .max = 1.0,
    .type = VALUE_TYPE_LABEL,
    .labels = chorus_vibrato_labels,
};

static EffectValues values_hp_lp = {
    .min = 0.0, .max = 1.0,
    .type = VALUE_TYPE_LABEL,
    .labels = hp_lp_labels,
};

static EffectValues values_loose_tight = {
    .min = 0.0, .max = 1.0,
    .type = VALUE_TYPE_LABEL,
    .labels = loose_tight_labels,
};

static EffectValues values_pickup_type = {
    .min = 65.0, .max = 66.0,
    .type = VALUE_TYPE_LABEL,
    .labels = pickup_type_labels,
};

static EffectValues values_comp_type = {
    .min = 195.0, .max = 197.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_dist_type = {
    .min = 1280.0, .max = 1302.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_amp_type = {
    .min = 307.0, .max = 351.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_cab_type = {
    .min = 570.0, .max = 627.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_gate_type = {
    .min = 768.0, .max = 769.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_mod_type = {
    .min = 862.0, .max = 1347.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_pre_post = {
    .min = 1543.0, .max = 1544.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_delay_type = {
    .min = 1027.0, .max = 1066.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_reverb_type = {
    .min = 1107.0, .max = 1151.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_wah_type = {
    .min = 129.0, .max = 134.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_exp_assign = {
    .min = 0.0, .max = 0x7fffffff,
    .type = VALUE_TYPE_POSID,
};

static EffectValues values_vswitch_pedal_assign = {
    .min = 0.0, .max = 0x7fffffff,
    .type = VALUE_TYPE_POSID,
};

static EffectValues values_vswitch_assign = {
    .min = 0.0, .max = 0x7fffffff,
    .type = VALUE_TYPE_POSID,
};

static EffectValues values_vswitch_type = {
    .min = 0.0, .max = 1.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_lfo_assign = {
    .min = 0.0, .max = 0x7fffffff,
    .type = VALUE_TYPE_POSID,
};

static EffectValues values_lfo_none = {
    .min = 0.0, .max = 0.0,
    .type = VALUE_TYPE_NONE,
};

static EffectValues values_lfo_speed_extra = {
    .min = 95.0, .max = 185.0,
    .type = VALUE_TYPE_PLAIN | VALUE_TYPE_OFFSET | VALUE_TYPE_STEP | VALUE_TYPE_DECIMAL,
    .offset = -85.0, .step = 0.1, .decimal = 1, .suffix = "Hz",
};

static EffectValues values_lfo_speed = {
    .min = 0.0, .max = 94.0,
    .type = VALUE_TYPE_PLAIN | VALUE_TYPE_OFFSET | VALUE_TYPE_STEP | VALUE_TYPE_DECIMAL | VALUE_TYPE_EXTRA | VALUE_TYPE_SUFFIX,
    .offset = 5, .step = 0.01, .decimal = 2, .suffix = "Hz",
    .extra = &values_lfo_speed_extra,
};

static EffectValues values_eq_type = {
    .min = 1472.0, .max = 1475.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_lfo_waveform = {
    .min = 0.0, .max = 3.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_tone_lib_type= {
    .min = 1792.0, .max = 1822.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_fx_lib_type= {
    .min = 1856.0, .max = 1866.0,
    .type = VALUE_TYPE_LABEL,
};

static EffectValues values_1_to_10_step_0p1 = {
    .min = 0.0, .max = 90.0,
    .type = VALUE_TYPE_OFFSET | VALUE_TYPE_STEP | VALUE_TYPE_DECIMAL,
    .offset = 10, .step = 0.1, .decimal = 1,
};

static EffectValues values_rp_mix = {
    /** \todo make this display properly (USB 0, USB 1, USB 2 ... USB 49, USB RP, RP 49, RP 48 ...  RP 1, RP 0) */
    .min = 0.0, .max = 100.0, .type = VALUE_TYPE_PLAIN,
};

static EffectSettings global_settings[] = {
    {"USB/RP Mix", USB_AUDIO_PLAYBACK_MIX, GLOBAL_POSITION, &values_rp_mix},
    {"USB Level", USB_AUDIO_LEVEL, GLOBAL_POSITION, &values_m12_to_24},
#if defined(DEVELOPMENT_MODE)
    {"GUI Mode", GUI_MODE_ON_OFF, GLOBAL_POSITION, &values_on_off},
#endif /* DEVELOPMENT_MODE */
    {"Tuning Reference", TUNING_REFERENCE, GLOBAL_POSITION, &values_0_to_29},
    {"Pedal Position", EXP_PEDAL_LEVEL, GLOBAL_POSITION, &values_0_to_255},
    {"Stomp", STOMP_MODE, GLOBAL_POSITION, &values_on_off},
    {"Wah Pedal Position", WAH_PEDAL_POSITION, WAH_POSITION, &values_0_to_99},
};

static EffectSettings misc_settings[] = {
    {"Preset Level", PRESET_LEVEL, PRESET_POSITION, &values_0_to_99},
};

static EffectSettings pre_fx_settings[] = {
    {"Volume Pre FX", PRESET_LEVEL, VOLUME_PRE_FX_POSITION, &values_0_to_99},
};

static EffectSettings post_fx_settings[] = {
    {"Volume Post FX", PRESET_LEVEL, VOLUME_POST_FX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_wah_settings[] = {
    {"Min", WAH_MIN, WAH_POSITION_MIN_MAX, &values_0_to_99},
    {"Max", WAH_MAX, WAH_POSITION_MIN_MAX, &values_0_to_99},
};

static EffectSettings wah_settings[] = {
    {"Min", WAH_MIN, WAH_POSITION_MIN_MAX, &values_0_to_99},
    {"Max", WAH_MAX, WAH_POSITION_MIN_MAX, &values_0_to_99},
    {"Level", WAH_VOLUME_BOOST, WAH_POSITION, &values_db_boost},
};

static EffectSettings gnx3k_whammy_settings[] = {
    {"Shift Amount", WHAMMY_AMOUNT, GNX3K_WHAM_POSITION, &values_whammy_amount},
    {"Pedal", WHAMMY_PEDAL, GNX3K_WHAM_POSITION, &values_0_to_99},
    {"Mix", WHAMMY_MIX, GNX3K_WHAM_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_ips_settings[] = {
    {"Shift Amount", IPS_SHIFT_AMOUNT, GNX3K_WHAM_POSITION, &values_ips_shift},
    {"Scale", IPS_SCALE, GNX3K_WHAM_POSITION, &values_ips_scale},
    {"Key", IPS_KEY, GNX3K_WHAM_POSITION, &values_ips_key},
    {"Level", IPS_LEVEL, GNX3K_WHAM_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_detune_settings[] = {
    {"Shift Amount", GNX3K_DETUNE_AMOUNT, GNX3K_WHAM_POSITION, &values_m24_to_24_step2},
    {"Level", DETUNE_LEVEL, GNX3K_WHAM_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_pitch_settings[] = {
    {"Shift Amount", GNX3K_PITCH_AMOUNT, GNX3K_WHAM_POSITION, &values_m24_to_24},
    {"Level", GNX3K_PITCH_LEVEL, GNX3K_WHAM_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_talk_settings[] = {
    {"Mic Level", GNX3K_TALK_LEVEL, GNX3K_WHAM_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_amp_channel_settings[] = {
    {"Amp Channel", GNX_CHANNEL_AMP, GNX_CHANNEL_POSITION, &values_1_2_warp},
    {"Warp", GNX_WARP, GNX_CHANNEL_POSITION, &values_warp_0_to_98},
    {"Amp Warp", GNX_AMP_WARP, GNX_CHANNEL_POSITION, &values_warp_0_to_98},
    {"Cabinet Warp", GNX_CABINET_WARP, GNX_CHANNEL_POSITION, &values_warp_0_to_98},
};

static EffectSettings gnx3k_preset_settings[] = {
    {"Preset Level", PRESET_LEVEL, PRESET_POSITION, &values_0_to_99},
};

static EffectSettings gnx_comp_settings[] = {
    {"Attack", GNX3K_COMP_ATTACK, COMP_POSITION, &values_fast_medium_slow},
    {"Ratio", GNX3K_COMP_RATIO, COMP_POSITION, &values_comp_ratio},
    {"Threshold", GNX3K_COMP_THRESHOLD, COMP_POSITION, &values_0_to_99},
    {"Gain", GNX3K_COMP_GAIN, COMP_POSITION, &values_0_to_20},
};

static EffectSettings comp_digi_settings[] = {
    {"Sustain", COMP_SUSTAIN, COMP_POSITION, &values_0_to_99},
    {"Tone", COMP_TONE, COMP_POSITION, &values_0_to_99},
    {"Attack", COMP_ATTACK, COMP_POSITION, &values_0_to_99},
    {"Level", COMP_LEVEL, COMP_POSITION, &values_0_to_99},
};

static EffectSettings comp_cs_settings[] = {
    {"Sustain", COMP_SUSTAIN, COMP_POSITION, &values_0_to_99},
    {"Attack", COMP_ATTACK, COMP_POSITION, &values_0_to_99},
    {"Level", COMP_LEVEL, COMP_POSITION, &values_0_to_99},
};

static EffectSettings comp_dyna_settings[] = {
    {"Sensitivity", COMP_SENSITIVITY, COMP_POSITION, &values_0_to_99},
    {"Output", COMP_OUTPUT, COMP_POSITION, &values_0_to_99},
};

static EffectSettings dist_screamer_settings[] = {
    {"Drive", DIST_SCREAMER_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Tone", DIST_SCREAMER_TONE, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_SCREAMER_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_808_settings[] = {
    {"Overdrive", DIST_808_OVERDRIVE, DIST_POSITION, &values_0_to_99},
    {"Tone", DIST_808_TONE, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_808_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_ts_mod_settings[] = {
    {"Drive", DIST_TS_MOD_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Tone", DIST_TS_MOD_TONE, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_TS_MOD_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_sd_odrv_settings[] = {
    {"Drive", DIST_SD_ODRV_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Tone", DIST_SD_ODRV_TONE, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_SD_ODRV_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_od_odrv_settings[] = {
    {"Overdrive", DIST_OD_ODRV_OVERDRIVE, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_OD_ODRV_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_sparkdrive_settings[] = {
    {"Gain", DIST_SPARKDRIVE_GAIN, DIST_POSITION, &values_0_to_99},
    {"Tone", DIST_SPARKDRIVE_TONE, DIST_POSITION, &values_0_to_99},
    {"Clean", DIST_SPARKDRIVE_CLEAN, DIST_POSITION, &values_0_to_99},
    {"Volume", DIST_SPARKDRIVE_VOLUME, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_guyod_settings[] = {
    {"Drive", DIST_GUYOD_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_GUYOD_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_dod250_settings[] = {
    {"Gain", DIST_DOD250_GAIN, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_DOD250_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_redline_settings[] = {
    {"Gain", DIST_REDLINE_GAIN, DIST_POSITION, &values_0_to_99},
    {"Low", DIST_REDLINE_LOW, DIST_POSITION, &values_0_to_99},
    {"High", DIST_REDLINE_HIGH, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_REDLINE_LEVEL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_ampdrivr_settings[] = {
    {"Gain", DIST_AMPDRIVR_GAIN, DIST_POSITION, &values_0_to_99},
    {"Mid Boost", DIST_AMPDRIVR_MIDBOOST, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_AMPDRIVR_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_oc_drive_settings[] = {
    {"Drive", DIST_OC_DRIVE_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Tone", DIST_OC_DRIVE_TONE, DIST_POSITION, &values_0_to_99},
    {"HP/LP", DIST_OC_DRIVE_HP_LP, DIST_POSITION, &values_hp_lp},
    {"Level", DIST_OC_DRIVE_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_rodent_settings[] = {
    {"Dist", DIST_RODENT_DIST, DIST_POSITION, &values_0_to_99},
    {"Filter", DIST_RODENT_FILTER, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_RODENT_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_mx_settings[] = {
    {"Dist", DIST_MX_DIST, DIST_POSITION, &values_0_to_99},
    {"Output", DIST_MX_OUTPUT, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_ds_settings[] = {
    {"Gain", DIST_DS_GAIN, DIST_POSITION, &values_0_to_99},
    {"Tone", DIST_DS_TONE, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_DS_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_grunge_settings[] = {
    {"Grunge", DIST_GRUNGE_GRUNGE, DIST_POSITION, &values_0_to_99},
    {"Face", DIST_GRUNGE_FACE, DIST_POSITION, &values_0_to_99},
    {"Loud", DIST_GRUNGE_LOUD, DIST_POSITION, &values_0_to_99},
    {"Butt", DIST_GRUNGE_BUTT, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_zone_settings[] = {
    {"Gain", DIST_ZONE_GAIN, DIST_POSITION, &values_0_to_99},
    {"Low", DIST_ZONE_LOW, DIST_POSITION, &values_0_to_99},
    {"Mid level", DIST_ZONE_MID_LVL, DIST_POSITION, &values_0_to_99},
    {"Mid freq", DIST_ZONE_MID_FREQ, DIST_POSITION, &values_0_to_99},
    {"High", DIST_ZONE_HIGH, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_ZONE_LEVEL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_death_settings[] = {
    {"Low", DIST_DEATH_LOW, DIST_POSITION, &values_0_to_99},
    {"Mid", DIST_DEATH_MID, DIST_POSITION, &values_0_to_99},
    {"High", DIST_DEATH_HIGH, DIST_POSITION, &values_0_to_99},
    {"Level", DIST_DEATH_LVL, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_gonk_settings[] = {
    {"Gonk", DIST_GONK_GONK, DIST_POSITION, &values_0_to_99},
    {"Smear", DIST_GONK_SMEAR, DIST_POSITION, &values_0_to_99},
    {"Suck", DIST_GONK_SUCK, DIST_POSITION, &values_0_to_99},
    {"Heave", DIST_GONK_HEAVE, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_8tavia_settings[] = {
    {"Drive", DIST_8TAVIA_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Volume", DIST_8TAVIA_VOLUME, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_fuzzlator_settings[] = {
    {"Fuzz", DIST_FUZZLATOR_FUZZ, DIST_POSITION, &values_0_to_99},
    {"Tone", DIST_FUZZLATOR_TONE, DIST_POSITION, &values_0_to_99},
    {"LooseTight", DIST_FUZZLATOR_LOOSETIGHT, DIST_POSITION, &values_loose_tight},
    {"Volume", DIST_FUZZLATOR_VOLUME, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_classic_fuzz_settings[] = {
    {"Fuzz", DIST_CLASSIC_FUZZ_FUZZ, DIST_POSITION, &values_0_to_99},
    {"Tone", DIST_CLASSIC_FUZZ_TONE, DIST_POSITION, &values_0_to_99},
    {"Volume", DIST_CLASSIC_FUZZ_VOLUME, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_fuzzy_settings[] = {
    {"Fuzz", DIST_FUZZY_FUZZ, DIST_POSITION, &values_0_to_99},
    {"Volume", DIST_FUZZY_VOLUME, DIST_POSITION, &values_0_to_99},
};

static EffectSettings dist_mp_settings[] = {
    {"Sustain", DIST_MP_SUSTAIN, DIST_POSITION, &values_0_to_99},
    {"Tone", DIST_MP_TONE, DIST_POSITION, &values_0_to_99},
    {"Volume", DIST_MP_VOLUME, DIST_POSITION, &values_0_to_99},
};

static EffectSettings rp250_amp_settings[] = {
    {"Gain", AMP_GAIN, AMP_A_POSITION, &values_0_to_99},
    {"Level", AMP_LEVEL, AMP_A_POSITION, &values_0_to_99},
};

static EffectSettings rp250_amp_settings2[] = {
    {"Level", AMP_LEVEL, AMP_A_POSITION, &values_0_to_99},
};

static EffectSettings rp355_amp_settings_A[] = {
    {"Gain", AMP_GAIN, AMP_A_POSITION, &values_0_to_99},
    {"Level", AMP_LEVEL, AMP_A_POSITION, &values_0_to_99},
};

static EffectSettings rp355_amp_settings_B[] = {
    {"Gain", AMP_GAIN, AMP_B_POSITION, &values_0_to_99},
    {"Level", AMP_LEVEL, AMP_B_POSITION, &values_0_to_99},
};

static EffectSettings rp355_amp_settings2_A[] = {
    {"Level", AMP_LEVEL, AMP_A_POSITION, &values_0_to_99},
};

static EffectSettings rp355_amp_settings2_B[] = {
    {"Level", AMP_LEVEL, AMP_B_POSITION, &values_0_to_99},
};

static EffectSettings rp500_amp_settings[] = {
    {"Gain", AMP_GAIN, AMP_A_POSITION, &values_0_to_99},
    {"Level", AMP_LEVEL, AMP_A_POSITION, &values_0_to_99},
    {"Bass", AMP_BASS, AMP_A_POSITION, &values_1_to_10_step_0p1},
    {"Mid", AMP_MID, AMP_A_POSITION, &values_1_to_10_step_0p1},
    {"Treble", AMP_TREBLE, AMP_A_POSITION, &values_1_to_10_step_0p1},
};

static EffectSettings rp500_amp_settings2[] = {
    {"Level", AMP_LEVEL, AMP_A_POSITION, &values_0_to_99},
    {"Bass", AMP_BASS, AMP_A_POSITION, &values_1_to_10_step_0p1},
    {"Mid", AMP_MID, AMP_A_POSITION, &values_1_to_10_step_0p1},
    {"Treble", AMP_TREBLE, AMP_A_POSITION, &values_1_to_10_step_0p1},
};

static EffectSettings rp500_amp_settings3[] = {
    {"Level", AMP_LEVEL, AMP_A_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_ch1_cab_tuning_settings[] = {
    {"Tuning", AMP_CAB_TUNING, AMP_CAB_POSITION, &values_m12_to_12_semitones},
};

static EffectSettings gnx3k_ch2_cab_tuning_settings[] = {
    {"Tuning", AMP_CAB_TUNING, AMP_CAB_B_POSITION, &values_m12_to_12_semitones},
};

static EffectSettings gnx3k_ch1_amp_eq_settings[] = {
    {"Gain", AMP_GAIN, AMP_A_POSITION, &values_0_to_99},
    {"Bass Freq", AMP_BASS_FREQ, AMP_A_POSITION, &values_eq_bass_hz},
    {"Bass Level", AMP_BASS_LEVEL, AMP_A_POSITION, &values_eq_db},
    {"Mid Freq", AMP_MID_FREQ, AMP_A_POSITION, &values_eq_mid_hz},
    {"Mid Level", AMP_MID_LEVEL, AMP_A_POSITION, &values_eq_db},
    {"Treb Freq", AMP_TREBLE_FREQ, AMP_A_POSITION, &values_eq_treb_hz},
    {"Treb Level", AMP_TREBLE_LEVEL, AMP_A_POSITION, &values_eq_db},
    {"Presence", AMP_PRESENCE, AMP_A_POSITION, &values_eq_db},
    {"Level", AMP_LEVEL, AMP_A_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_ch2_amp_eq_settings[] = {
    {"Gain", AMP_GAIN, AMP_B_POSITION, &values_0_to_99},
    {"Bass Freq", AMP_BASS_FREQ, AMP_B_POSITION, &values_eq_bass_hz},
    {"Bass Level", AMP_BASS_LEVEL, AMP_B_POSITION, &values_eq_db},
    {"Mid Freq", AMP_MID_FREQ, AMP_B_POSITION, &values_eq_mid_hz},
    {"Mid Level", AMP_MID_LEVEL, AMP_B_POSITION, &values_eq_db},
    {"Treb Freq", AMP_TREBLE_FREQ, AMP_B_POSITION, &values_eq_treb_hz},
    {"Treb Level", AMP_TREBLE_LEVEL, AMP_B_POSITION, &values_eq_db},
    {"Presence", AMP_PRESENCE, AMP_B_POSITION, &values_eq_db},
    {"Level", AMP_LEVEL, AMP_B_POSITION, &values_0_to_99},
};

static EffectSettings rp250_eq_settings[] = {
    {"Bass", EQ_BASS, EQ_A_POSITION, &values_eq_db},
    {"Mid", EQ_MID, EQ_A_POSITION, &values_eq_db},
    {"Treble", EQ_TREB, EQ_A_POSITION, &values_eq_db},
    {"Mid Hz", EQ_MID_FREQ, EQ_A_POSITION, &values_eq_mid_hz},
    {"Treb Hz", EQ_TREB_FREQ, EQ_A_POSITION, &values_eq_treb_hz},
};

static EffectSettings rp355_eq_settings_A[] = {
    {"Bass", EQ_BASS, EQ_A_POSITION, &values_eq_db},
    {"Mid", EQ_MID, EQ_A_POSITION, &values_eq_db},
    {"Treble", EQ_TREB, EQ_A_POSITION, &values_eq_db},
    {"Presence", EQ_PRESENCE, EQ_A_POSITION, &values_eq_db},
    {"Mid Hz", EQ_MID_FREQ, EQ_A_POSITION, &values_eq_mid_hz},
    {"Treb Hz", EQ_TREB_FREQ, EQ_A_POSITION, &values_eq_treb_hz},
};

static EffectSettings rp355_eq_settings_B[] = {
    {"Bass", EQ_BASS, EQ_B_POSITION, &values_eq_db},
    {"Mid", EQ_MID, EQ_B_POSITION, &values_eq_db},
    {"Treble", EQ_TREB, EQ_B_POSITION, &values_eq_db},
    {"Presence", EQ_PRESENCE, EQ_B_POSITION, &values_eq_db},
    {"Mid Hz", EQ_MID_FREQ, EQ_B_POSITION, &values_eq_mid_hz},
    {"Treb Hz", EQ_TREB_FREQ, EQ_B_POSITION, &values_eq_treb_hz},
};

static EffectSettings rp500_eq_settings[] = {
    {"Low Level", EQ_BASS, EQ_A_POSITION, &values_eq_db},
    {"Mid Level", EQ_MID, EQ_A_POSITION, &values_eq_db},
    {"High Level", EQ_TREB, EQ_A_POSITION, &values_eq_db},
    {"Low Freq", EQ_LOW_FREQ, EQ_A_POSITION, &values_eq_low_freq},
    {"Mid Freq", EQ_MID_FREQ_RP500, EQ_A_POSITION, &values_eq_mid_freq},
    {"High Freq", EQ_HIGH_FREQ, EQ_A_POSITION, &values_eq_high_freq},
    {"Low Bandwidth", EQ_LOW_BANDWIDTH, EQ_A_POSITION, &values_eq_bandwidth},
    {"Mid Bandwidth", EQ_MID_BANDWIDTH, EQ_A_POSITION, &values_eq_bandwidth},
    {"High Bandwidth", EQ_HIGH_BANDWIDTH, EQ_A_POSITION, &values_eq_bandwidth},
};

static EffectSettings noisegate_silencer_settings[] = {
    {"Threshold", NOISEGATE_GATE_TRESHOLD, NOISEGATE_POSITION, &values_0_to_99},
    {"Attack", GNX3K_GATE_ATTACK, NOISEGATE_POSITION, &values_0_to_9},
};

static EffectSettings noisegate_pluck_settings[] = {
    {"Threshold", NOISEGATE_GATE_TRESHOLD, NOISEGATE_POSITION, &values_0_to_99},
    {"Attack", GNX3K_GATE_ATTACK, NOISEGATE_POSITION, &values_0_to_9},
    {"Sens", NOISEGATE_SWELL_SENS, NOISEGATE_POSITION, &values_0_to_99},
};

static EffectSettings noisegate_gate_settings[] = {
    {"Threshold", NOISEGATE_GATE_TRESHOLD, NOISEGATE_POSITION, &values_0_to_99},
    {"Attack", NOISEGATE_ATTACK, NOISEGATE_POSITION, &values_0_to_99},
    {"Release", NOISEGATE_RELEASE, NOISEGATE_POSITION, &values_0_to_99},
    {"Attn", NOISEGATE_ATTN, NOISEGATE_POSITION, &values_0_to_99},
};

static EffectSettings noisegate_swell_settings[] = {
    {"Sens", NOISEGATE_SWELL_SENS, NOISEGATE_POSITION, &values_0_to_99},
    {"Attack", NOISEGATE_ATTACK, NOISEGATE_POSITION, &values_0_to_99},
    {"Release", NOISEGATE_RELEASE, NOISEGATE_POSITION, &values_0_to_99},
    {"Attn", NOISEGATE_ATTN, NOISEGATE_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_chorus_settings[] = {
    {"Speed", CHORUS_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", CHORUS_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Predelay", CHORUS_PREDELAY, CHORUSFX_POSITION, &values_predelay_time},
    {"Wave", CHORUS_WAVE, CHORUSFX_POSITION, &values_waveform},
    {"Balance", CHORUS_BALANCE, CHORUSFX_POSITION, &values_balance},
    {"Level", CHORUS_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_flanger_settings[] = {
    {"Speed", FLANGER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", FLANGER_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Regen", FLANGER_REGEN, CHORUSFX_POSITION, &values_0_to_99},
    {"Waveform", FLANGER_WAVE, CHORUSFX_POSITION, &values_waveform},
    {"Balance", FLANGER_BALANCE, CHORUSFX_POSITION, &values_balance},
    {"Mix", FLANGER_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_phaser_settings[] = {
    {"Speed", PHASER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", PHASER_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Regen", PHASER_REGEN, CHORUSFX_POSITION, &values_0_to_99},
    {"Waveform", PHASER_WAVE, CHORUSFX_POSITION, &values_waveform},
    {"Balance", PHASER_BALANCE, CHORUSFX_POSITION, &values_balance},
    {"Level", PHASER_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_trigflanger_settings[] = {
    {"Speed", TRIG_FLANGER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Sens", TRIG_FLANGER_SENS, CHORUSFX_POSITION, &values_0_to_99},
    {"Lfo Start", TRIG_FLANGER_LFO_START, CHORUSFX_POSITION, &values_0_to_99},
    {"Mix", TRIG_FLANGER_MIX, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_trigphaser_settings[] = {
    {"Speed", TRIG_PHASER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Sens", TRIG_PHASER_SENS, CHORUSFX_POSITION, &values_0_to_99},
    {"Lfo Start", TRIG_PHASER_LFO_START, CHORUSFX_POSITION, &values_0_to_99},
    {"Mix", TRIG_FLANGER_MIX, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_unovibe_settings[] = {
    {"Chorus/Vibrato", UNOVIBE_CHORUS_VIBRATO, CHORUSFX_POSITION, &values_chorus_vibrato},
    {"Intensity", UNOVIBE_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Pedal Speed", UNOVIBE_PEDAL_SPEED, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_vibrato_settings[] = {
    {"Speed", VIBRATO_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", VIBRATO_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Waveform", VIBRATO_WAVEFORM, CHORUSFX_POSITION, &values_waveform},
};

static EffectSettings gnx3k_rotary_settings[] = {
    {"Speed", ROTARY_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", ROTARY_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Doppler", ROTARY_DOPPLER, CHORUSFX_POSITION, &values_0_to_99},
    {"X-Over", ROTARY_CROSSOVER, CHORUSFX_POSITION, &values_200hz_to_1_5khz},
    {"Balance", ROTARY_BALANCE, CHORUSFX_POSITION, &values_balance},
    {"Mix", ROTARY_MIX, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_autoya_settings[] = {
    {"Speed", AUTOYA_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", AUTOYA_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Range", GNX3K_AUTOYA_RANGE, CHORUSFX_POSITION, &values_0_to_49},
    {"Balance", AUTOYA_BALANCE, CHORUSFX_POSITION, &values_balance},
    {"Mix", AUTOYA_MIX, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_yaya_settings[] = {
    {"Pedal", YAYA_PEDAL, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", YAYA_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Range", GNX3K_YAYA_RANGE, CHORUSFX_POSITION, &values_0_to_49},
    {"Balance", YAYA_BALANCE, CHORUSFX_POSITION, &values_balance},
    {"Mix", YAYA_MIX, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_synthtalk_settings[] = {
    {"Attack", SYNTH_TALK_ATTACK, CHORUSFX_POSITION, &values_0_to_99},
    {"Release", GNX3K_SYNTH_TALK_RELEASE, CHORUSFX_POSITION, &values_synth_talk_release},
    {"Sens", SYNTH_TALK_SENS, CHORUSFX_POSITION, &values_0_to_99},
    {"Vox", SYNTH_TALK_VOX, CHORUSFX_POSITION, &values_0_to_99},
    {"Balance", SYNTH_TALK_BALANCE, CHORUSFX_POSITION, &values_balance},
};

static EffectSettings gnx3k_envelope_settings[] = {
    {"Sensitivity", ENVELOPE_SENSITIVITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Range", ENVELOPE_RANGE, CHORUSFX_POSITION, &values_0_to_99},
    {"Balance", ENVELOPE_BALANCE, CHORUSFX_POSITION, &values_balance},
    {"Mix", ENVELOPE_MIX, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_mod_detune_settings[] = {
    {"Shift Amount", DETUNE_AMOUNT, CHORUSFX_POSITION, &values_m24_to_24},
    {"Balance", DETUNE_BALANCE, CHORUSFX_POSITION, &values_balance},
    {"Level", DETUNE_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_mod_pitch_settings[] = {
    {"Shift Amount", PITCH_AMOUNT, CHORUSFX_POSITION, &values_m12_to_24},
    {"Balance", PITCH_BALANCE, CHORUSFX_POSITION, &values_balance},
    {"Level", GNX3K_PITCH_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_ce_settings[] = {
    {"Speed", CHORUS_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", CHORUS_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_tc_settings[] = {
    {"Speed", CHORUS_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Width", CHORUS_WIDTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Intensity", CHORUS_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_dual_settings[] = {
    {"Speed", CHORUS_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", CHORUS_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Level", CHORUS_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
    {"Wave", CHORUS_WAVE, CHORUSFX_POSITION, &values_waveform},
};

static EffectSettings chorusfx_glisten_settings[] = {
    {"Speed", CHORUS_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", CHORUS_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Level", CHORUS_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_multi_settings[] = {
    {"Speed", CHORUS_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", CHORUS_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Level", CHORUS_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
    {"Wave", CHORUS_WAVE, CHORUSFX_POSITION, &values_waveform},
};

static EffectSettings chorusfx_voo_doo_settings[] = {
    {"Speed", CHORUS_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Intensity", CHORUS_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_clone_settings[] = {
    {"Rate", CHORUS_RATE, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", CHORUS_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_flanger_settings[] = {
    {"Speed", FLANGER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", FLANGER_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Regen", FLANGER_REGEN, CHORUSFX_POSITION, &values_0_to_99},
    {"Level", FLANGER_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
    {"Wave", FLANGER_WAVE, CHORUSFX_POSITION, &values_waveform},
};

static EffectSettings chorusfx_trig_flanger_settings[] = {
    {"Speed", TRIG_FLANGER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Sens", TRIG_FLANGER_SENS, CHORUSFX_POSITION, &values_0_to_99},
    {"Lfo Start", TRIG_FLANGER_LFO_START, CHORUSFX_POSITION, &values_0_to_99},
    {"Level", TRIG_FLANGER_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_fltflanger_settings[] = {
    {"Speed", FLANGER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", FLANGER_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Regen", FLANGER_REGEN, CHORUSFX_POSITION, &values_0_to_99},
    {"Frequency", FLTFLANGER_FREQ, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_mxr_flanger_settings[] = {
    {"Speed", FLANGER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Width", MXR_FLANGER_WIDTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Regen", FLANGER_REGEN, CHORUSFX_POSITION, &values_0_to_99},
    {"Manual", MXR_FLANGER_MANUAL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_eh_flanger_settings[] = {
    {"Rate", EH_FLANGER_RATE, CHORUSFX_POSITION, &values_0_to_99},
    {"Range", EH_FLANGER_RANGE, CHORUSFX_POSITION, &values_0_to_99},
    {"Color", EH_FLANGER_COLOR, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_ad_flanger_settings[] = {
    {"Speed", FLANGER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Enhance", AD_FLANGER_ENHANCE, CHORUSFX_POSITION, &values_0_to_99},
    {"Range", EH_FLANGER_RANGE, CHORUSFX_POSITION, &values_0_to_99},
    {"Harmonics", AD_FLANGER_HARMONICS, CHORUSFX_POSITION, &values_odd_even},
    {"Manual", MXR_FLANGER_MANUAL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_phaser_settings[] = {
    {"Speed", PHASER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", PHASER_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Regen", PHASER_REGEN, CHORUSFX_POSITION, &values_0_to_99},
    {"Level", PHASER_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
    {"Wave", PHASER_WAVE, CHORUSFX_POSITION, &values_waveform},
};

static EffectSettings chorusfx_trig_phaser_settings[] = {
    {"Speed", TRIG_PHASER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Sens", TRIG_PHASER_SENS, CHORUSFX_POSITION, &values_0_to_99},
    {"Lfo Start", TRIG_PHASER_LFO_START, CHORUSFX_POSITION, &values_0_to_99},
    {"Level", TRIG_PHASER_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_mx_phaser_settings[] = {
    {"Speed", PHASER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Intensity", MX_PHASER_INTENSITY, CHORUSFX_POSITION, &values_1_to_4},
};

static EffectSettings chorusfx_eh_phaser_settings[] = {
    {"Rate", EH_PHASER_RATE, CHORUSFX_POSITION, &values_0_to_99},
    {"Color", EH_PHASER_COLOR, CHORUSFX_POSITION, &values_on_off},
};

static EffectSettings chorusfx_vibrato_settings[] = {
    {"Speed", VIBRATO_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", VIBRATO_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_rotary_settings[] = {
    {"Speed", ROTARY_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Intensity", ROTARY_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Doppler", ROTARY_DOPPLER, CHORUSFX_POSITION, &values_0_to_99},
    {"Crossover", ROTARY_CROSSOVER, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_vibropan_settings[] = {
    {"Speed", VIBROPAN_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", VIBROPAN_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Vibra", VIBROPAN_VIBRA, CHORUSFX_POSITION, &values_0_to_99},
    {"Wave", VIBROPAN_WAVE, CHORUSFX_POSITION, &values_waveform},
};

static EffectSettings chorusfx_unovibe_settings[] = {
    {"Pedal Speed", UNOVIBE_PEDAL_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Intensity", UNOVIBE_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Chorus/Vibrato", UNOVIBE_CHORUS_VIBRATO, CHORUSFX_POSITION, &values_chorus_vibrato},
    {"Volume", UNOVIBE_VOLUME, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_tremolo_settings[] = {
    {"Speed", TREMOLO_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", TREMOLO_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Wave", TREMOLO_WAVE, CHORUSFX_POSITION, &values_waveform},
};

static EffectSettings chorusfx_trem_settings[] = {
    {"Speed", TREMOLO_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", TREMOLO_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_panner_settings[] = {
    {"Speed", PANNER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Depth", PANNER_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Wave", PANNER_WAVE, CHORUSFX_POSITION, &values_waveform},
};

static EffectSettings chorusfx_envelope_settings[] = {
    {"Sensitivity", ENVELOPE_SENSITIVITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Range", ENVELOPE_RANGE, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_fx25_settings[] = {
    {"Sensitivity", ENVELOPE_SENSITIVITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Range", ENVELOPE_RANGE, CHORUSFX_POSITION, &values_0_to_99},
    {"Blend", ENVELOPE_BLEND, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_autoya_settings[] = {
    {"Speed", AUTOYA_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Intensity", AUTOYA_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Range", AUTOYA_RANGE, CHORUSFX_POSITION, &values_0_to_49},
};

static EffectSettings chorusfx_yaya_settings[] = {
    {"Pedal", YAYA_PEDAL, CHORUSFX_POSITION, &values_0_to_99},
    {"Intensity", YAYA_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Range", YAYA_RANGE, CHORUSFX_POSITION, &values_0_to_49},
};

static EffectSettings chorusfx_synth_talk_settings[] = {
    {"Attack", SYNTH_TALK_ATTACK, CHORUSFX_POSITION, &values_0_to_99},
    {"Release", SYNTH_TALK_RELEASE, CHORUSFX_POSITION, &values_0_to_99},
    {"Sens", SYNTH_TALK_SENS, CHORUSFX_POSITION, &values_0_to_99},
    {"Vox", SYNTH_TALK_VOX, CHORUSFX_POSITION, &values_0_to_99},
    {"Balance", SYNTH_TALK_BALANCE, CHORUSFX_POSITION, &values_balance},
};

static EffectSettings chorusfx_step_filter_settings[] = {
    {"Speed", STEP_FILTER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Intensity", STEP_FILTER_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_sample_hold_settings[] = {
    {"Speed", SAMPLE_HOLD_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Intensity", SAMPLE_HOLD_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_whammy_settings[] = {
    {"Pedal", WHAMMY_PEDAL, CHORUSFX_POSITION, &values_0_to_99},
    {"Mix", WHAMMY_MIX, CHORUSFX_POSITION, &values_0_to_99},
    {"Amount", WHAMMY_AMOUNT, CHORUSFX_POSITION, &values_whammy_amount},
};

static EffectSettings chorusfx_pitch_shift_settings[] = {
    {"Amount", PITCH_AMOUNT, CHORUSFX_POSITION, &values_m24_to_24},
    {"Mix", PITCH_MIX, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_detune_settings[] = {
    {"Amount", DETUNE_AMOUNT, CHORUSFX_POSITION, &values_m24_to_24},
    {"Level", DETUNE_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_ips_settings[] = {
    {"Shift", IPS_SHIFT_AMOUNT, CHORUSFX_POSITION, &values_ips_shift},
    {"Key", IPS_KEY, CHORUSFX_POSITION, &values_ips_key},
    {"Scale", IPS_SCALE, CHORUSFX_POSITION, &values_ips_scale},
    {"Level", IPS_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings chorusfx_octaver_settings[] = {
    {"Octave 1", OCTAVER_OCTAVE1, CHORUSFX_POSITION, &values_0_to_99},
    {"Octave 2", OCTAVER_OCTAVE2, CHORUSFX_POSITION, &values_0_to_99},
    {"Dry Level", OCTAVER_DRY_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_delay_settings[] = {
    {"Time", GNX3K_DELAY_TIME, DELAY_POSITION, &values_delay_time_0_2000},
    {"Feedback", GNX3K_DELAY_FEEDBACK, DELAY_POSITION, &values_delay_repeats},
    {"Thresh", GNX3K_DELAY_DUCK_THRESH, DELAY_POSITION, &values_delay_thresh},
    {"Atten", GNX3K_DELAY_DUCK_ATTEN, DELAY_POSITION, &values_0_to_99},
    {"Balance", GNX3K_DELAY_BALANCE, DELAY_POSITION, &values_balance},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_delay_spread_settings[] = {
    {"Time", GNX3K_DELAY_TIME, DELAY_POSITION, &values_delay_time_0_2000},
    {"Feedback", GNX3K_DELAY_FEEDBACK, DELAY_POSITION, &values_delay_repeats},
    {"Thresh", GNX3K_DELAY_DUCK_THRESH, DELAY_POSITION, &values_delay_thresh},
    {"Atten", GNX3K_DELAY_DUCK_ATTEN, DELAY_POSITION, &values_0_to_99},
    {"Spread", GNX3K_DELAY_SPREAD, DELAY_POSITION, &values_delay_spread_0_49},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings delay_analog_settings[] = {
    {"Time", DELAY_TIME, DELAY_POSITION, &values_delay_time},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
};

static EffectSettings delay_dm_settings[] = {
    {"Repeat Rate", DELAY_REPEAT_RATE_DM, DELAY_POSITION, &values_0_to_99},
    {"Echo", DELAY_ECHO, DELAY_POSITION, &values_0_to_99},
    {"Intensity", DELAY_INTENSITY, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings delay_digital_settings[] = {
    {"Time", DELAY_TIME, DELAY_POSITION, &values_delay_time},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Ducker thresh", DELAY_DUCK_THRESH, DELAY_POSITION, &values_0_to_99},
    {"Ducker level", DELAY_DUCK_LEVEL, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings delay_modulated_settings[] = {
    {"Time", DELAY_TIME, DELAY_POSITION, &values_delay_time},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Depth", DELAY_DEPTH, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings delay_pong_settings[] = {
    {"Time", DELAY_TIME, DELAY_POSITION, &values_delay_time},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Ducker thresh", DELAY_DUCK_THRESH, DELAY_POSITION, &values_0_to_99},
    {"Ducker level", DELAY_DUCK_LEVEL, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings delay_tape_settings[] = {
    {"Time", DELAY_TIME, DELAY_POSITION, &values_delay_time},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Delay Tape Wow", DELAY_TAPE_WOW, DELAY_POSITION, &values_0_to_99},
    {"Flutter", DELAY_TAPE_FLUTTER, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings delay_echoplex_settings[] = {
    {"Time", DELAY_ECHOPLEX_TIME, DELAY_POSITION, &values_0_to_99},
    {"Repeats", DELAY_REPEATS_0_99, DELAY_POSITION, &values_0_to_99},
    {"Volume", DELAY_VOLUME, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings rp500_delay_digital_settings[] = {
    {"Tap Time", DELAY_TAP_TIME, DELAY_POSITION, &values_delay_time_0_5000},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Duck Thresh", DELAY_DUCK_THRESH, DELAY_POSITION, &values_0_to_99},
    {"Duck Level", DELAY_DUCK_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings rp500_delay_analog_settings[] = {
    {"Tap Time", DELAY_TAP_TIME, DELAY_POSITION, &values_delay_time_0_5000},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings rp500_delay_dm_settings[] = {
    {"Repeat Rate", DELAY_REPEAT_RATE, DELAY_POSITION, &values_delay_repeat_rate_24_310},
    {"Echo", DELAY_ECHO, DELAY_POSITION, &values_0_to_99},
    {"Intensity", DELAY_INTENSITY, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings rp500_delay_echoplex_settings[] = {
    {"Time", DELAY_TIME_0_760, DELAY_POSITION, &values_delay_time_110_870},
    {"Volume", DELAY_VOLUME, DELAY_POSITION, &values_0_to_99},
    {"Repeats", DELAY_REPEATS_0_99, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings rp500_delay_modulated_settings[] = {
    {"Tap Time", DELAY_TAP_TIME_0_4990, DELAY_POSITION, &values_delay_time_0_4990},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Depth", DELAY_DEPTH, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings rp500_delay_pong_settings[] = {
    {"Tap Time", DELAY_TAP_TIME, DELAY_POSITION, &values_delay_time_0_5000},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Duck Thresh", DELAY_DUCK_THRESH, DELAY_POSITION, &values_0_to_99},
    {"Duck Level", DELAY_DUCK_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings rp500_delay_reverse_settings[] = {
    {"Time", DELAY_TIME_0_4650, DELAY_POSITION, &values_delay_time_0_4650},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Mix", DELAY_MIX, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings rp500_delay_tape_settings[] = {
    {"Tap Time", DELAY_TAP_TIME_0_4990, DELAY_POSITION, &values_delay_time_0_4990},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Delay Tape Wow", DELAY_TAPE_WOW, DELAY_POSITION, &values_0_to_99},
    {"Delay Tape Flutter", DELAY_TAPE_FLUTTER, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings rp1000_delay_lo_fi_settings[] = {
    {"Time", DELAY_TAP_TIME, DELAY_POSITION, &values_delay_time_0_5000},
    {"Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Repeats", DELAY_REPEATS_0_99, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings rp1000_delay_2_tap_settings[] = {
    {"Time", DELAY_TAP_TIME, DELAY_POSITION, &values_delay_time_0_5000},
    {"Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Ratio", DELAY_TAP_RATIO, DELAY_POSITION, &values_delay_repeats},
    {"Mix", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
};

static EffectSettings reverb_twin_settings[] = {
    {"Reverb", REVERB_LEVEL, REVERB_POSITION, &values_0_to_99},
};

static EffectSettings gnx3k_reverb_settings[] = {
    {"Predelay", REVERB_PREDELAY, REVERB_POSITION, &values_0_to_15},
    {"Decay", REVERB_DECAY, REVERB_POSITION, &values_0_to_99},
    {"Damping", REVERB_DAMPING, REVERB_POSITION, &values_0_to_99},
    {"Balance", REVERB_BALANCE, REVERB_POSITION, &values_balance},
    {"Level", REVERB_LEVEL, REVERB_POSITION, &values_0_to_99},
};

static EffectSettings lfo1_settings[] = {
    {"Heel", LFO_MIN, LFO1_POSITION, &values_0_to_99},
    {"Toe", LFO_MAX, LFO1_POSITION, &values_0_to_99},
    {"Waveform", LFO_WAVEFORM, LFO1_POSITION, &values_waveform},
    {"Speed(HZ)", LFO_SPEED, LFO1_POSITION, &values_lfo_speed},
};

static EffectSettings lfo2_settings[] = {
    {"Heel", LFO_MIN, LFO2_POSITION, &values_0_to_99},
    {"Toe", LFO_MAX, LFO2_POSITION, &values_0_to_99},
    {"Waveform", LFO_WAVEFORM, LFO2_POSITION, &values_waveform},
    {"Speed(HZ)", LFO_SPEED, LFO2_POSITION, &values_lfo_speed},
};

static EffectSettings reverb_lex_settings[] = {
    {"Predelay", REVERB_PREDELAY, REVERB_POSITION, &values_0_to_15},
    {"Decay", REVERB_DECAY, REVERB_POSITION, &values_0_to_99},
    {"Liveliness", REVERB_LIVELINESS, REVERB_POSITION, &values_0_to_99},
    {"Level", REVERB_LEVEL, REVERB_POSITION, &values_0_to_99},
};

static EffectSettings tone_lib_level_a_settings[] = {
    {"Tone Effect Level", FX_LIB_LEVEL, LIB_POSITION_A, &values_0_to_99},
    {"Tone Level 1", FX_LIB_LEVEL_MAX1, LIB_POSITION_A, &values_0_to_99},
    {"Tone Level 2", FX_LIB_LEVEL_MAX2, LIB_POSITION_A, &values_0_to_99},
    {"Tone Level 3", FX_LIB_LEVEL_MAX3, LIB_POSITION_A, &values_0_to_99},
};

static EffectSettings tone_lib_level_b_settings[] = {
    {"Tone Effect Level", FX_LIB_LEVEL, LIB_POSITION_B, &values_0_to_99},
    {"Tone Level 1", FX_LIB_LEVEL_MAX1, LIB_POSITION_B, &values_0_to_99},
    {"Tone Level 2", FX_LIB_LEVEL_MAX2, LIB_POSITION_B, &values_0_to_99},
    {"Tone Level 3", FX_LIB_LEVEL_MAX3, LIB_POSITION_B, &values_0_to_99},
};

static EffectGroup gnx3k_wah_group[] = {
    {GNX3K_WAH_TYPE_CRY, "Cry", gnx3k_wah_settings, G_N_ELEMENTS(gnx3k_wah_settings)},
    {GNX3K_WAH_TYPE_BOUTIQUE, "Boutique", gnx3k_wah_settings, G_N_ELEMENTS(gnx3k_wah_settings)},
    {GNX3K_WAH_TYPE_FULLRANGE, "Full-Range", gnx3k_wah_settings, G_N_ELEMENTS(gnx3k_wah_settings)},
};

static EffectGroup wah_group[] = {
    {WAH_TYPE_CRY, "Cry Wah", wah_settings, G_N_ELEMENTS(wah_settings)},
    {WAH_TYPE_FULLRANGE, "Fullrange Wah", wah_settings, G_N_ELEMENTS(wah_settings)},
    {WAH_TYPE_CLYDE, "Clyde Wah", wah_settings, G_N_ELEMENTS(wah_settings)},
};

static EffectGroup gnx3k_whammy_group[] = {
    {GNX3K_WHAM_TYPE_WHAMMY, "Whammy", gnx3k_whammy_settings, G_N_ELEMENTS(gnx3k_whammy_settings)},
    {GNX3K_WHAM_TYPE_IPS, "IPS", gnx3k_ips_settings, G_N_ELEMENTS(gnx3k_ips_settings)},
    {GNX3K_WHAM_TYPE_DETUNE, "Detune", gnx3k_detune_settings, G_N_ELEMENTS(gnx3k_detune_settings)},
    {GNX3K_WHAM_TYPE_PITCH, "Pitch Shift", gnx3k_pitch_settings, G_N_ELEMENTS(gnx3k_pitch_settings)},
    {GNX3K_WHAM_TYPE_TALK1, "Talker 1", gnx3k_talk_settings, G_N_ELEMENTS(gnx3k_talk_settings)},
    {GNX3K_WHAM_TYPE_TALK2, "Talker 2", gnx3k_talk_settings, G_N_ELEMENTS(gnx3k_talk_settings)},
    {GNX3K_WHAM_TYPE_TALK3, "Talker 3", gnx3k_talk_settings, G_N_ELEMENTS(gnx3k_talk_settings)},
    {GNX3K_WHAM_TYPE_TALK4, "Talker 4", gnx3k_talk_settings, G_N_ELEMENTS(gnx3k_talk_settings)},
    {GNX3K_WHAM_TYPE_TALK5, "Talker 5", gnx3k_talk_settings, G_N_ELEMENTS(gnx3k_talk_settings)},
};

static EffectGroup gnx3k_amp_channel_group[] = {
    {-1, NULL, gnx3k_amp_channel_settings, G_N_ELEMENTS(gnx3k_amp_channel_settings)},
};

/** \todo it's not part of Preset, but should appear in GUI */
static EffectGroup global_group[] = {
    {-1, NULL, global_settings, G_N_ELEMENTS(global_settings)},
};

static EffectGroup misc_group[] = {
    {-1, NULL, misc_settings, G_N_ELEMENTS(misc_settings)},
};

static EffectGroup pre_fx_group[] = {
    {-1, NULL, pre_fx_settings, G_N_ELEMENTS(pre_fx_settings)},
};

static EffectGroup post_fx_group[] = {
    {-1, NULL, post_fx_settings, G_N_ELEMENTS(post_fx_settings)},
};

static EffectGroup gnx3k_preset_group[] = {
    {-1, NULL, gnx3k_preset_settings, G_N_ELEMENTS(gnx3k_preset_settings)},
};

static EffectGroup gnx_comp_group[] = {
    {-1, NULL, gnx_comp_settings, G_N_ELEMENTS(gnx_comp_settings)},
};

static EffectGroup rp250_comp_group[] = {
    {COMP_TYPE_DIGI, "Digital compressor", comp_digi_settings, G_N_ELEMENTS(comp_digi_settings)},
    {COMP_TYPE_CS, "CS compressor", comp_cs_settings, G_N_ELEMENTS(comp_cs_settings)},
};

static EffectGroup rp355_comp_group[] = {
    {COMP_TYPE_DIGI, "Digital compressor", comp_digi_settings, G_N_ELEMENTS(comp_digi_settings)},
    {COMP_TYPE_CS, "CS compressor", comp_cs_settings, G_N_ELEMENTS(comp_cs_settings)},
    {COMP_TYPE_DYNA, "Dyna comp", comp_dyna_settings, G_N_ELEMENTS(comp_dyna_settings)},
};

static EffectGroup rp500_comp_group[] = {
    {COMP_TYPE_DIGI, "Digital compressor", comp_digi_settings, G_N_ELEMENTS(comp_digi_settings)},
    {COMP_TYPE_CS, "CS compressor", comp_cs_settings, G_N_ELEMENTS(comp_cs_settings)},
    {COMP_TYPE_DYNA, "Dyna comp", comp_dyna_settings, G_N_ELEMENTS(comp_dyna_settings)},
};

static EffectGroup rp150_dist_group[] = {
    {DIST_TYPE_SCREAMER, "Screamer", dist_screamer_settings, G_N_ELEMENTS(dist_screamer_settings)},
    {DIST_TYPE_DOD250, "DOD250", dist_dod250_settings, G_N_ELEMENTS(dist_dod250_settings)},
    {DIST_TYPE_RODENT, "Rodent", dist_rodent_settings, G_N_ELEMENTS(dist_rodent_settings)},
    {DIST_TYPE_DS, "DS", dist_ds_settings, G_N_ELEMENTS(dist_ds_settings)},
    {DIST_TYPE_GRUNGE, "Grunge", dist_grunge_settings, G_N_ELEMENTS(dist_grunge_settings)},
    {DIST_TYPE_ZONE, "Zone", dist_zone_settings, G_N_ELEMENTS(dist_zone_settings)},
    {DIST_TYPE_GONK, "Gonk", dist_gonk_settings, G_N_ELEMENTS(dist_gonk_settings)},
    {DIST_TYPE_FUZZY, "Fuzzy", dist_fuzzy_settings, G_N_ELEMENTS(dist_fuzzy_settings)},
    {DIST_TYPE_MP, "Big MP", dist_mp_settings, G_N_ELEMENTS(dist_mp_settings)},
};

static EffectGroup rp155_dist_group[] = {
    {DIST_TYPE_SCREAMER, "Screamer", dist_screamer_settings, G_N_ELEMENTS(dist_screamer_settings)},
    {DIST_TYPE_808, "808", dist_808_settings, G_N_ELEMENTS(dist_808_settings)},
    {DIST_TYPE_DOD250, "DOD250", dist_dod250_settings, G_N_ELEMENTS(dist_dod250_settings)},
    {DIST_TYPE_RODENT, "Rodent", dist_rodent_settings, G_N_ELEMENTS(dist_rodent_settings)},
    {DIST_TYPE_DS, "DS", dist_ds_settings, G_N_ELEMENTS(dist_ds_settings)},
    {DIST_TYPE_GRUNGE, "Grunge", dist_grunge_settings, G_N_ELEMENTS(dist_grunge_settings)},
    {DIST_TYPE_ZONE, "Zone", dist_zone_settings, G_N_ELEMENTS(dist_zone_settings)},
    {DIST_TYPE_GONK, "Gonk", dist_gonk_settings, G_N_ELEMENTS(dist_gonk_settings)},
    {DIST_TYPE_FUZZY, "Fuzzy", dist_fuzzy_settings, G_N_ELEMENTS(dist_fuzzy_settings)},
    {DIST_TYPE_MP, "Big MP", dist_mp_settings, G_N_ELEMENTS(dist_mp_settings)},
};

static EffectGroup rp250_dist_group[] = {
    {DIST_TYPE_SCREAMER, "Screamer", dist_screamer_settings, G_N_ELEMENTS(dist_screamer_settings)},
    {DIST_TYPE_808, "808", dist_808_settings, G_N_ELEMENTS(dist_808_settings)},
    {DIST_TYPE_GUYOD, "GuyOD", dist_guyod_settings, G_N_ELEMENTS(dist_guyod_settings)},
    {DIST_TYPE_DOD250, "DOD250", dist_dod250_settings, G_N_ELEMENTS(dist_dod250_settings)},
    {DIST_TYPE_RODENT, "Rodent", dist_rodent_settings, G_N_ELEMENTS(dist_rodent_settings)},
    {DIST_TYPE_MX, "MX", dist_mx_settings, G_N_ELEMENTS(dist_mx_settings)},
    {DIST_TYPE_DS, "DS", dist_ds_settings, G_N_ELEMENTS(dist_ds_settings)},
    {DIST_TYPE_GRUNGE, "Grunge", dist_grunge_settings, G_N_ELEMENTS(dist_grunge_settings)},
    {DIST_TYPE_ZONE, "Zone", dist_zone_settings, G_N_ELEMENTS(dist_zone_settings)},
    {DIST_TYPE_DEATH, "Death", dist_death_settings, G_N_ELEMENTS(dist_death_settings)},
    {DIST_TYPE_GONK, "Gonk", dist_gonk_settings, G_N_ELEMENTS(dist_gonk_settings)},
    {DIST_TYPE_FUZZY, "Fuzzy", dist_fuzzy_settings, G_N_ELEMENTS(dist_fuzzy_settings)},
    {DIST_TYPE_MP, "Big MP", dist_mp_settings, G_N_ELEMENTS(dist_mp_settings)},
};

static EffectGroup rp355_dist_group[] = {
    {DIST_TYPE_SCREAMER, "Screamer", dist_screamer_settings, G_N_ELEMENTS(dist_screamer_settings)},
    {DIST_TYPE_808, "808", dist_808_settings, G_N_ELEMENTS(dist_808_settings)},
    {DIST_TYPE_SPARKDRIVE, "Sparkdrive", dist_sparkdrive_settings, G_N_ELEMENTS(dist_sparkdrive_settings)},
    {DIST_TYPE_GUYOD, "OD Overdrive", dist_guyod_settings, G_N_ELEMENTS(dist_guyod_settings)},
    {DIST_TYPE_DOD250, "DOD250", dist_dod250_settings, G_N_ELEMENTS(dist_dod250_settings)},
    {DIST_TYPE_REDLINE, "Redline", dist_redline_settings, G_N_ELEMENTS(dist_redline_settings)},
    {DIST_TYPE_RODENT, "Rodent", dist_rodent_settings, G_N_ELEMENTS(dist_rodent_settings)},
    {DIST_TYPE_MX, "MX", dist_mx_settings, G_N_ELEMENTS(dist_mx_settings)},
    {DIST_TYPE_DS, "DS", dist_ds_settings, G_N_ELEMENTS(dist_ds_settings)},
    {DIST_TYPE_GRUNGE, "Grunge", dist_grunge_settings, G_N_ELEMENTS(dist_grunge_settings)},
    {DIST_TYPE_ZONE, "Zone", dist_zone_settings, G_N_ELEMENTS(dist_zone_settings)},
    {DIST_TYPE_DEATH, "Death", dist_death_settings, G_N_ELEMENTS(dist_death_settings)},
    {DIST_TYPE_GONK, "Gonk", dist_gonk_settings, G_N_ELEMENTS(dist_gonk_settings)},
    {DIST_TYPE_8TAVIA, "8tavia", dist_8tavia_settings, G_N_ELEMENTS(dist_8tavia_settings)},
    {DIST_TYPE_FUZZLATOR, "Fuzzlator", dist_fuzzlator_settings, G_N_ELEMENTS(dist_fuzzlator_settings)},
    {DIST_TYPE_CLASSIC_FUZZ, "Classic Fuzz", dist_classic_fuzz_settings, G_N_ELEMENTS(dist_classic_fuzz_settings)},
    {DIST_TYPE_FUZZY, "Fuzzy", dist_fuzzy_settings, G_N_ELEMENTS(dist_fuzzy_settings)},
    {DIST_TYPE_MP, "Big MP", dist_mp_settings, G_N_ELEMENTS(dist_mp_settings)},
};

static EffectGroup rp500_dist_group[] = {
    {DIST_TYPE_SCREAMER, "Screamer", dist_screamer_settings, G_N_ELEMENTS(dist_screamer_settings)},
    {DIST_TYPE_808, "808", dist_808_settings, G_N_ELEMENTS(dist_808_settings)},
    {DIST_TYPE_SPARKDRIVE, "Sparkdrive", dist_sparkdrive_settings, G_N_ELEMENTS(dist_sparkdrive_settings)},
    {DIST_TYPE_GUYOD, "OD Overdrive", dist_guyod_settings, G_N_ELEMENTS(dist_guyod_settings)},
    {DIST_TYPE_DOD250, "DOD250", dist_dod250_settings, G_N_ELEMENTS(dist_dod250_settings)},
    {DIST_TYPE_REDLINE, "Redline", dist_redline_settings, G_N_ELEMENTS(dist_redline_settings)},
    {DIST_TYPE_RODENT, "Rodent", dist_rodent_settings, G_N_ELEMENTS(dist_rodent_settings)},
    {DIST_TYPE_MX, "MX", dist_mx_settings, G_N_ELEMENTS(dist_mx_settings)},
    {DIST_TYPE_DS, "DS", dist_ds_settings, G_N_ELEMENTS(dist_ds_settings)},
    {DIST_TYPE_GRUNGE, "Grunge", dist_grunge_settings, G_N_ELEMENTS(dist_grunge_settings)},
    {DIST_TYPE_ZONE, "Zone", dist_zone_settings, G_N_ELEMENTS(dist_zone_settings)},
    {DIST_TYPE_DEATH, "Death", dist_death_settings, G_N_ELEMENTS(dist_death_settings)},
    {DIST_TYPE_GONK, "Gonk", dist_gonk_settings, G_N_ELEMENTS(dist_gonk_settings)},
    {DIST_TYPE_8TAVIA, "8tavia", dist_8tavia_settings, G_N_ELEMENTS(dist_8tavia_settings)},
    {DIST_TYPE_FUZZLATOR, "Fuzzlator", dist_fuzzlator_settings, G_N_ELEMENTS(dist_fuzzlator_settings)},
    {DIST_TYPE_CLASSIC_FUZZ, "Classic Fuzz", dist_classic_fuzz_settings, G_N_ELEMENTS(dist_classic_fuzz_settings)},
    {DIST_TYPE_FUZZY, "Fuzzy", dist_fuzzy_settings, G_N_ELEMENTS(dist_fuzzy_settings)},
    {DIST_TYPE_MP, "Big MP", dist_mp_settings, G_N_ELEMENTS(dist_mp_settings)},
};

static EffectGroup rp1000_dist_group[] = {
    {DIST_TYPE_SCREAMER, "Screamer", dist_screamer_settings, G_N_ELEMENTS(dist_screamer_settings)},
    {DIST_TYPE_808, "808", dist_808_settings, G_N_ELEMENTS(dist_808_settings)},
    {DIST_TYPE_TS_MOD, "TS Mod", dist_ts_mod_settings, G_N_ELEMENTS(dist_ts_mod_settings)},
    {DIST_TYPE_SD_ODRV, "SD Overdrive", dist_sd_odrv_settings, G_N_ELEMENTS(dist_sd_odrv_settings)},
    {DIST_TYPE_OD_ODRV, "OD Overdrive", dist_od_odrv_settings, G_N_ELEMENTS(dist_od_odrv_settings)},
    {DIST_TYPE_SPARKDRIVE, "Sparkdrive", dist_sparkdrive_settings, G_N_ELEMENTS(dist_sparkdrive_settings)},
    {DIST_TYPE_GUYOD, "Guy Overdrive", dist_guyod_settings, G_N_ELEMENTS(dist_guyod_settings)},
    {DIST_TYPE_DOD250, "DOD250", dist_dod250_settings, G_N_ELEMENTS(dist_dod250_settings)},
    {DIST_TYPE_REDLINE, "Redline", dist_redline_settings, G_N_ELEMENTS(dist_redline_settings)},
    {DIST_TYPE_AMPDRIVR, "Amp Driver", dist_ampdrivr_settings, G_N_ELEMENTS(dist_ampdrivr_settings)},
    {DIST_TYPE_OC_DRIVE, "OC Drive", dist_oc_drive_settings, G_N_ELEMENTS(dist_oc_drive_settings)},
    {DIST_TYPE_RODENT, "Rodent", dist_rodent_settings, G_N_ELEMENTS(dist_rodent_settings)},
    {DIST_TYPE_MX, "MX Dist", dist_mx_settings, G_N_ELEMENTS(dist_mx_settings)},
    {DIST_TYPE_DS, "DS Dist", dist_ds_settings, G_N_ELEMENTS(dist_ds_settings)},
    {DIST_TYPE_GRUNGE, "Grunge", dist_grunge_settings, G_N_ELEMENTS(dist_grunge_settings)},
    {DIST_TYPE_ZONE, "Zone", dist_zone_settings, G_N_ELEMENTS(dist_zone_settings)},
    {DIST_TYPE_DEATH, "Death", dist_death_settings, G_N_ELEMENTS(dist_death_settings)},
    {DIST_TYPE_GONK, "Gonk", dist_gonk_settings, G_N_ELEMENTS(dist_gonk_settings)},
    {DIST_TYPE_8TAVIA, "8tavia", dist_8tavia_settings, G_N_ELEMENTS(dist_8tavia_settings)},
    {DIST_TYPE_FUZZLATOR, "Fuzzlator", dist_fuzzlator_settings, G_N_ELEMENTS(dist_fuzzlator_settings)},
    {DIST_TYPE_CLASSIC_FUZZ, "Classic Fuzz", dist_classic_fuzz_settings, G_N_ELEMENTS(dist_classic_fuzz_settings)},
    {DIST_TYPE_FUZZY, "Fuzzy", dist_fuzzy_settings, G_N_ELEMENTS(dist_fuzzy_settings)},
    {DIST_TYPE_MP, "Big Pi", dist_mp_settings, G_N_ELEMENTS(dist_mp_settings)},
};

static EffectGroup gnx4_dist_group[] = {
    {DIST_TYPE_SCREAMER, "Screamer", dist_screamer_settings, G_N_ELEMENTS(dist_screamer_settings)},
    {DIST_TYPE_RODENT, "Rodent", dist_rodent_settings, G_N_ELEMENTS(dist_rodent_settings)},
    {DIST_TYPE_DS, "DS Dist", dist_ds_settings, G_N_ELEMENTS(dist_ds_settings)},
    {DIST_TYPE_DOD250, "DOD250", dist_dod250_settings, G_N_ELEMENTS(dist_dod250_settings)},
    {DIST_TYPE_MP, "Big MP", dist_mp_settings, G_N_ELEMENTS(dist_mp_settings)},
    {DIST_TYPE_GUYOD, "Guy OD", dist_guyod_settings, G_N_ELEMENTS(dist_guyod_settings)},
    {DIST_TYPE_SPARKDRIVE, "Sparkdrive", dist_sparkdrive_settings, G_N_ELEMENTS(dist_sparkdrive_settings)},
    {DIST_TYPE_GRUNGE, "Grunge", dist_grunge_settings, G_N_ELEMENTS(dist_grunge_settings)},
    {DIST_TYPE_FUZZY, "Fuzzy", dist_fuzzy_settings, G_N_ELEMENTS(dist_fuzzy_settings)},
    {DIST_TYPE_ZONE, "Zone", dist_zone_settings, G_N_ELEMENTS(dist_zone_settings)},
};

static EffectGroup gnx3k_dist_group[] = {
    {DIST_TYPE_SCREAMER, "Screamer", dist_screamer_settings, G_N_ELEMENTS(dist_screamer_settings)},
    {DIST_TYPE_RODENT, "Rodent", dist_rodent_settings, G_N_ELEMENTS(dist_rodent_settings)},
    {DIST_TYPE_DS, "DS", dist_ds_settings, G_N_ELEMENTS(dist_ds_settings)},
    {DIST_TYPE_DOD250, "DOD250", dist_dod250_settings, G_N_ELEMENTS(dist_dod250_settings)},
    {DIST_TYPE_MP, "Big MP", dist_mp_settings, G_N_ELEMENTS(dist_mp_settings)},
    {DIST_TYPE_GUYOD, "Guy OD", dist_guyod_settings, G_N_ELEMENTS(dist_guyod_settings)},
    {DIST_TYPE_SPARKDRIVE, "Sparkdrive", dist_sparkdrive_settings, G_N_ELEMENTS(dist_sparkdrive_settings)},
    {DIST_TYPE_GRUNGE, "Grunge", dist_grunge_settings, G_N_ELEMENTS(dist_grunge_settings)},
    {DIST_TYPE_FUZZY, "Fuzzy", dist_fuzzy_settings, G_N_ELEMENTS(dist_fuzzy_settings)},
    {DIST_TYPE_ZONE, "Zone", dist_zone_settings, G_N_ELEMENTS(dist_zone_settings)},
    {DIST_TYPE_8TAVIA, "8tavia", dist_8tavia_settings, G_N_ELEMENTS(dist_8tavia_settings)},
};

static EffectGroup gnx3k_noisegate_group[] = {
    {NOISEGATE_GATE, "Silencer", noisegate_silencer_settings, G_N_ELEMENTS(noisegate_silencer_settings)},
    {NOISEGATE_SWELL, "Pluck", noisegate_pluck_settings, G_N_ELEMENTS(noisegate_pluck_settings)},
};

static EffectGroup noisegate_group[] = {
    {NOISEGATE_GATE, "Gate", noisegate_gate_settings, G_N_ELEMENTS(noisegate_gate_settings)},
    {NOISEGATE_SWELL, "Swell", noisegate_swell_settings, G_N_ELEMENTS(noisegate_swell_settings)},
};

static EffectGroup gnx4_chorusfx_group[] = {
    {GNX3K_MOD_TYPE_CHORUS, "Chorus", gnx3k_chorus_settings, G_N_ELEMENTS(gnx3k_chorus_settings)},
    {GNX3K_MOD_TYPE_FLANGER, "Flanger", gnx3k_flanger_settings, G_N_ELEMENTS(gnx3k_flanger_settings)},
    {GNX3K_MOD_TYPE_PHASER, "Phaser", gnx3k_phaser_settings, G_N_ELEMENTS(gnx3k_phaser_settings)},
    {GNX3K_MOD_TYPE_TRIGFLANGER, "Triggered Flanger", gnx3k_trigflanger_settings, G_N_ELEMENTS(gnx3k_trigflanger_settings)},
    {GNX3K_MOD_TYPE_TRIGPHASER, "Triggered Phaser", gnx3k_trigphaser_settings, G_N_ELEMENTS(gnx3k_trigphaser_settings)},
    {GNX3K_MOD_TYPE_TREMOLO, "Tremolo", chorusfx_tremolo_settings, G_N_ELEMENTS(chorusfx_tremolo_settings)},
    {GNX3K_MOD_TYPE_PANNER, "Panner", chorusfx_panner_settings, G_N_ELEMENTS(chorusfx_panner_settings)},
    {GNX3K_MOD_TYPE_VIBRATO, "Vibrato", gnx3k_vibrato_settings, G_N_ELEMENTS(gnx3k_vibrato_settings)},
    {GNX3K_MOD_TYPE_ROTARY, "Rotary", gnx3k_rotary_settings, G_N_ELEMENTS(gnx3k_rotary_settings)},
    {GNX3K_MOD_TYPE_AUTOYA, "Auto Ya", gnx3k_autoya_settings, G_N_ELEMENTS(gnx3k_autoya_settings)},
    {GNX3K_MOD_TYPE_YAYA, "Ya Ya", gnx3k_yaya_settings, G_N_ELEMENTS(gnx3k_yaya_settings)},
    {GNX3K_MOD_TYPE_SYNTHTALK, "Synthtalk", gnx3k_synthtalk_settings, G_N_ELEMENTS(gnx3k_synthtalk_settings)},
    {GNX3K_MOD_TYPE_ENVELOPE, "Envelope", gnx3k_envelope_settings, G_N_ELEMENTS(gnx3k_envelope_settings)},
    {GNX3K_MOD_TYPE_DETUNE, "Detune", gnx3k_mod_detune_settings, G_N_ELEMENTS(gnx3k_mod_detune_settings)},
    {GNX3K_MOD_TYPE_PITCH, "Pitch", gnx3k_mod_pitch_settings, G_N_ELEMENTS(gnx3k_mod_pitch_settings)},
};

static EffectGroup gnx3k_chorusfx_group[] = {
    {GNX3K_MOD_TYPE_CHORUS, "Chorus", gnx3k_chorus_settings, G_N_ELEMENTS(gnx3k_chorus_settings)},
    {GNX3K_MOD_TYPE_FLANGER, "Flanger", gnx3k_flanger_settings, G_N_ELEMENTS(gnx3k_flanger_settings)},
    {GNX3K_MOD_TYPE_PHASER, "Phaser", gnx3k_phaser_settings, G_N_ELEMENTS(gnx3k_phaser_settings)},
    {GNX3K_MOD_TYPE_TRIGFLANGER, "Triggered Flanger", gnx3k_trigflanger_settings, G_N_ELEMENTS(gnx3k_trigflanger_settings)},
    {GNX3K_MOD_TYPE_TRIGPHASER, "Triggered Phaser", gnx3k_trigphaser_settings, G_N_ELEMENTS(gnx3k_trigphaser_settings)},
    {GNX3K_MOD_TYPE_UNOVIBE, "Unovibe", gnx3k_unovibe_settings, G_N_ELEMENTS(gnx3k_unovibe_settings)},
    {GNX3K_MOD_TYPE_TREMOLO, "Tremolo", chorusfx_tremolo_settings, G_N_ELEMENTS(chorusfx_tremolo_settings)},
    {GNX3K_MOD_TYPE_PANNER, "Panner", chorusfx_panner_settings, G_N_ELEMENTS(chorusfx_panner_settings)},
    {GNX3K_MOD_TYPE_VIBRATO, "Vibrato", gnx3k_vibrato_settings, G_N_ELEMENTS(gnx3k_vibrato_settings)},
    {GNX3K_MOD_TYPE_ROTARY, "Rotary", gnx3k_rotary_settings, G_N_ELEMENTS(gnx3k_rotary_settings)},
    {GNX3K_MOD_TYPE_AUTOYA, "Auto Ya", gnx3k_autoya_settings, G_N_ELEMENTS(gnx3k_autoya_settings)},
    {GNX3K_MOD_TYPE_YAYA, "Ya Ya", gnx3k_yaya_settings, G_N_ELEMENTS(gnx3k_yaya_settings)},
    {GNX3K_MOD_TYPE_SYNTHTALK, "Synthtalk", gnx3k_synthtalk_settings, G_N_ELEMENTS(gnx3k_synthtalk_settings)},
    {GNX3K_MOD_TYPE_ENVELOPE, "Envelope", gnx3k_envelope_settings, G_N_ELEMENTS(gnx3k_envelope_settings)},
    {GNX3K_MOD_TYPE_DETUNE, "Detune", gnx3k_mod_detune_settings, G_N_ELEMENTS(gnx3k_mod_detune_settings)},
    {GNX3K_MOD_TYPE_PITCH, "Pitch", gnx3k_mod_pitch_settings, G_N_ELEMENTS(gnx3k_mod_pitch_settings)},
};

static EffectGroup rp155_chorusfx_group[] = {
    {CHORUS_TYPE_CE, "CE Chorus", chorusfx_ce_settings, G_N_ELEMENTS(chorusfx_ce_settings)},
    {CHORUS_TYPE_DUAL, "Dual Chorus", chorusfx_dual_settings, G_N_ELEMENTS(chorusfx_dual_settings)},
    {CHORUS_TYPE_MULTI, "Multi Chorus", chorusfx_multi_settings, G_N_ELEMENTS(chorusfx_multi_settings)},
    {CHORUS_TYPE_FLANGER, "Flanger", chorusfx_flanger_settings, G_N_ELEMENTS(chorusfx_flanger_settings)},
    {CHORUS_TYPE_MXR_FLANGER, "MXR Flanger", chorusfx_mxr_flanger_settings, G_N_ELEMENTS(chorusfx_mxr_flanger_settings)},
    {CHORUS_TYPE_PHASER, "Phaser", chorusfx_phaser_settings, G_N_ELEMENTS(chorusfx_phaser_settings)},
    {CHORUS_TYPE_VIBRATO, "Vibrato", chorusfx_vibrato_settings, G_N_ELEMENTS(chorusfx_vibrato_settings)},
    {CHORUS_TYPE_ROTARY, "Rotary", chorusfx_rotary_settings, G_N_ELEMENTS(chorusfx_rotary_settings)},
    {CHORUS_TYPE_TREMOLO, "Tremolo", chorusfx_tremolo_settings, G_N_ELEMENTS(chorusfx_tremolo_settings)},
    {CHORUS_TYPE_PANNER, "Panner", chorusfx_panner_settings, G_N_ELEMENTS(chorusfx_panner_settings)},
    {CHORUS_TYPE_ENVELOPE, "Envelope", chorusfx_envelope_settings, G_N_ELEMENTS(chorusfx_envelope_settings)},
    {CHORUS_TYPE_AUTOYA, "AutoYa", chorusfx_autoya_settings, G_N_ELEMENTS(chorusfx_autoya_settings)},
    {CHORUS_TYPE_STEP_FILTER, "Step Filter", chorusfx_step_filter_settings, G_N_ELEMENTS(chorusfx_step_filter_settings)},
    {CHORUS_TYPE_WHAMMY, "Whammy", chorusfx_whammy_settings, G_N_ELEMENTS(chorusfx_whammy_settings)},
    {CHORUS_TYPE_PITCH_SHIFT, "Pitch Shift", chorusfx_pitch_shift_settings, G_N_ELEMENTS(chorusfx_pitch_shift_settings)},
    {CHORUS_TYPE_DETUNE, "Detune", chorusfx_detune_settings, G_N_ELEMENTS(chorusfx_detune_settings)},
    {CHORUS_TYPE_IPS, "Harmony Pitch", chorusfx_ips_settings, G_N_ELEMENTS(chorusfx_ips_settings)},
};

static EffectGroup rp250_chorusfx_group[] = {
    {CHORUS_TYPE_CE, "CE Chorus", chorusfx_ce_settings, G_N_ELEMENTS(chorusfx_ce_settings)},
    {CHORUS_TYPE_DUAL, "Dual Chorus", chorusfx_dual_settings, G_N_ELEMENTS(chorusfx_dual_settings)},
    {CHORUS_TYPE_MULTI, "Multi Chorus", chorusfx_multi_settings, G_N_ELEMENTS(chorusfx_multi_settings)},
    {CHORUS_TYPE_FLANGER, "Flanger", chorusfx_flanger_settings, G_N_ELEMENTS(chorusfx_flanger_settings)},
    {CHORUS_TYPE_MXR_FLANGER, "MXR FLANGER", chorusfx_mxr_flanger_settings, G_N_ELEMENTS(chorusfx_mxr_flanger_settings)},
    {CHORUS_TYPE_PHASER, "Phaser", chorusfx_phaser_settings, G_N_ELEMENTS(chorusfx_phaser_settings)},
    {CHORUS_TYPE_VIBRATO, "Vibrato", chorusfx_vibrato_settings, G_N_ELEMENTS(chorusfx_vibrato_settings)},
    {CHORUS_TYPE_ROTARY, "Rotary", chorusfx_rotary_settings, G_N_ELEMENTS(chorusfx_rotary_settings)},
    {CHORUS_TYPE_VIBROPAN, "Vibropan", chorusfx_vibropan_settings, G_N_ELEMENTS(chorusfx_vibropan_settings)},
    {CHORUS_TYPE_TREMOLO, "Tremolo", chorusfx_tremolo_settings, G_N_ELEMENTS(chorusfx_tremolo_settings)},
    {CHORUS_TYPE_PANNER, "Panner", chorusfx_panner_settings, G_N_ELEMENTS(chorusfx_panner_settings)},
    {CHORUS_TYPE_ENVELOPE, "Envelope", chorusfx_envelope_settings, G_N_ELEMENTS(chorusfx_envelope_settings)},
    {CHORUS_TYPE_AUTOYA, "AutoYa", chorusfx_autoya_settings, G_N_ELEMENTS(chorusfx_autoya_settings)},
    {CHORUS_TYPE_YAYA, "YaYa", chorusfx_yaya_settings, G_N_ELEMENTS(chorusfx_yaya_settings)},
    {CHORUS_TYPE_STEP_FILTER, "Step Filter", chorusfx_step_filter_settings, G_N_ELEMENTS(chorusfx_step_filter_settings)},
    {CHORUS_TYPE_WHAMMY, "Whammy", chorusfx_whammy_settings, G_N_ELEMENTS(chorusfx_whammy_settings)},
    {CHORUS_TYPE_PITCH_SHIFT, "Pitch Shift", chorusfx_pitch_shift_settings, G_N_ELEMENTS(chorusfx_pitch_shift_settings)},
    {CHORUS_TYPE_DETUNE, "Detune", chorusfx_detune_settings, G_N_ELEMENTS(chorusfx_detune_settings)},
    {CHORUS_TYPE_IPS, "IPS", chorusfx_ips_settings, G_N_ELEMENTS(chorusfx_ips_settings)},
};

/* same as rp250, with IPS renamed to Harmony Pitch */
static EffectGroup rp255_chorusfx_group[] = {
    {CHORUS_TYPE_CE, "CE Chorus", chorusfx_ce_settings, G_N_ELEMENTS(chorusfx_ce_settings)},
    {CHORUS_TYPE_DUAL, "Dual Chorus", chorusfx_dual_settings, G_N_ELEMENTS(chorusfx_dual_settings)},
    {CHORUS_TYPE_MULTI, "Multi Chorus", chorusfx_multi_settings, G_N_ELEMENTS(chorusfx_multi_settings)},
    {CHORUS_TYPE_FLANGER, "Flanger", chorusfx_flanger_settings, G_N_ELEMENTS(chorusfx_flanger_settings)},
    {CHORUS_TYPE_MXR_FLANGER, "MXR FLANGER", chorusfx_mxr_flanger_settings, G_N_ELEMENTS(chorusfx_mxr_flanger_settings)},
    {CHORUS_TYPE_PHASER, "Phaser", chorusfx_phaser_settings, G_N_ELEMENTS(chorusfx_phaser_settings)},
    {CHORUS_TYPE_VIBRATO, "Vibrato", chorusfx_vibrato_settings, G_N_ELEMENTS(chorusfx_vibrato_settings)},
    {CHORUS_TYPE_ROTARY, "Rotary", chorusfx_rotary_settings, G_N_ELEMENTS(chorusfx_rotary_settings)},
    {CHORUS_TYPE_VIBROPAN, "Vibropan", chorusfx_vibropan_settings, G_N_ELEMENTS(chorusfx_vibropan_settings)},
    {CHORUS_TYPE_TREMOLO, "Tremolo", chorusfx_tremolo_settings, G_N_ELEMENTS(chorusfx_tremolo_settings)},
    {CHORUS_TYPE_PANNER, "Panner", chorusfx_panner_settings, G_N_ELEMENTS(chorusfx_panner_settings)},
    {CHORUS_TYPE_ENVELOPE, "Envelope", chorusfx_envelope_settings, G_N_ELEMENTS(chorusfx_envelope_settings)},
    {CHORUS_TYPE_AUTOYA, "AutoYa", chorusfx_autoya_settings, G_N_ELEMENTS(chorusfx_autoya_settings)},
    {CHORUS_TYPE_YAYA, "YaYa", chorusfx_yaya_settings, G_N_ELEMENTS(chorusfx_yaya_settings)},
    {CHORUS_TYPE_STEP_FILTER, "Step Filter", chorusfx_step_filter_settings, G_N_ELEMENTS(chorusfx_step_filter_settings)},
    {CHORUS_TYPE_WHAMMY, "Whammy", chorusfx_whammy_settings, G_N_ELEMENTS(chorusfx_whammy_settings)},
    {CHORUS_TYPE_PITCH_SHIFT, "Pitch Shift", chorusfx_pitch_shift_settings, G_N_ELEMENTS(chorusfx_pitch_shift_settings)},
    {CHORUS_TYPE_DETUNE, "Detune", chorusfx_detune_settings, G_N_ELEMENTS(chorusfx_detune_settings)},
    {CHORUS_TYPE_IPS, "Harmony Pitch", chorusfx_ips_settings, G_N_ELEMENTS(chorusfx_ips_settings)},
};

static EffectGroup rp355_chorusfx_group[] = {
    {CHORUS_TYPE_CE, "CE Chorus", chorusfx_ce_settings, G_N_ELEMENTS(chorusfx_ce_settings)},
    {CHORUS_TYPE_TC, "TC Chorus", chorusfx_tc_settings, G_N_ELEMENTS(chorusfx_tc_settings)},
    {CHORUS_TYPE_DUAL, "Dual Chorus", chorusfx_dual_settings, G_N_ELEMENTS(chorusfx_dual_settings)},
    {CHORUS_TYPE_MULTI, "Multi Chorus", chorusfx_multi_settings, G_N_ELEMENTS(chorusfx_multi_settings)},
    {CHORUS_TYPE_FLANGER, "Flanger", chorusfx_flanger_settings, G_N_ELEMENTS(chorusfx_flanger_settings)},
    {CHORUS_TYPE_TRIGGERED_FLANGER, "Triggered Flanger", chorusfx_trig_flanger_settings, G_N_ELEMENTS(chorusfx_trig_flanger_settings)},
    {CHORUS_TYPE_MXR_FLANGER, "MXR FLANGER", chorusfx_mxr_flanger_settings, G_N_ELEMENTS(chorusfx_mxr_flanger_settings)},
    {CHORUS_TYPE_EH_FLANGER, "EH Flanger", chorusfx_eh_flanger_settings, G_N_ELEMENTS(chorusfx_eh_flanger_settings)},
    {CHORUS_TYPE_PHASER, "Phaser", chorusfx_phaser_settings, G_N_ELEMENTS(chorusfx_phaser_settings)},
    {CHORUS_TYPE_TRIGGERED_PHASER, "Triggered Phaser", chorusfx_trig_phaser_settings, G_N_ELEMENTS(chorusfx_trig_phaser_settings)},
    {CHORUS_TYPE_MX_PHASER, "MX Phaser", chorusfx_mx_phaser_settings, G_N_ELEMENTS(chorusfx_mx_phaser_settings)},
    {CHORUS_TYPE_EH_PHASER, "EH Phaser", chorusfx_eh_phaser_settings, G_N_ELEMENTS(chorusfx_eh_phaser_settings)},
    {CHORUS_TYPE_VIBRATO, "Vibrato", chorusfx_vibrato_settings, G_N_ELEMENTS(chorusfx_vibrato_settings)},
    {CHORUS_TYPE_ROTARY, "Rotary", chorusfx_rotary_settings, G_N_ELEMENTS(chorusfx_rotary_settings)},
    {CHORUS_TYPE_VIBROPAN, "Vibropan", chorusfx_vibropan_settings, G_N_ELEMENTS(chorusfx_vibropan_settings)},
    {CHORUS_TYPE_UNOVIBE, "Unovibe", chorusfx_unovibe_settings, G_N_ELEMENTS(chorusfx_unovibe_settings)},
    {CHORUS_TYPE_TREMOLO, "Tremolo", chorusfx_tremolo_settings, G_N_ELEMENTS(chorusfx_tremolo_settings)},
    {CHORUS_TYPE_OPTO_TREMOLO, "Opto Tremolo", chorusfx_trem_settings, G_N_ELEMENTS(chorusfx_trem_settings)},
    {CHORUS_TYPE_BIAS_TREMOLO, "Bias Tremolo", chorusfx_trem_settings, G_N_ELEMENTS(chorusfx_trem_settings)},
    {CHORUS_TYPE_PANNER, "Panner", chorusfx_panner_settings, G_N_ELEMENTS(chorusfx_panner_settings)},
    {CHORUS_TYPE_ENVELOPE, "Envelope", chorusfx_envelope_settings, G_N_ELEMENTS(chorusfx_envelope_settings)},
    {CHORUS_TYPE_FX25, "FX25", chorusfx_fx25_settings, G_N_ELEMENTS(chorusfx_fx25_settings)},
    {CHORUS_TYPE_AUTOYA, "AutoYa", chorusfx_autoya_settings, G_N_ELEMENTS(chorusfx_autoya_settings)},
    {CHORUS_TYPE_YAYA, "YaYa", chorusfx_yaya_settings, G_N_ELEMENTS(chorusfx_yaya_settings)},
    {CHORUS_TYPE_SYNTH_TALK, "Synth Talk", chorusfx_synth_talk_settings, G_N_ELEMENTS(chorusfx_synth_talk_settings)},
    {CHORUS_TYPE_STEP_FILTER, "Step Filter", chorusfx_step_filter_settings, G_N_ELEMENTS(chorusfx_step_filter_settings)},
    {CHORUS_TYPE_WHAMMY, "Whammy", chorusfx_whammy_settings, G_N_ELEMENTS(chorusfx_whammy_settings)},
    {CHORUS_TYPE_PITCH_SHIFT, "Pitch Shift", chorusfx_pitch_shift_settings, G_N_ELEMENTS(chorusfx_pitch_shift_settings)},
    {CHORUS_TYPE_DETUNE, "Detune", chorusfx_detune_settings, G_N_ELEMENTS(chorusfx_detune_settings)},
    {CHORUS_TYPE_IPS, "Harmony Pitch", chorusfx_ips_settings, G_N_ELEMENTS(chorusfx_ips_settings)},
    {CHORUS_TYPE_OCTAVER, "Octaver", chorusfx_octaver_settings, G_N_ELEMENTS(chorusfx_octaver_settings)},
};

/*
 * The combo boxes for the pedal assign and lfo groups are populated dynamically
 * from the RECEIVE_MODIFIER_LINKABLE_LIST. We request this message at startup
 * and are sent this message asynchronously whenever the selected chorus/FX
 * effect changes.
 */
static EffectGroup expression_pedal_assign_group[] = {
    { 0, "None", NULL, 0},
};

static EffectGroup rp355_lfo2_group[] = {
    { 0, NULL, lfo2_settings, G_N_ELEMENTS(lfo2_settings)},
    { 0, "None", NULL, 0},
};

static EffectGroup rp355_lfo1_group[] = {
    { 0, NULL, lfo1_settings, G_N_ELEMENTS(lfo1_settings)},
    { 0, "None", NULL, 0},
};

static EffectGroup rp500_chorusfx_group[] = {
    {CHORUS_TYPE_CE, "CE Chorus", chorusfx_ce_settings, G_N_ELEMENTS(chorusfx_ce_settings)},
    {CHORUS_TYPE_TC, "TC Chorus", chorusfx_tc_settings, G_N_ELEMENTS(chorusfx_tc_settings)},
    {CHORUS_TYPE_DUAL, "Dual Chorus", chorusfx_dual_settings, G_N_ELEMENTS(chorusfx_dual_settings)},
    {CHORUS_TYPE_GLISTEN, "Glisten Chorus", chorusfx_glisten_settings, G_N_ELEMENTS(chorusfx_glisten_settings)},
    {CHORUS_TYPE_MULTI, "Multi Chorus", chorusfx_multi_settings, G_N_ELEMENTS(chorusfx_multi_settings)},
    {CHORUS_TYPE_FLANGER, "Flanger", chorusfx_flanger_settings, G_N_ELEMENTS(chorusfx_flanger_settings)},
    {CHORUS_TYPE_TRIGGERED_FLANGER, "Triggered Flanger", chorusfx_trig_flanger_settings, G_N_ELEMENTS(chorusfx_trig_flanger_settings)},
    {CHORUS_TYPE_MXR_FLANGER, "MXR FLANGER", chorusfx_mxr_flanger_settings, G_N_ELEMENTS(chorusfx_mxr_flanger_settings)},
    {CHORUS_TYPE_EH_FLANGER, "EH Flanger", chorusfx_eh_flanger_settings, G_N_ELEMENTS(chorusfx_eh_flanger_settings)},
    {CHORUS_TYPE_AD_FLANGER, "AD Flanger", chorusfx_ad_flanger_settings, G_N_ELEMENTS(chorusfx_ad_flanger_settings)},
    {CHORUS_TYPE_PHASER, "Phaser", chorusfx_phaser_settings, G_N_ELEMENTS(chorusfx_phaser_settings)},
    {CHORUS_TYPE_TRIGGERED_PHASER, "Triggered Phaser", chorusfx_trig_phaser_settings, G_N_ELEMENTS(chorusfx_trig_phaser_settings)},
    {CHORUS_TYPE_MX_PHASER, "MX Phaser", chorusfx_mx_phaser_settings, G_N_ELEMENTS(chorusfx_mx_phaser_settings)},
    {CHORUS_TYPE_EH_PHASER, "EH Phaser", chorusfx_eh_phaser_settings, G_N_ELEMENTS(chorusfx_eh_phaser_settings)},
    {CHORUS_TYPE_VIBRATO, "Vibrato", chorusfx_vibrato_settings, G_N_ELEMENTS(chorusfx_vibrato_settings)},
    {CHORUS_TYPE_ROTARY, "Rotary", chorusfx_rotary_settings, G_N_ELEMENTS(chorusfx_rotary_settings)},
    {CHORUS_TYPE_VIBROPAN, "Vibropan", chorusfx_vibropan_settings, G_N_ELEMENTS(chorusfx_vibropan_settings)},
    {CHORUS_TYPE_UNOVIBE, "Unovibe", chorusfx_unovibe_settings, G_N_ELEMENTS(chorusfx_unovibe_settings)},
    {CHORUS_TYPE_TREMOLO, "Tremolo", chorusfx_tremolo_settings, G_N_ELEMENTS(chorusfx_tremolo_settings)},
    {CHORUS_TYPE_SCATTER_TREM, "ScatterTrem", chorusfx_trem_settings, G_N_ELEMENTS(chorusfx_trem_settings)},
    {CHORUS_TYPE_OPTO_TREMOLO, "Opto Tremolo", chorusfx_trem_settings, G_N_ELEMENTS(chorusfx_trem_settings)},
    {CHORUS_TYPE_BIAS_TREMOLO, "Bias Tremolo", chorusfx_trem_settings, G_N_ELEMENTS(chorusfx_trem_settings)},
    {CHORUS_TYPE_PANNER, "Panner", chorusfx_panner_settings, G_N_ELEMENTS(chorusfx_panner_settings)},
    {CHORUS_TYPE_ENVELOPE, "Envelope", chorusfx_envelope_settings, G_N_ELEMENTS(chorusfx_envelope_settings)},
    {CHORUS_TYPE_FX25, "FX25", chorusfx_fx25_settings, G_N_ELEMENTS(chorusfx_fx25_settings)},
    {CHORUS_TYPE_AUTOYA, "AutoYa", chorusfx_autoya_settings, G_N_ELEMENTS(chorusfx_autoya_settings)},
    {CHORUS_TYPE_YAYA, "YaYa", chorusfx_yaya_settings, G_N_ELEMENTS(chorusfx_yaya_settings)},
    {CHORUS_TYPE_SYNTH_TALK, "Synth Talk", chorusfx_synth_talk_settings, G_N_ELEMENTS(chorusfx_synth_talk_settings)},
    {CHORUS_TYPE_STEP_FILTER, "Step Filter", chorusfx_step_filter_settings, G_N_ELEMENTS(chorusfx_step_filter_settings)},
    {CHORUS_TYPE_SAMPLE_HOLD, "Sample/Hold", chorusfx_sample_hold_settings, G_N_ELEMENTS(chorusfx_sample_hold_settings)},
    {CHORUS_TYPE_WHAMMY, "Whammy", chorusfx_whammy_settings, G_N_ELEMENTS(chorusfx_whammy_settings)},
    {CHORUS_TYPE_PITCH_SHIFT, "Pitch", chorusfx_pitch_shift_settings, G_N_ELEMENTS(chorusfx_pitch_shift_settings)},
    {CHORUS_TYPE_DETUNE, "Detune", chorusfx_detune_settings, G_N_ELEMENTS(chorusfx_detune_settings)},
    {CHORUS_TYPE_IPS, "Harmony Pitch", chorusfx_ips_settings, G_N_ELEMENTS(chorusfx_ips_settings)},
    {CHORUS_TYPE_OCTAVER, "Octaver", chorusfx_octaver_settings, G_N_ELEMENTS(chorusfx_octaver_settings)},
};

static EffectGroup rp1000_chorusfx_group[] = {
    {CHORUS_TYPE_CE, "CE Chorus", chorusfx_ce_settings, G_N_ELEMENTS(chorusfx_ce_settings)},
    {CHORUS_TYPE_TC, "TC Chorus", chorusfx_tc_settings, G_N_ELEMENTS(chorusfx_tc_settings)},
    {CHORUS_TYPE_DUAL, "Dual Chorus", chorusfx_dual_settings, G_N_ELEMENTS(chorusfx_dual_settings)},
    {CHORUS_TYPE_GLISTEN, "Glisten Chorus", chorusfx_glisten_settings, G_N_ELEMENTS(chorusfx_glisten_settings)},
    {CHORUS_TYPE_MULTI, "Multi Chorus", chorusfx_multi_settings, G_N_ELEMENTS(chorusfx_multi_settings)},
    {CHORUS_TYPE_VOO_DOO, "Analog Chorus", chorusfx_voo_doo_settings, G_N_ELEMENTS(chorusfx_voo_doo_settings)},
    {CHORUS_TYPE_CLONE, "Small Clone", chorusfx_clone_settings, G_N_ELEMENTS(chorusfx_clone_settings)},
    {CHORUS_TYPE_FLANGER, "Flanger", chorusfx_flanger_settings, G_N_ELEMENTS(chorusfx_flanger_settings)},
    {CHORUS_TYPE_TRIGGERED_FLANGER, "Triggered Flanger", chorusfx_trig_flanger_settings, G_N_ELEMENTS(chorusfx_trig_flanger_settings)},
    {CHORUS_TYPE_FLTFLANGER, "Filter Flanger", chorusfx_fltflanger_settings, G_N_ELEMENTS(chorusfx_fltflanger_settings)},
    {CHORUS_TYPE_MXR_FLANGER, "MXR FLANGER", chorusfx_mxr_flanger_settings, G_N_ELEMENTS(chorusfx_mxr_flanger_settings)},
    {CHORUS_TYPE_EH_FLANGER, "EH Flanger", chorusfx_eh_flanger_settings, G_N_ELEMENTS(chorusfx_eh_flanger_settings)},
    {CHORUS_TYPE_AD_FLANGER, "AD Flanger", chorusfx_ad_flanger_settings, G_N_ELEMENTS(chorusfx_ad_flanger_settings)},
    {CHORUS_TYPE_PHASER, "Phaser", chorusfx_phaser_settings, G_N_ELEMENTS(chorusfx_phaser_settings)},
    {CHORUS_TYPE_TRIGGERED_PHASER, "Triggered Phaser", chorusfx_trig_phaser_settings, G_N_ELEMENTS(chorusfx_trig_phaser_settings)},
    {CHORUS_TYPE_MX_PHASER, "MX Phaser", chorusfx_mx_phaser_settings, G_N_ELEMENTS(chorusfx_mx_phaser_settings)},
    {CHORUS_TYPE_EH_PHASER, "EH Phaser", chorusfx_eh_phaser_settings, G_N_ELEMENTS(chorusfx_eh_phaser_settings)},
    {CHORUS_TYPE_VIBRATO, "Vibrato", chorusfx_vibrato_settings, G_N_ELEMENTS(chorusfx_vibrato_settings)},
    {CHORUS_TYPE_ROTARY, "Rotary", chorusfx_rotary_settings, G_N_ELEMENTS(chorusfx_rotary_settings)},
    {CHORUS_TYPE_VIBROPAN, "Vibropan", chorusfx_vibropan_settings, G_N_ELEMENTS(chorusfx_vibropan_settings)},
    {CHORUS_TYPE_UNOVIBE, "Unovibe", chorusfx_unovibe_settings, G_N_ELEMENTS(chorusfx_unovibe_settings)},
    {CHORUS_TYPE_TREMOLO, "Tremolo", chorusfx_tremolo_settings, G_N_ELEMENTS(chorusfx_tremolo_settings)},
    {CHORUS_TYPE_SCATTER_TREM, "ScatterTrem", chorusfx_trem_settings, G_N_ELEMENTS(chorusfx_trem_settings)},
    {CHORUS_TYPE_OPTO_TREMOLO, "Opto Tremolo", chorusfx_trem_settings, G_N_ELEMENTS(chorusfx_trem_settings)},
    {CHORUS_TYPE_BIAS_TREMOLO, "Bias Tremolo", chorusfx_trem_settings, G_N_ELEMENTS(chorusfx_trem_settings)},
    {CHORUS_TYPE_PANNER, "Panner", chorusfx_panner_settings, G_N_ELEMENTS(chorusfx_panner_settings)},
    {CHORUS_TYPE_ENVELOPE, "Envelope", chorusfx_envelope_settings, G_N_ELEMENTS(chorusfx_envelope_settings)},
    {CHORUS_TYPE_FX25, "FX25", chorusfx_fx25_settings, G_N_ELEMENTS(chorusfx_fx25_settings)},
    {CHORUS_TYPE_AUTOYA, "AutoYa", chorusfx_autoya_settings, G_N_ELEMENTS(chorusfx_autoya_settings)},
    {CHORUS_TYPE_YAYA, "YaYa", chorusfx_yaya_settings, G_N_ELEMENTS(chorusfx_yaya_settings)},
    {CHORUS_TYPE_SYNTH_TALK, "Synth Talk", chorusfx_synth_talk_settings, G_N_ELEMENTS(chorusfx_synth_talk_settings)},
    {CHORUS_TYPE_STEP_FILTER, "Step Filter", chorusfx_step_filter_settings, G_N_ELEMENTS(chorusfx_step_filter_settings)},
    {CHORUS_TYPE_SAMPLE_HOLD, "Sample/Hold", chorusfx_sample_hold_settings, G_N_ELEMENTS(chorusfx_sample_hold_settings)},
    {CHORUS_TYPE_WHAMMY, "Whammy", chorusfx_whammy_settings, G_N_ELEMENTS(chorusfx_whammy_settings)},
    {CHORUS_TYPE_PITCH_SHIFT, "Pitch", chorusfx_pitch_shift_settings, G_N_ELEMENTS(chorusfx_pitch_shift_settings)},
    {CHORUS_TYPE_DETUNE, "Detune", chorusfx_detune_settings, G_N_ELEMENTS(chorusfx_detune_settings)},
    {CHORUS_TYPE_IPS, "Harmony Pitch", chorusfx_ips_settings, G_N_ELEMENTS(chorusfx_ips_settings)},
    {CHORUS_TYPE_OCTAVER, "Octaver", chorusfx_octaver_settings, G_N_ELEMENTS(chorusfx_octaver_settings)},
};

static EffectGroup gnx3k_delay_group[] = {
    {DELAY_GNX3K_TYPE_MONO, "Mono", gnx3k_delay_settings, G_N_ELEMENTS(gnx3k_delay_settings)},
    {DELAY_GNX3K_TYPE_PINGPONG, "Ping-Pong", gnx3k_delay_settings, G_N_ELEMENTS(gnx3k_delay_settings)},
    {DELAY_GNX3K_TYPE_ANALOG, "Analog", gnx3k_delay_settings, G_N_ELEMENTS(gnx3k_delay_settings)},
    {DELAY_GNX3K_TYPE_ANAPONG, "Analog-Pong", gnx3k_delay_settings, G_N_ELEMENTS(gnx3k_delay_settings)},
    {DELAY_GNX3K_TYPE_SPREAD, "Spread", gnx3k_delay_spread_settings, G_N_ELEMENTS(gnx3k_delay_spread_settings)},
};

static EffectGroup rp250_delay_group[] = {
    {DELAY_TYPE_ANALOG, "Analog", delay_analog_settings, G_N_ELEMENTS(delay_analog_settings)},
    {DELAY_TYPE_DIGITAL, "Digital", delay_digital_settings, G_N_ELEMENTS(delay_digital_settings)},
    {DELAY_TYPE_MODULATED, "Modulated", delay_modulated_settings, G_N_ELEMENTS(delay_modulated_settings)},
    {DELAY_TYPE_PONG, "Pong", delay_pong_settings, G_N_ELEMENTS(delay_pong_settings)},
    {DELAY_TYPE_TAPE, "Tape", delay_tape_settings, G_N_ELEMENTS(delay_tape_settings)},
};

static EffectGroup rp355_delay_group[] = {
    {DELAY_TYPE_ANALOG, "Analog", delay_analog_settings, G_N_ELEMENTS(delay_analog_settings)},
    {DELAY_TYPE_DM, "DM Delay", delay_dm_settings, G_N_ELEMENTS(delay_dm_settings)},
    {DELAY_TYPE_DIGITAL, "Digital", delay_digital_settings, G_N_ELEMENTS(delay_digital_settings)},
    {DELAY_TYPE_MODULATED, "Modulated", delay_modulated_settings, G_N_ELEMENTS(delay_modulated_settings)},
    {DELAY_TYPE_PONG, "Pong", delay_pong_settings, G_N_ELEMENTS(delay_pong_settings)},
    {DELAY_TYPE_TAPE, "Tape", delay_tape_settings, G_N_ELEMENTS(delay_tape_settings)},
    {DELAY_TYPE_ECHOPLEX, "Echo Plex", delay_echoplex_settings, G_N_ELEMENTS(delay_echoplex_settings)},
};

static EffectGroup rp500_delay_group[] = {
    {DELAY_RP500_TYPE_DIGITAL, "Digital", rp500_delay_digital_settings, G_N_ELEMENTS(rp500_delay_digital_settings)},
    {DELAY_RP500_TYPE_ANALOG, "Analog", rp500_delay_analog_settings, G_N_ELEMENTS(rp500_delay_analog_settings)},
    {DELAY_RP500_TYPE_DM, "DM Delay", rp500_delay_dm_settings, G_N_ELEMENTS(rp500_delay_dm_settings)},
    {DELAY_RP500_TYPE_ECHOPLEX, "Echo Plex", rp500_delay_echoplex_settings, G_N_ELEMENTS(rp500_delay_echoplex_settings)},
    {DELAY_RP500_TYPE_MODULATED, "Modulated", rp500_delay_modulated_settings, G_N_ELEMENTS(rp500_delay_modulated_settings)},
    {DELAY_RP500_TYPE_PONG, "Pong", rp500_delay_pong_settings, G_N_ELEMENTS(rp500_delay_pong_settings)},
    {DELAY_RP500_TYPE_REVERSE, "Reverse", rp500_delay_reverse_settings, G_N_ELEMENTS(rp500_delay_reverse_settings)},
    {DELAY_RP500_TYPE_TAPE, "Tape", rp500_delay_tape_settings, G_N_ELEMENTS(rp500_delay_tape_settings)},
};

static EffectGroup rp1000_delay_group[] = {
    {DELAY_RP500_TYPE_DIGITAL, "Digital", rp500_delay_digital_settings, G_N_ELEMENTS(rp500_delay_digital_settings)},
    {DELAY_RP500_TYPE_ANALOG, "Analog", rp500_delay_analog_settings, G_N_ELEMENTS(rp500_delay_analog_settings)},
    {DELAY_RP500_TYPE_DM, "DM Delay", rp500_delay_dm_settings, G_N_ELEMENTS(rp500_delay_dm_settings)},
    {DELAY_RP500_TYPE_ECHOPLEX, "Echo Plex", rp500_delay_echoplex_settings, G_N_ELEMENTS(rp500_delay_echoplex_settings)},
    {DELAY_RP500_TYPE_MODULATED, "Modulated", rp500_delay_modulated_settings, G_N_ELEMENTS(rp500_delay_modulated_settings)},
    {DELAY_RP500_TYPE_PONG, "Pong", rp500_delay_pong_settings, G_N_ELEMENTS(rp500_delay_pong_settings)},
    {DELAY_RP500_TYPE_REVERSE, "Reverse", rp500_delay_reverse_settings, G_N_ELEMENTS(rp500_delay_reverse_settings)},
    {DELAY_RP500_TYPE_TAPE, "Tape", rp500_delay_tape_settings, G_N_ELEMENTS(rp500_delay_tape_settings)},
    {DELAY_RP1000_TYPE_LO_FI, "Lo Fidelity", rp1000_delay_lo_fi_settings, G_N_ELEMENTS(rp1000_delay_lo_fi_settings)},
    {DELAY_RP1000_TYPE_2_TAP, "2-tap", rp1000_delay_2_tap_settings, G_N_ELEMENTS(rp1000_delay_2_tap_settings)},
};

static EffectGroup gnx3k_reverb_group[] = {
    {GNX3K_REVERB_TYPE_STUDIO, "Studio", gnx3k_reverb_settings, G_N_ELEMENTS(gnx3k_reverb_settings)},
    {GNX3K_REVERB_TYPE_ROOM, "Room", gnx3k_reverb_settings, G_N_ELEMENTS(gnx3k_reverb_settings)},
    {GNX3K_REVERB_TYPE_CLUB, "Club", gnx3k_reverb_settings, G_N_ELEMENTS(gnx3k_reverb_settings)},
    {GNX3K_REVERB_TYPE_PLATE, "Plate", gnx3k_reverb_settings, G_N_ELEMENTS(gnx3k_reverb_settings)},
    {GNX3K_REVERB_TYPE_HALL, "Hall", gnx3k_reverb_settings, G_N_ELEMENTS(gnx3k_reverb_settings)},
    {GNX3K_REVERB_TYPE_AMPHITHEATER, "Amphitheater", gnx3k_reverb_settings, G_N_ELEMENTS(gnx3k_reverb_settings)},
    {GNX3K_REVERB_TYPE_CHURCH, "Church", gnx3k_reverb_settings, G_N_ELEMENTS(gnx3k_reverb_settings)},
    {GNX3K_REVERB_TYPE_GARAGE, "Garage", gnx3k_reverb_settings, G_N_ELEMENTS(gnx3k_reverb_settings)},
    {GNX3K_REVERB_TYPE_ARENA, "Arena", gnx3k_reverb_settings, G_N_ELEMENTS(gnx3k_reverb_settings)},
    {GNX3K_REVERB_TYPE_SPRING, "Spring", gnx3k_reverb_settings, G_N_ELEMENTS(gnx3k_reverb_settings)},
};

static EffectGroup reverb_group[] = {
    {REVERB_TYPE_TWIN, "Twin", reverb_twin_settings, G_N_ELEMENTS(reverb_twin_settings)},
    {REVERB_TYPE_LEX_AMBIENCE, "Lexicon ambience", reverb_lex_settings, G_N_ELEMENTS(reverb_lex_settings)},
    {REVERB_TYPE_LEX_STUDIO, "Lexicon studio", reverb_lex_settings, G_N_ELEMENTS(reverb_lex_settings)},
    {REVERB_TYPE_LEX_ROOM, "Lexicon room", reverb_lex_settings, G_N_ELEMENTS(reverb_lex_settings)},
    {REVERB_TYPE_LEX_HALL, "Lexicon hall", reverb_lex_settings, G_N_ELEMENTS(reverb_lex_settings)},
    {REVERB_TYPE_EMT240_PLATE, "EMT240 Plate", reverb_lex_settings, G_N_ELEMENTS(reverb_lex_settings)},
};

static EffectGroup rp150_amp_group[] = {
    {AMP_TYPE_TWEED_CHAMP, "Tweed Champ", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_TWEED_DELUXE, "Tweed Deluxe", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_TWEED_BASSMAN, "Tweed Bassman", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BLACKFACE_TWIN, "Blackface Twin", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_SUPER_LEAD_PLEXI, "Super Lead Plexi", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_MASTER_VOLUME, "Master Volume", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_JCM800, "JCM800", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_AC30TB, "AC30TB", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_HIWATT_100, "Hiwatt 100", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BOOGIE_MARK_II, "Boogie Mark II", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_DUAL_RECTIFIER, "Dual Rectifier", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_MATCHLESS_HC30, "Matchless HC30", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_SOLO, "Solo", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_METAL, "Metal", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BRIGHT, "Bright", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_DIGITECH_CLEAN, "Clean", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_ACOUSTIC, "Acoustic", rp250_amp_settings2, G_N_ELEMENTS(rp250_amp_settings2)},
    {AMP_TYPE_DIRECT, "Direct", rp250_amp_settings2, G_N_ELEMENTS(rp250_amp_settings2)},
};


static EffectGroup rp155_amp_group[] = {
    {AMP_TYPE_TWEED_CHAMP, "Tweed Champ", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_TWEED_DELUXE, "Tweed Deluxe", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_TWEED_BASSMAN, "Tweed Bassman", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BLACKFACE_TWIN, "Blackface Twin", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BLACKFACE_DELUXE, "Blackface Deluxe", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_SUPER_LEAD_PLEXI, "Super Lead Plexi", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_MASTER_VOLUME, "Master Volume", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_JCM800, "JCM800", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_JCM900, "JCM900", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_AC15, "AC15", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_AC30TB, "AC30TB", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_HIWATT_100, "Hiwatt 100", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BOOGIE_MARK_II, "Boogie Mark II", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_DUAL_RECTIFIER, "Dual Rectifier", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_MATCHLESS_HC30, "Matchless HC30", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_SOLO, "Solo", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_METAL, "Metal", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_HIGH_GAIN, "High Gain", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BRIGHT, "Bright", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_DIGITECH_CLEAN, "Clean", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_ACOUSTIC, "Acoustic", rp250_amp_settings2, G_N_ELEMENTS(rp250_amp_settings2)},
    {AMP_TYPE_DIRECT, "Direct", rp250_amp_settings2, G_N_ELEMENTS(rp250_amp_settings2)},
};

static EffectGroup rp250_amp_group[] = {
    {AMP_TYPE_TWEED_CHAMP, "Tweed Champ", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_TWEED_DELUXE, "Tweed Deluxe", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_TWEED_BASSMAN, "Tweed Bassman", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BLACKFACE_TWIN, "Blackface Twin", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BLACKFACE_DELUXE, "Blackface Deluxe", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_SUPER_LEAD_PLEXI, "Super Lead Plexi", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_MASTER_VOLUME, "Master Volume", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_JCM800, "JCM800", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_JCM900, "JCM900", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_AC15, "AC15", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_AC30TB, "AC30TB", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_HIWATT_100, "Hiwatt 100", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BOOGIE_MARK_II, "Boogie Mark II", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_DUAL_RECTIFIER, "Dual Rectifier", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_MATCHLESS_HC30, "Matchless HC30", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_SOLO, "Solo", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_METAL, "Metal", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BRIGHT, "Bright", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_DIGITECH_CLEAN, "Clean", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_HIGH_GAIN, "High Gain", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_ACOUSTIC, "Acoustic", rp250_amp_settings2, G_N_ELEMENTS(rp250_amp_settings2)},
    {AMP_TYPE_DIRECT, "Direct", rp250_amp_settings2, G_N_ELEMENTS(rp250_amp_settings2)},
};

/* same as RP250, with added 45 JTM, JMPPNL and SOLDNO */
static EffectGroup rp255_amp_group[] = {
    {AMP_TYPE_TWEED_CHAMP, "Tweed Champ", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_TWEED_DELUXE, "Tweed Deluxe", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_TWEED_BASSMAN, "Tweed Bassman", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BLACKFACE_TWIN, "Blackface Twin", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BLACKFACE_DELUXE, "Blackface Deluxe", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_SUPER_LEAD_PLEXI, "Super Lead Plexi", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_PLEXI_JTM_45, "Plexi JTM-45", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_68_MARSHALL_JUMP, "Plexi Jump Panel", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_MASTER_VOLUME, "Master Volume", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_JCM800, "JCM800", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_JCM900, "JCM900", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_AC15, "AC15", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_AC30TB, "AC30TB", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_HIWATT_100, "Hiwatt 100", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BOOGIE_MARK_II, "Boogie Mark II", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_DUAL_RECTIFIER, "Dual Rectifier", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_MATCHLESS_HC30, "Matchless HC30", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_SOLDANO_100, "Soldano 100", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_SOLO, "Solo", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_METAL, "Metal", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_BRIGHT, "Bright", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_DIGITECH_CLEAN, "Clean", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_HIGH_GAIN, "High Gain", rp250_amp_settings, G_N_ELEMENTS(rp250_amp_settings)},
    {AMP_TYPE_ACOUSTIC, "Acoustic", rp250_amp_settings2, G_N_ELEMENTS(rp250_amp_settings2)},
    {AMP_TYPE_DIRECT, "Direct", rp250_amp_settings2, G_N_ELEMENTS(rp250_amp_settings2)},
};

static EffectGroup rp355_amp_select_group[] = {
    {AMP_CHANNEL_A, "A", NULL, -1},
    {AMP_CHANNEL_B, "B", NULL, -1},
};

static EffectGroup rp355_amp_group_A[] = {
    {AMP_TYPE_TWEED_CHAMP, "Tweed Champ", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_TWEED_DELUXE, "Tweed Deluxe", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_TWEED_BASSMAN, "Tweed Bassman", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_BLACKFACE_TWIN, "Blackface Twin", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_BLACKFACE_DELUXE, "Blackface Deluxe", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_PLEXI_JTM_45, "Plexi JTM-45", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_SUPER_LEAD_PLEXI, "Plexi Lead", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_68_MARSHALL_JUMP, "Plexi Jump Panel", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_MASTER_VOLUME, "Master Volume", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_JCM800, "JCM800", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_JCM900, "JCM900", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_AC15, "AC-15", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_AC30TB, "AC-30 TB", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_HIWATT_100, "Hiwatt 100", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_BOOGIE_MARK_II, "Boogie Mark IIC", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_DUAL_RECTIFIER, "Dual Rectifier", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_MATCHLESS_HC30, "Matchless HC30", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_SOLDANO_100, "Soldano 100", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_SOLO, "Solo", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_METAL, "Metal", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_BRIGHT, "Bright Clean", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_CHUNK, "Chunk", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_DIGITECH_CLEAN, "Clean Tube", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_HIGH_GAIN, "High Gain", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_GSP2101_CLEAN_TUBE, "GSP2101 Clean Tube", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_GSP2101_SAT_TUBE, "GSP2101 Sat Tube", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_MONSTER, "Monster", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_TWEEDFACE, "Tweedface", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_BLACKBASS, "Blackbass", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_STONER_ROCK, "Stoner Rock", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_DARK_METAL, "Dark Metal", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_BROWN_SOUND, "Brown Sound", rp355_amp_settings_A, G_N_ELEMENTS(rp355_amp_settings_A)},
    {AMP_TYPE_ACOUSTIC, "Dread Acoustic", rp355_amp_settings2_A, G_N_ELEMENTS(rp355_amp_settings2_A)},
    {AMP_TYPE_JUMBO_ACOUSTIC, "Jumbo Acoustic", rp355_amp_settings2_A, G_N_ELEMENTS(rp355_amp_settings2_A)},
    {AMP_TYPE_DIRECT, "Direct", rp355_amp_settings2_A, G_N_ELEMENTS(rp355_amp_settings2_A)},
};

static EffectGroup rp355_amp_group_B[] = {
    {AMP_TYPE_TWEED_CHAMP, "Tweed Champ", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_TWEED_DELUXE, "Tweed Deluxe", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_TWEED_BASSMAN, "Tweed Bassman", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_BLACKFACE_TWIN, "Blackface Twin", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_BLACKFACE_DELUXE, "Blackface Deluxe", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_PLEXI_JTM_45, "Plexi JTM-45", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_SUPER_LEAD_PLEXI, "Plexi Lead", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_68_MARSHALL_JUMP, "Plexi Jump Panel", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_MASTER_VOLUME, "Master Volume", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_JCM800, "JCM800", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_JCM900, "JCM900", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_AC15, "AC-15", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_AC30TB, "AC-30 TB", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_HIWATT_100, "Hiwatt 100", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_BOOGIE_MARK_II, "Boogie Mark IIC", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_DUAL_RECTIFIER, "Dual Rectifier", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_MATCHLESS_HC30, "Matchless HC30", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_SOLDANO_100, "Soldano 100", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_SOLO, "Solo", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_METAL, "Metal", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_BRIGHT, "Bright Clean", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_CHUNK, "Chunk", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_DIGITECH_CLEAN, "Clean Tube", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_HIGH_GAIN, "High Gain", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_GSP2101_CLEAN_TUBE, "GSP2101 Clean Tube", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_GSP2101_SAT_TUBE, "GSP2101 Sat Tube", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_MONSTER, "Monster", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_TWEEDFACE, "Tweedface", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_BLACKBASS, "Blackbass", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_STONER_ROCK, "Stoner Rock", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_DARK_METAL, "Dark Metal", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_BROWN_SOUND, "Brown Sound", rp355_amp_settings_B, G_N_ELEMENTS(rp355_amp_settings_B)},
    {AMP_TYPE_ACOUSTIC, "Dread Acoustic", rp355_amp_settings2_B, G_N_ELEMENTS(rp355_amp_settings2_B)},
    {AMP_TYPE_JUMBO_ACOUSTIC, "Jumbo Acoustic", rp355_amp_settings2_B, G_N_ELEMENTS(rp355_amp_settings2_B)},
    {AMP_TYPE_DIRECT, "Direct", rp355_amp_settings2_B, G_N_ELEMENTS(rp355_amp_settings2_B)},
};

static EffectGroup rp500_amp_group[] = {
    {AMP_TYPE_TWEED_CHAMP, "Tweed Champ", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_TWEED_DELUXE, "Tweed Deluxe", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_TWEED_BASSMAN, "Tweed Bassman", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BROWN_BASSMAN, "Brown Bassman", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BLACKFACE_TWIN, "Blackface Twin", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BLACKFACE_DELUXE, "Blackface Deluxe", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_PLEXI_JTM_45, "Plexi JTM-45", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SUPER_LEAD_PLEXI, "Plexi Lead", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_68_MARSHALL_JUMP, "Plexi Jump Panel", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_MASTER_VOLUME, "Master Volume", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_JCM800, "JCM800", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_JCM900, "JCM900", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_JCM2000, "JCM2000", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_AC15, "AC-15", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_AC30TB, "AC-30 TB", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_HIWATT_100, "Hiwatt 100", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BOOGIE_MARK_II, "Boogie Mark IIC", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BOOGIE_MARK_IV, "Boogie Mark IV", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_DUAL_RECTIFIER, "Dual Rectifier", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_TRIPLE_RECTIFIER, "Triple Rectifier", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_LEGACY_VL100, "Legacy VL-100", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_MATCHLESS_HC30, "Matchless HC30", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SOLDANO_100, "Soldano 100", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SUPERGROUP, "Supergroup", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_GA40, "GA-40", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_OR120, "OR-120", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_PV5150II, "PV 5150II", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_RG100, "RG100", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_JC120_JAZZ, "JC-120 Jazz", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SOLAR100, "Solar 100", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SOLO, "Solo", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_METAL, "Metal", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BRIGHT, "Bright Clean", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_CHUNK, "Chunk", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_DIGITECH_CLEAN, "Clean Tube", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_HIGH_GAIN, "High Gain", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BLUES, "Blues", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_FUZZ, "Fuzz", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SPANK, "Spank", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_GSP2101_CLEAN_TUBE, "GSP2101 Clean Tube", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_GSP2101_SAT_TUBE, "GSP2101 Sat Tube", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_CRUNCH, "Crunch", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_MONSTER, "Monster", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_TWEEDFACE, "Tweedface", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BLACKBASS, "Blackbass", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_STONER_ROCK, "Stoner Rock", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_DARK_METAL, "Dark Metal", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_TRANSISTOR, "Transistor", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BROWN_SOUND, "Brown Sound", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_MOSH, "Mosh", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_ACOUSTIC, "Dread Acoustic", rp500_amp_settings2, G_N_ELEMENTS(rp500_amp_settings2)},
    {AMP_TYPE_JUMBO_ACOUSTIC, "Jumbo Acoustic", rp500_amp_settings2, G_N_ELEMENTS(rp500_amp_settings2)},
    {AMP_TYPE_DIRECT, "Direct", rp500_amp_settings3, G_N_ELEMENTS(rp500_amp_settings3)},
};

static EffectGroup rp1000_amp_group[] = {
    {AMP_TYPE_TWEED_CHAMP, "Tweed Champ", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_TWEED_DELUXE, "Tweed Deluxe", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_TWEED_BASSMAN, "Tweed Bassman", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BROWN_BASSMAN, "Brown Bassman", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BLACKFACE_TWIN, "Blackface Twin", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BLACKFACE_DELUXE, "Blackface Deluxe", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_PLEXI_JTM_45, "Plexi JTM-45", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SUPER_LEAD_PLEXI, "Plexi Lead", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_68_MARSHALL_JUMP, "Plexi Jump Panel", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_MASTER_VOLUME, "Master Volume", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_JCM800, "JCM800", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_JCM900, "JCM900", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_JCM2000, "JCM2000", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_AC15, "AC-15", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_AC30TB, "AC-30 TB", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_HIWATT_100, "Hiwatt 100", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BOOGIE_MARK_II, "Boogie Mark IIC", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BOOGIE_MARK_IV, "Boogie Mark IV", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_DUAL_RECTIFIER, "Dual Rectifier", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_TRIPLE_RECTIFIER, "Triple Rectifier", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_22_CALIBR, ".22 Caliber", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_LEGACY_VL100, "Legacy VL-100", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_MATCHLESS_HC30, "Matchless HC30", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_CHIEF, "Matchless Chieftan", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SOLDANO_100, "Soldano 100", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SUPERGROUP, "Supergroup", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_GA40, "GA-40", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_OR120, "OR-120", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_PV5150II, "PV 5150II", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_RG100, "RG100", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_JC120_JAZZ, "JC-120 Jazz", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SOLAR100, "Solar 100", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SOLO, "Solo", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_METAL, "Metal", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BRIGHT, "Bright Clean", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_CHUNK, "Chunk", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_DIGITECH_CLEAN, "Clean Tube", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_HIGH_GAIN, "High Gain", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BLUES, "Blues", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_FUZZ, "Fuzz", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_SPANK, "Spank", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_GSP2101_CLEAN_TUBE, "GSP2101 Clean Tube", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_GSP2101_SAT_TUBE, "GSP2101 Sat Tube", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_CRUNCH, "Crunch", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_MONSTER, "Monster", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_TWEEDFACE, "Tweedface", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BLACKBASS, "Blackbass", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_STONER_ROCK, "Stoner Rock", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_DARK_METAL, "Dark Metal", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_TRANSISTOR, "Transistor", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_BROWN_SOUND, "Brown Sound", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_MOSH, "Mosh", rp500_amp_settings, G_N_ELEMENTS(rp500_amp_settings)},
    {AMP_TYPE_ACOUSTIC, "Dread Acoustic", rp500_amp_settings2, G_N_ELEMENTS(rp500_amp_settings2)},
    {AMP_TYPE_JUMBO_ACOUSTIC, "Jumbo Acoustic", rp500_amp_settings2, G_N_ELEMENTS(rp500_amp_settings2)},
    {AMP_TYPE_DIRECT, "Direct", rp500_amp_settings3, G_N_ELEMENTS(rp500_amp_settings3)},
};

static EffectGroup gnx3k_amp_group[] = {
    {AMP_TYPE_DIRECT, "Direct", NULL, -1},
    {AMP_TYPE_TWEED_CHAMP, "Tweed Champ", NULL, -1},
    {AMP_TYPE_TWEED_DELUXE, "Tweed Deluxe", NULL, -1},
    {AMP_TYPE_TWEED_BASSMAN, "Tweed Bassman", NULL, -1},
    {AMP_TYPE_BROWN_BASSMAN, "Brown Bassman", NULL, -1},
    {AMP_TYPE_BLACKFACE_TWIN, "Blackface Twin", NULL, -1},
    {AMP_TYPE_BLACKFACE_DELUXE, "Blackface Deluxe", NULL, -1},
    {AMP_TYPE_PLEXI_JTM_45, "Plexi JTM-45", NULL, -1},
    {AMP_TYPE_SUPER_LEAD_PLEXI, "Plexi Lead", NULL, -1},
    {AMP_TYPE_68_MARSHALL_JUMP, "Plexi Jump Panel", NULL, -1},
    {AMP_TYPE_MASTER_VOLUME, "Master Volume", NULL, -1},
    {AMP_TYPE_JCM800, "JCM800", NULL, -1},
    {AMP_TYPE_JCM900, "JCM900", NULL, -1},
    {AMP_TYPE_JCM2000, "JCM2000", NULL, -1},
    {AMP_TYPE_BOOGIE_MARK_II, "Boogie Mark II", NULL, -1},
    {AMP_TYPE_DUAL_RECTIFIER, "Dual Rectifier", NULL, -1},
    {AMP_TYPE_AC15, "AC-15", NULL, -1},
    {AMP_TYPE_AC30TB, "AC-30 TB", NULL, -1},
    {AMP_TYPE_HIWATT_100, "Hiwatt 100", NULL, -1},
    {AMP_TYPE_SOLO, "Solo", NULL, -1},
    {AMP_TYPE_MATCHLESS_HC30, "Matchless HC30", NULL, -1},
    {AMP_TYPE_LEGACY_VL100, "Legacy VL-100", NULL, -1},
    {AMP_TYPE_GSP2101_CLEAN_TUBE, "GSP2101 Clean Tube", NULL, -1},
    {AMP_TYPE_GSP2101_SAT_TUBE, "GSP2101 Sat Tube", NULL, -1},
    {AMP_TYPE_SPANK, "Spank", NULL, -1},
    {AMP_TYPE_METAL, "Metal", NULL, -1},
    {AMP_TYPE_BRIGHT, "Bright Clean", NULL, -1},
    {AMP_TYPE_CHUNK, "Chunk", NULL, -1},
    {AMP_TYPE_DIGITECH_CLEAN, "Clean Tube", NULL, -1},
    {AMP_TYPE_CRUNCH, "Crunch", NULL, -1},
    {AMP_TYPE_HIGH_GAIN, "High Gain", NULL, -1},
    {AMP_TYPE_BLUES, "Blues", NULL, -1},
    {AMP_TYPE_FUZZ, "Fuzz", NULL, -1},
    {AMP_TYPE_JUMBO_ACOUSTIC, "Jumbo Acoustic", NULL, -1},
    {AMP_TYPE_ACOUSTIC, "Dread Acoustic", NULL, -1},
    {AMP_TYPE_SVT_ROCK_BASS, "SVT Rock Bass", NULL, -1},
    {AMP_TYPE_SVT_CLASSIC_BASS, "SVT Classic Bass", NULL, -1},
    {AMP_TYPE_PEG_B15_BASS, "Peg B-15 Bass", NULL, -1},
    {AMP_TYPE_BASIC_BASS , "Basic Bass", NULL, -1},
    {AMP_TYPE_SHOWMAN_BASS , "Showman Bass", NULL, -1},
    {AMP_TYPE_ASH_MODERN_BASS , "Ash Modern Bass", NULL, -1},
    {AMP_TYPE_BRIT_BASS , "Brit Bass", NULL, -1},
    {AMP_TYPE_SOLAR_BASS , "Solar 200s Bass", NULL, -1},
    {AMP_TYPE_BOOGIE_BASS , "Boogie Bass", NULL, -1},
    {AMP_TYPE_HART_BASS , "Hart Bass", NULL, -1},
};

static EffectGroup rp250_eq_group[] = {
    {EQ_TYPE_BRIGHT, "Bright", rp250_eq_settings, G_N_ELEMENTS(rp250_eq_settings)},
    {EQ_TYPE_MIDBOOST, "Mid Boost", rp250_eq_settings, G_N_ELEMENTS(rp250_eq_settings)},
    {EQ_TYPE_SCOOP, "Scoop", rp250_eq_settings, G_N_ELEMENTS(rp250_eq_settings)},
    {EQ_TYPE_WARM, "Warm", rp250_eq_settings, G_N_ELEMENTS(rp250_eq_settings)},
};

static EffectGroup rp355_eq_group_A[] = {
    {EQ_TYPE_BRIGHT, "Bright", rp355_eq_settings_A, G_N_ELEMENTS(rp355_eq_settings_A)},
    {EQ_TYPE_MIDBOOST, "Mid Boost", rp355_eq_settings_A, G_N_ELEMENTS(rp355_eq_settings_A)},
    {EQ_TYPE_SCOOP, "Scoop", rp355_eq_settings_A, G_N_ELEMENTS(rp355_eq_settings_A)},
    {EQ_TYPE_WARM, "Warm", rp355_eq_settings_A, G_N_ELEMENTS(rp355_eq_settings_A)},
};

static EffectGroup rp355_eq_group_B[] = {
    {EQ_TYPE_BRIGHT, "Bright", rp355_eq_settings_B, G_N_ELEMENTS(rp355_eq_settings_B)},
    {EQ_TYPE_MIDBOOST, "Mid Boost", rp355_eq_settings_B, G_N_ELEMENTS(rp355_eq_settings_B)},
    {EQ_TYPE_SCOOP, "Scoop", rp355_eq_settings_B, G_N_ELEMENTS(rp355_eq_settings_B)},
    {EQ_TYPE_WARM, "Warm", rp355_eq_settings_B, G_N_ELEMENTS(rp355_eq_settings_B)},
};

static EffectGroup rp500_eq_group[] = {
    {-1, NULL, rp500_eq_settings, G_N_ELEMENTS(rp500_eq_settings)},
};

static EffectGroup rp150_amp_cab_group[] = {
    {AMP_CAB_DIRECT, "Direct", NULL, -1},
    {AMP_CAB_DELUXE, "Deluxe 1x12", NULL, -1},
    {AMP_CAB_TWIN, "Twin 2x12", NULL, -1},
    {AMP_CAB_BRITISH2_12, "British 2x12", NULL, -1},
    {AMP_CAB_BASSMAN, "Bassman 4x10", NULL, -1},
    {AMP_CAB_BRITISH4_12, "British 4x12", NULL, -1},
    {AMP_CAB_VINTAGE, "Vintage V30 4x12", NULL, -1},
    {AMP_CAB_DIGI_SOLO, "DigiTech Solo 4x12", NULL, -1},
    {AMP_CAB_DIGI_BRIGHT, "DigiTech Bright 2x12", NULL, -1},
    {AMP_CAB_DIGI_METAL, "DigiTech Metal 4x12", NULL, -1},
    {AMP_CAB_DIGI_ROCK, "DigiTech Rock 4x12", NULL, -1},
    {AMP_CAB_DIGI_ALT, "DigiTech Alt 4x12", NULL, -1},
    {AMP_CAB_DIGI_VNTG, "DigiTech Vntg 4x12", NULL, -1},
};

static EffectGroup rp250_amp_cab_group[] = {
    {AMP_CAB_DIRECT, "Direct", NULL, -1},
    {AMP_CAB_CHAMP, "Champ 1x8", NULL, -1},
    {AMP_CAB_DELUXE, "Deluxe 1x12", NULL, -1},
    {AMP_CAB_TWIN, "Twin 2x12", NULL, -1},
    {AMP_CAB_BRITISH2_12, "British 2x12", NULL, -1},
    {AMP_CAB_BASSMAN, "Bassman 4x10", NULL, -1},
    {AMP_CAB_BRITISH4_12, "British 4x12", NULL, -1},
    {AMP_CAB_BRITISH_GREEN, "British Green 4x12", NULL, -1},
    {AMP_CAB_VINTAGE, "Vintage V30 4x12", NULL, -1},
    {AMP_CAB_DIGI_SOLO, "DigiTech Solo 4x12", NULL, -1},
    {AMP_CAB_DIGI_BRIGHT, "DigiTech Bright 2x12", NULL, -1},
    {AMP_CAB_DIGI_METAL, "DigiTech Metal 4x12", NULL, -1},
    {AMP_CAB_DIGI_ROCK, "DigiTech Rock 4x12", NULL, -1},
    {AMP_CAB_DIGI_ALT, "DigiTech Alt 4x12", NULL, -1},
    {AMP_CAB_DIGI_VNTG, "DigiTech Vntg 4x12", NULL, -1},
};

static EffectGroup rp355_amp_cab_group[] = {
    {AMP_CAB_DIRECT, "Direct", NULL, -1},
    {AMP_CAB_CHAMP, "Champ 1x8", NULL, -1},
    {AMP_CAB_DELUXE, "Deluxe 1x12", NULL, -1},
    {AMP_CAB_DELUXE_REVERB, "Deluxe Reverb 1x12", NULL, -1},
    {AMP_CAB_BLONDE2_12, "Blonde 2x12", NULL, -1},
    {AMP_CAB_TWIN, "Twin 2x12", NULL, -1},
    {AMP_CAB_BRITISH2_12, "British 2x12", NULL, -1},
    {AMP_CAB_BASSMAN, "Bassman 4x10", NULL, -1},
    {AMP_CAB_BRITISH4_12, "British 4x12", NULL, -1},
    {AMP_CAB_BRITISH_GREEN, "British Green 4x12", NULL, -1},
    {AMP_CAB_FANE4_12, "Fane 4x12", NULL, -1},
    {AMP_CAB_BOUTIQUE4_12, "Boutique 4x12", NULL, -1},
    {AMP_CAB_VINTAGE, "Vintage V30 4x12", NULL, -1},
    {AMP_CAB_DIGI_SOLO, "DigiTech Solo 4x12", NULL, -1},
    {AMP_CAB_DIGI_BRIGHT, "DigiTech Bright 2x12", NULL, -1},
    {AMP_CAB_DIGI_METAL, "DigiTech Metal 4x12", NULL, -1},
    {AMP_CAB_DIGI_ROCK, "DigiTech Rock 4x12", NULL, -1},
    {AMP_CAB_DIGI_ALT, "DigiTech Alt 4x12", NULL, -1},
    {AMP_CAB_DIGI_VNTG, "DigiTech Vntg 4x12", NULL, -1},
};

static EffectGroup rp500_amp_cab_group[] = {
    {AMP_CAB_DIRECT, "Direct", NULL, -1},
    {AMP_CAB_CHAMP, "Champ", NULL, -1},
    {AMP_CAB_DELUXE, "Deluxe", NULL, -1},
    {AMP_CAB_DELUXE_REVERB, "Deluxe Reverb 1x12", NULL, -1},
    {AMP_CAB_BRITISH1_12, "British 1x12", NULL, -1},
    {AMP_CAB_GA1_12, "GA 1x12", NULL, -1},
    {AMP_CAB_BLONDE2_12, "Blonde 2x12", NULL, -1},
    {AMP_CAB_TWIN, "Twin 2x12", NULL, -1},
    {AMP_CAB_BRITISH2_12, "British 2x12", NULL, -1},
    {AMP_CAB_JAZZ2_12, "Jazz 2x12", NULL, -1},
    {AMP_CAB_BASSMAN, "Bassman 4x10", NULL, -1},
    {AMP_CAB_BRITISH4_12, "British 4x12", NULL, -1},
    {AMP_CAB_BRITISH_GREEN, "Greenback 4x12", NULL, -1},
    {AMP_CAB_FANE4_12, "Fane 4x12", NULL, -1},
    {AMP_CAB_BOUTIQUE4_12, "Boutique 4x12", NULL, -1},
    {AMP_CAB_VINTAGE, "Vintage 4x12", NULL, -1},
    {AMP_CAB_RECTO4_12, "Recto 4x12", NULL, -1},
    {AMP_CAB_DIGI_SOLO, "DigiTech Solo 4x12", NULL, -1},
    {AMP_CAB_DIGI_BRIGHT, "DigiTech Bright 2x12", NULL, -1},
    {AMP_CAB_DIGI_METAL, "DigiTech Metal 4x12", NULL, -1},
    {AMP_CAB_DIGI_ROCK, "DigiTech Rock 4x12", NULL, -1},
    {AMP_CAB_DIGI_ALT, "DigiTech Alt 4x12", NULL, -1},
    {AMP_CAB_DIGI_VNTG, "DigiTech Vintage 4x12", NULL, -1},
    {AMP_CAB_DIGI_CHUNK, "DigiTech Chunk 4x12", NULL, -1},
    {AMP_CAB_DIGI_SPANK2_12, "DigiTech Spank 2x12", NULL, -1},
    {AMP_CAB_DIGI_SPKR_COMP, "DigiTech Spkr Comp", NULL, -1},
};

static EffectGroup rp1000_amp_cab_group[] = {
    {AMP_CAB_DIRECT, "Direct", NULL, -1},
    {AMP_CAB_CHAMP, "Champ", NULL, -1},
    {AMP_CAB_DELUXE, "Deluxe", NULL, -1},
    {AMP_CAB_DELUXE_REVERB, "Deluxe Reverb 1x12", NULL, -1},
    {AMP_CAB_BRITISH1_12, "British 1x12", NULL, -1},
    {AMP_CAB_GA1_12, "GA 1x12", NULL, -1},
    {AMP_CAB_BLONDE2_12, "Blonde 2x12", NULL, -1},
    {AMP_CAB_TWIN, "Twin 2x12", NULL, -1},
    {AMP_CAB_BRITISH2_12, "British 2x12", NULL, -1},
    {AMP_CAB_JAZZ2_12, "Jazz 2x12", NULL, -1},
    {AMP_CAB_JBL_215, "JBL/Lansing Enclosure", NULL, -1},
    {AMP_CAB_BASSMAN, "Bassman 4x10", NULL, -1},
    {AMP_CAB_BRITISH4_12, "British 4x12", NULL, -1},
    {AMP_CAB_BRITISH_GREEN, "Greenback 4x12", NULL, -1},
    {AMP_CAB_FANE4_12, "Fane 4x12", NULL, -1},
    {AMP_CAB_BOUTIQUE4_12, "Boutique 4x12", NULL, -1},
    {AMP_CAB_VINTAGE, "Vintage 4x12", NULL, -1},
    {AMP_CAB_RECTO4_12, "Recto 4x12", NULL, -1},
    {AMP_CAB_DIGI_SOLO, "DigiTech Solo 4x12", NULL, -1},
    {AMP_CAB_DIGI_BRIGHT, "DigiTech Bright 2x12", NULL, -1},
    {AMP_CAB_DIGI_METAL, "DigiTech Metal 4x12", NULL, -1},
    {AMP_CAB_DIGI_ROCK, "DigiTech Rock 4x12", NULL, -1},
    {AMP_CAB_DIGI_ALT, "DigiTech Alt 4x12", NULL, -1},
    {AMP_CAB_DIGI_VNTG, "DigiTech Vintage 4x12", NULL, -1},
    {AMP_CAB_DIGI_CHUNK, "DigiTech Chunk 4x12", NULL, -1},
    {AMP_CAB_DIGI_SPANK2_12, "DigiTech Spank 2x12", NULL, -1},
    {AMP_CAB_DIGI_SPKR_COMP, "DigiTech Spkr Comp", NULL, -1},
};

static EffectGroup gnx3k_amp_cab_group[] = {
    {GNX_AMP_CAB_DIRECT, "Direct", NULL, -1},
    {GNX_AMP_CAB_TWEED1_8, "Tweed 1x8", NULL, -1},
    {GNX_AMP_CAB_TWEED1_12, "Tweed 1x12", NULL, -1},
    {GNX_AMP_CAB_BLACKFACE1_12, "Blackface 1x12", NULL, -1},
    {GNX_AMP_CAB_BRITISH1_12, "British 1x12", NULL, -1},
    {GNX_AMP_CAB_BLACKFACE2_12, "Blackface 2x12", NULL, -1},
    {GNX_AMP_CAB_BLONDE2_12, "Blonde 2x12", NULL, -1},
    {GNX_AMP_CAB_BRITISH2_12, "British 2x12", NULL, -1},
    {GNX_AMP_CAB_TWEED4_10, "Tweed 4x10", NULL, -1},
    {GNX_AMP_CAB_BRITISH_70_4_12, "British 70 4x12", NULL, -1},
    {GNX_AMP_CAB_BRITISH_GREEN4_12, "British Green 4x12", NULL, -1},
    {GNX_AMP_CAB_STRAIGHT_V30_4_12, "Straight V30 4x12", NULL, -1},
    {GNX_AMP_CAB_SLANT_V30_4_12, "Slant V30 4x12", NULL, -1},
    {GNX_AMP_CAB_FANE4_12, "Fane 4x12", NULL, -1},
    {GNX_AMP_CAB_2101_SPKR_COMP, "2101 Spkr Comp", NULL, -1},
    {GNX_AMP_CAB_DIGI_SPANK, "Digitech Spank 4x12", NULL, -1},
    {GNX_AMP_CAB_DIGI_SOLO, "Digitech Solo 4x12", NULL, -1},
    {GNX_AMP_CAB_DIGI_METAL, "Digitech Metal 4x12", NULL, -1},
    {GNX_AMP_CAB_DIGI_BRIGHT, "Digitech Bright 4x12", NULL, -1},
    {GNX_AMP_CAB_DIGI_CHUNK, "Digitech Chunk 4x12", NULL, -1},
    {GNX_AMP_CAB_JUMBO_ACOUSTIC, "Jumbo Acoustic", NULL, -1},
    {GNX_AMP_CAB_DREAD_ACOUSTIC, "Dread Acoustic", NULL, -1},
    {GNX_AMP_CAB_HART_BASS1_15, "Hart Bass 1x15", NULL, -1},
    {GNX_AMP_CAB_BASIC_BASS1_15, "Basic Bass 1x15", NULL, -1},
    {GNX_AMP_CAB_PORTA_BASS1_15, "Porta Bass 1x15", NULL, -1},
    {GNX_AMP_CAB_REFLEX1_18, "Reflex 1x18", NULL, -1},
    {GNX_AMP_CAB_SOLAR_BASS2_15, "Solar Bass 2x15", NULL, -1},
    {GNX_AMP_CAB_DE_BASS4_10, "DE Bass 4x10", NULL, -1},
    {GNX_AMP_CAB_ASH_BASS4_10, "Ash Bass 4x10", NULL, -1},
    {GNX_AMP_CAB_GOLIATH_BASS4_10, "Goliath Bass 4x10", NULL, -1},
    {GNX_AMP_CAB_HART_BASS4_10, "Hart Bass 4x10", NULL, -1},
    {GNX_AMP_CAB_SVT_BASS8_10, "SVT Bass 8x10", NULL, -1},
};

static EffectGroup gnx3k_ch1_cab_tuning_group[] = {
    {-1, NULL, gnx3k_ch1_cab_tuning_settings, G_N_ELEMENTS(gnx3k_ch1_cab_tuning_settings)},
};

static EffectGroup gnx3k_ch2_cab_tuning_group[] = {
    {-1, NULL, gnx3k_ch2_cab_tuning_settings, G_N_ELEMENTS(gnx3k_ch2_cab_tuning_settings)},
};

static EffectGroup gnx3k_ch1_amp_eq_group[] = {
    {-1, NULL, gnx3k_ch1_amp_eq_settings, G_N_ELEMENTS(gnx3k_ch1_amp_eq_settings)},
};

static EffectGroup gnx3k_ch2_amp_eq_group[] = {
    {-1, NULL, gnx3k_ch2_amp_eq_settings, G_N_ELEMENTS(gnx3k_ch2_amp_eq_settings)},
};

/* LIBRARY_TONE, LIBRARY_POSITION */
static EffectGroup tone_lib_group[] = {
    {TONE_LIB_CUSTOM, "None", NULL, -1},
    {TONE_LIB_OVERDRIVE, "Overdrive", NULL, -1},
    {TONE_LIB_ROCK1, "Rock 1", NULL, -1},
    {TONE_LIB_ROCK2, "Rock 2", NULL, -1},
    {TONE_LIB_BLUES1, "Blues 1", NULL, -1},
    {TONE_LIB_BLUES2, "Blues 2", NULL, -1},
    {TONE_LIB_METAL1, "Metal 1", NULL, -1},
    {TONE_LIB_METAL2, "Metal 2", NULL, -1},
    {TONE_LIB_COUNTRY1, "Country 1", NULL, -1},
    {TONE_LIB_COUNTRY2, "Country 2", NULL, -1},
    {TONE_LIB_WARM_DRIVE, "Warm Drive", NULL, -1},
    {TONE_LIB_CRUNCH, "Crunch", NULL, -1},
    {TONE_LIB_TEXAS_TONE, "Texas Tone", NULL, -1},
    {TONE_LIB_ROCKABILLY, "Rockabilly", NULL, -1},
    {TONE_LIB_SOLO1, "Solo 1", NULL, -1},
    {TONE_LIB_SOLO2, "Solo 2", NULL, -1},
    {TONE_LIB_ROCKWAH, "Rock Wah", NULL, -1},
    {TONE_LIB_CHUNKY, "Chunky", NULL, -1},
    {TONE_LIB_SMOOTH, "Smooth", NULL, -1},
    {TONE_LIB_HEAVY, "Heavy", NULL, -1},
    {TONE_LIB_CLEAN1, "Clean 1", NULL, -1},
    {TONE_LIB_CLEAN2, "Clean 2", NULL, -1},
    {TONE_LIB_BRITISH1, "British 1", NULL, -1},
    {TONE_LIB_BRITISH2, "British 2", NULL, -1},
    {TONE_LIB_AMERICAN1, "American 1", NULL, -1},
    {TONE_LIB_AMERICAN2, "American 2", NULL, -1},
    {TONE_LIB_TUBE_DRIVE, "Tube Drive", NULL, -1},
    {TONE_LIB_DISTORTION, "Distortion", NULL, -1},
    {TONE_LIB_SCOOPED, "Scooped", NULL, -1},
    {TONE_LIB_PUNCHY, "Punchy", NULL, -1},
    {TONE_LIB_BRIGHT_CLEAN, "Bright Clean", NULL, -1},
};

/* LIBRARY_EFFECTS, LIBRARY_POSITION */
static EffectGroup effects_lib_group[] = {
    {EFFECTS_LIB_CUSTOM, "None", NULL, -1},
    {EFFECTS_LIB_CHORUS, "Chorus", NULL, -1},
    {EFFECTS_LIB_PHASER, "Phaser", NULL, -1},
    {EFFECTS_LIB_FLANGER, "Flanger", NULL, -1},
    {EFFECTS_LIB_PITCH, "Pitch", NULL, -1},
    {EFFECTS_LIB_TREMOLO, "Tremolo", NULL, -1},
    {EFFECTS_LIB_ROTARY, "Rotary", NULL, -1},
    {EFFECTS_LIB_ENVELOPE, "Envelope Filter", NULL, -1},
    {EFFECTS_LIB_DIGITAL, "Digital Delay", NULL, -1},
    {EFFECTS_LIB_ANALOG, "Analog Delay", NULL, -1},
    {EFFECTS_LIB_PONG, "Pong Delay", NULL, -1},
    {EFFECTS_LIB_MOD, "Mod Delay", NULL, -1},
    {EFFECTS_LIB_TAPE, "Tape Delay", NULL, -1},
    {EFFECTS_LIB_HALL, "Hall Reverb", NULL, -1},
    {EFFECTS_LIB_PLATE, "Plate Reverb", NULL, -1},
    {EFFECTS_LIB_SPRING, "Spring Reverb", NULL, -1},
    {EFFECTS_LIB_CHORUS_DIGITAL, "Chorus + Digital Delay", NULL, -1},
    {EFFECTS_LIB_CHORUS_DELAY_REVERB, "Chorus + Delay + Reverb", NULL, -1},
    {EFFECTS_LIB_FLANGER_ANALOG, "Flanger + Analog Delay", NULL, -1},
    {EFFECTS_LIB_PHASER_TAPE, "Phaser + Tape Delay", NULL, -1},
    {EFFECTS_LIB_PHASER_MOD, "Phaser + Mod Delay", NULL, -1},
    {EFFECTS_LIB_PHASER_ROOM, "Phaser + Room Reverb", NULL, -1},
    {EFFECTS_LIB_DIGITAL_HALL, "Digital Delay + Hall Reverb", NULL, -1},
    {EFFECTS_LIB_ANALOG_SPRING, "Analog Delay + Spring Reverb", NULL, -1},
    {EFFECTS_LIB_CHORUS_HALL, "Chorus + Hall Reverb", NULL, -1},
    {EFFECTS_LIB_PONG_HALL, "Pong Delay + Hall Reverb", NULL, -1},
    {EFFECTS_LIB_TAPE_SPRING, "Tape Delay + Spring Reverb", NULL, -1},
    {EFFECTS_LIB_TREMOLO_TAPE, "Tremolo + Tape Delay", NULL, -1},
    {EFFECTS_LIB_PITCH_DIGITAL, "Pitch + Digital Delay", NULL, -1},
    {EFFECTS_LIB_MOD_PLATE, "Mod Delay + Plate Reverb", NULL, -1},
    {EFFECTS_LIB_ROTARY_TAPE, "Rotary + Tape Delay", NULL, -1},
};

static EffectGroup tone_lib_level_a_group[] = {
    {-1, NULL, tone_lib_level_a_settings, G_N_ELEMENTS(tone_lib_level_a_settings)},
};

static EffectGroup tone_lib_level_b_group[] = {
    {-1, NULL, tone_lib_level_b_settings, G_N_ELEMENTS(tone_lib_level_b_settings)},
};

static EffectGroup pickup_group[] = {
    {PICKUP_TYPE_HB_SC, "HB>SC", NULL, -1},
    {PICKUP_TYPE_SC_HB, "SC>HB", NULL, -1},
};

static EffectGroup pre_post_group[] = {
    {CHORUSFX_PRE, "Pre Amp", NULL, -1},
    {CHORUSFX_POST, "Post Amp", NULL, -1},
};

static EffectGroup delay_mult_group[] = {
    {DELAY_3_QUARTR, "3 Quarter", NULL, -1},
    {DELAY_EIGHT, "Eighth", NULL, -1},
    {DELAY_DOTEIGHT, "Dot Eighth", NULL, -1},
    {DELAY_QUARTER, "Quarter", NULL, -1},
    {DELAY_HALF, "Half", NULL, -1},
};

static Effect gnx3k_wah_effect[] = {
    {NULL, WAH_ON_OFF, WAH_TYPE, WAH_POSITION, gnx3k_wah_group, G_N_ELEMENTS(gnx3k_wah_group)},
};

static Effect wah_effect[] = {
    {NULL, WAH_ON_OFF, WAH_TYPE, WAH_POSITION, wah_group, G_N_ELEMENTS(wah_group)},
};

static Effect expression_pedal_assign_effect[] = {
    {NULL, -1, EXP_TYPE, EXP_POSITION, expression_pedal_assign_group, G_N_ELEMENTS(expression_pedal_assign_group)},
};

static Effect gnx3k_whammy_effect[] = {
    {NULL, GNX3K_WHAM_ENABLE, GNX3K_WHAM_TYPE, GNX3K_WHAM_POSITION, gnx3k_whammy_group, G_N_ELEMENTS(gnx3k_whammy_group)},
};

static Effect gnx3k_preset_effect[] = {
    {NULL, -1, -1, -1, gnx3k_preset_group, G_N_ELEMENTS(gnx3k_preset_group)},
};

static Effect rp250_comp_effect[] = {
    {NULL, COMP_ON_OFF, COMP_TYPE, COMP_POSITION, rp250_comp_group, G_N_ELEMENTS(rp250_comp_group)},
};

static Effect rp355_comp_effect[] = {
    {NULL, COMP_ON_OFF, COMP_TYPE, COMP_POSITION, rp355_comp_group, G_N_ELEMENTS(rp355_comp_group)},
};

static Effect gnx_comp_effect[] = {
    {"Compressor", COMP_ON_OFF, -1, COMP_POSITION, gnx_comp_group, G_N_ELEMENTS(gnx_comp_group)},
};

static Effect rp500_comp_effect[] = {
    {NULL, COMP_ON_OFF, COMP_TYPE, COMP_POSITION, rp500_comp_group, G_N_ELEMENTS(rp500_comp_group)},
};

static Effect rp150_dist_effect[] = {
    {NULL, DIST_ON_OFF, DIST_TYPE, DIST_POSITION, rp150_dist_group, G_N_ELEMENTS(rp150_dist_group)},
};

static Effect rp155_dist_effect[] = {
    {NULL, DIST_ON_OFF, DIST_TYPE, DIST_POSITION, rp155_dist_group, G_N_ELEMENTS(rp155_dist_group)},
};

static Effect rp250_dist_effect[] = {
    {NULL, DIST_ON_OFF, DIST_TYPE, DIST_POSITION, rp250_dist_group, G_N_ELEMENTS(rp250_dist_group)},
};

static Effect rp355_dist_effect[] = {
    {NULL, DIST_ON_OFF, DIST_TYPE, DIST_POSITION, rp355_dist_group, G_N_ELEMENTS(rp355_dist_group)},
};

static Effect rp500_dist_effect[] = {
    {NULL, DIST_ON_OFF, DIST_TYPE, DIST_POSITION, rp500_dist_group, G_N_ELEMENTS(rp500_dist_group)},
};

static Effect rp1000_dist_effect[] = {
    {NULL, DIST_ON_OFF, DIST_TYPE, DIST_POSITION, rp1000_dist_group, G_N_ELEMENTS(rp1000_dist_group)},
};

static Effect gnx4_dist_effect[] = {
    {NULL, DIST_ON_OFF, DIST_TYPE, DIST_POSITION, gnx4_dist_group, G_N_ELEMENTS(gnx4_dist_group)},
};

static Effect gnx3k_dist_effect[] = {
    {NULL, DIST_ON_OFF, DIST_TYPE, DIST_POSITION, gnx3k_dist_group, G_N_ELEMENTS(gnx3k_dist_group)},
};

static Effect gnx3k_noisegate_effect[] = {
    {NULL, NOISEGATE_ON_OFF, NOISEGATE_TYPE, NOISEGATE_POSITION, gnx3k_noisegate_group, G_N_ELEMENTS(gnx3k_noisegate_group)},
};

static Effect noisegate_effect[] = {
    {NULL, NOISEGATE_ON_OFF, NOISEGATE_TYPE, NOISEGATE_POSITION, noisegate_group, G_N_ELEMENTS(noisegate_group)},
};

static Effect gnx4_chorusfx_effect[] = {
    {NULL, CHORUSFX_ON_OFF, CHORUSFX_TYPE, CHORUSFX_POSITION, gnx4_chorusfx_group, G_N_ELEMENTS(gnx4_chorusfx_group)},
};

static Effect gnx3k_chorusfx_effect[] = {
    {NULL, CHORUSFX_ON_OFF, CHORUSFX_TYPE, CHORUSFX_POSITION, gnx3k_chorusfx_group, G_N_ELEMENTS(gnx3k_chorusfx_group)},
};

static Effect rp150_chorusfx_effect[] = {
    {NULL, CHORUSFX_ON_OFF, CHORUSFX_TYPE, CHORUSFX_POSITION, rp155_chorusfx_group, G_N_ELEMENTS(rp155_chorusfx_group)},
};

static Effect rp250_chorusfx_effect[] = {
    {NULL, CHORUSFX_ON_OFF, CHORUSFX_TYPE, CHORUSFX_POSITION, rp250_chorusfx_group, G_N_ELEMENTS(rp250_chorusfx_group)},
};

static Effect rp255_chorusfx_effect[] = {
    {NULL, CHORUSFX_ON_OFF, CHORUSFX_TYPE, CHORUSFX_POSITION, rp255_chorusfx_group, G_N_ELEMENTS(rp255_chorusfx_group)},
};

static Effect rp355_chorusfx_effect[] = {
    {NULL, CHORUSFX_ON_OFF,CHORUSFX_TYPE, CHORUSFX_POSITION, rp355_chorusfx_group, G_N_ELEMENTS(rp355_chorusfx_group)},
    {"Position",-1, CHORUSFX_PRE_POST,CHORUSFX_POSITION, pre_post_group,G_N_ELEMENTS(pre_post_group)},
};

static Effect rp355_lfo1_effect[] = {
    {NULL, -1, LFO_TYPE, LFO1_POSITION, rp355_lfo1_group, G_N_ELEMENTS(rp355_lfo1_group)},
};

static Effect rp355_lfo2_effect[] = {
    {NULL, -1, LFO_TYPE, LFO2_POSITION, rp355_lfo2_group, G_N_ELEMENTS(rp355_lfo2_group)},
};

static Effect rp500_chorusfx_effect[] = {
    {NULL, CHORUSFX_ON_OFF, CHORUSFX_TYPE, CHORUSFX_POSITION, rp500_chorusfx_group, G_N_ELEMENTS(rp500_chorusfx_group)},
};

static Effect rp1000_chorusfx_effect[] = {
    {NULL, CHORUSFX_ON_OFF, CHORUSFX_TYPE, CHORUSFX_POSITION, rp1000_chorusfx_group, G_N_ELEMENTS(rp1000_chorusfx_group)},
    {"Position",-1, CHORUSFX_PRE_POST,CHORUSFX_POSITION, pre_post_group,G_N_ELEMENTS(pre_post_group)},
};

static Effect gnx3k_delay_effect[] = {
    {NULL, DELAY_ON_OFF, DELAY_TYPE, DELAY_POSITION, gnx3k_delay_group, G_N_ELEMENTS(gnx3k_delay_group)},
};

static Effect rp250_delay_effect[] = {
    {NULL, DELAY_ON_OFF, DELAY_TYPE, DELAY_POSITION, rp250_delay_group, G_N_ELEMENTS(rp250_delay_group)},
};

static Effect rp355_delay_effect[] = {
    {NULL, DELAY_ON_OFF, DELAY_TYPE, DELAY_POSITION, rp355_delay_group, G_N_ELEMENTS(rp355_delay_group)},
};

static Effect rp500_delay_effect[] = {
    {NULL, DELAY_ON_OFF, DELAY_TYPE, DELAY_POSITION, rp500_delay_group, G_N_ELEMENTS(rp500_delay_group)},
};

static Effect rp1000_delay_effect[] = {
    {NULL, DELAY_ON_OFF, DELAY_TYPE, DELAY_POSITION, rp1000_delay_group, G_N_ELEMENTS(rp1000_delay_group)},
    {NULL, -1, DELAY_MULTIPLIER, DELAY_POSITION, delay_mult_group, G_N_ELEMENTS(delay_mult_group)},
};

static Effect gnx3k_reverb_effect[] = {
    {NULL, REVERB_ON_OFF, REVERB_TYPE, REVERB_POSITION, gnx3k_reverb_group, G_N_ELEMENTS(gnx3k_reverb_group)},
};

static Effect reverb_effect[] = {
    {NULL, REVERB_ON_OFF, REVERB_TYPE, REVERB_POSITION, reverb_group, G_N_ELEMENTS(reverb_group)},
};

static Effect rp150_amp_effect[] = {
    {NULL, AMP_ON_OFF, AMP_TYPE, AMP_A_POSITION, rp150_amp_group, G_N_ELEMENTS(rp150_amp_group)},
    {"Cabinet", -1, AMP_CAB_TYPE, AMP_CAB_POSITION, rp150_amp_cab_group, G_N_ELEMENTS(rp150_amp_cab_group)},
};

static Effect rp155_amp_effect[] = {
    {NULL, AMP_ON_OFF, AMP_TYPE, AMP_A_POSITION, rp155_amp_group, G_N_ELEMENTS(rp155_amp_group)},
    {"Cabinet", -1, AMP_CAB_TYPE, AMP_CAB_POSITION, rp150_amp_cab_group, G_N_ELEMENTS(rp150_amp_cab_group)},
};

static Effect rp250_amp_effect[] = {
    {NULL, AMP_ON_OFF, AMP_TYPE, AMP_A_POSITION, rp250_amp_group, G_N_ELEMENTS(rp250_amp_group)},
    {"Cabinet", -1, AMP_CAB_TYPE, AMP_CAB_POSITION, rp250_amp_cab_group, G_N_ELEMENTS(rp250_amp_cab_group)},
};

/* same cabs as rp250, but 3 new amp models */
static Effect rp255_amp_effect[] = {
    {NULL, AMP_ON_OFF, AMP_TYPE, AMP_A_POSITION, rp255_amp_group, G_N_ELEMENTS(rp255_amp_group)},
    {"Cabinet", -1, AMP_CAB_TYPE, AMP_CAB_POSITION, rp250_amp_cab_group, G_N_ELEMENTS(rp250_amp_cab_group)},
};

static Effect rp355_select_amp_effect[] = {
    {"Select Amp", -1, AMP_CHANNEL, AMP_CHANNEL_POSITION, rp355_amp_select_group, G_N_ELEMENTS(rp355_amp_select_group)},
};

static Effect rp355_amp_effect_A[] = {
    {NULL, AMP_ON_OFF, AMP_TYPE, AMP_A_POSITION, rp355_amp_group_A, G_N_ELEMENTS(rp355_amp_group_A)},
    {"Cabinet", -1, AMP_CAB_TYPE, AMP_CAB_POSITION, rp355_amp_cab_group, G_N_ELEMENTS(rp355_amp_cab_group)},
};

static Effect rp355_amp_effect_B[] = {
    {NULL, AMP_ON_OFF, AMP_TYPE, AMP_B_POSITION, rp355_amp_group_B, G_N_ELEMENTS(rp355_amp_group_B)},
    {"Cabinet", -1, AMP_CAB_TYPE, AMP_CAB_B_POSITION, rp355_amp_cab_group, G_N_ELEMENTS(rp355_amp_cab_group)},
};

static Effect rp500_amp_effect[] = {
    {"Amp/Cab Bypass", AMP_BYPASS_ON_OFF, -1, AMP_BYPASS_POSITION, NULL, -1},
    {NULL, -1, AMP_TYPE, AMP_A_POSITION, rp500_amp_group, G_N_ELEMENTS(rp500_amp_group)},
    {"Cabinet", -1, AMP_CAB_TYPE, AMP_CAB_POSITION, rp500_amp_cab_group, G_N_ELEMENTS(rp500_amp_cab_group)},
};

static Effect rp1000_amp_effect[] = {
    {"Amp Loop", AMP_LOOP_ON_OFF, -1, AMP_LOOP_POSITION, NULL, -1},
    {"Amp/Cab Bypass", AMP_BYPASS_ON_OFF, -1, AMP_BYPASS_POSITION, NULL, -1},
    {NULL, -1, AMP_TYPE, AMP_A_POSITION, rp1000_amp_group, G_N_ELEMENTS(rp1000_amp_group)},
    {NULL, -1, AMP_CAB_TYPE, AMP_CAB_POSITION, rp1000_amp_cab_group, G_N_ELEMENTS(rp1000_amp_cab_group)},
};

static Effect gnx3k_channel_1_effect[] = {
    {"EQ Enable", AMP_EQ_ON_OFF, AMP_TYPE, AMP_A_POSITION, gnx3k_amp_group, G_N_ELEMENTS(gnx3k_amp_group)},
    {NULL, -1, AMP_CAB_TYPE, AMP_CAB_POSITION, gnx3k_amp_cab_group, G_N_ELEMENTS(gnx3k_amp_cab_group)},
    {NULL, -1, -1, -1, gnx3k_ch1_cab_tuning_group, G_N_ELEMENTS(gnx3k_ch1_cab_tuning_group)},
    {NULL, -1, -1, -1, gnx3k_ch1_amp_eq_group, G_N_ELEMENTS(gnx3k_ch1_amp_eq_group)},
};

static Effect gnx3k_channel_2_effect[] = {
    {"EQ Enable", AMP_EQ_ON_OFF, AMP_TYPE, AMP_B_POSITION, gnx3k_amp_group, G_N_ELEMENTS(gnx3k_amp_group)},
    {NULL, -1, AMP_CAB_TYPE, AMP_CAB_B_POSITION, gnx3k_amp_cab_group, G_N_ELEMENTS(gnx3k_amp_cab_group)},
    {NULL, -1, -1, -1, gnx3k_ch2_cab_tuning_group, G_N_ELEMENTS(gnx3k_ch2_cab_tuning_group)},
    {NULL, -1, -1, -1, gnx3k_ch2_amp_eq_group, G_N_ELEMENTS(gnx3k_ch2_amp_eq_group)},
};

static Effect rp250_eq_effect[] = {
    {NULL, EQ_ENABLE, EQ_TYPE, EQ_A_POSITION, rp250_eq_group, G_N_ELEMENTS(rp250_eq_group)},
};

static Effect rp355_eq_effect_A[] = {
    {NULL, EQ_ENABLE, EQ_TYPE, EQ_A_POSITION, rp355_eq_group_A, G_N_ELEMENTS(rp355_eq_group_A)},
};

static Effect rp355_eq_effect_B[] = {
    {NULL, EQ_ENABLE, EQ_TYPE, EQ_B_POSITION, rp355_eq_group_B, G_N_ELEMENTS(rp355_eq_group_B)},
};

static Effect rp500_eq_effect[] = {
    {"Enable Equalizer", EQ_ENABLE, -1, EQ_A_POSITION, rp500_eq_group, G_N_ELEMENTS(rp500_eq_group)},
};

static Effect global_effect[] = {
    {NULL, -1, 0, GLOBAL_POSITION, global_group, G_N_ELEMENTS(global_group)},
};

static Effect pickup_misc_effect[] = {
    {NULL, PICKUP_ON_OFF, PICKUP_TYPE, PICKUP_POSITION, pickup_group, G_N_ELEMENTS(pickup_group)},
    {NULL, -1, PRESET_LEVEL, PRESET_POSITION,  misc_group, G_N_ELEMENTS(misc_group)},
    {NULL, -1, PRESET_LEVEL, PRESET_POSITION,  pre_fx_group, G_N_ELEMENTS(pre_fx_group)},
    {NULL, -1, PRESET_LEVEL, PRESET_POSITION,  post_fx_group, G_N_ELEMENTS(post_fx_group)},
};

static Effect pickup_effect[] = {
    {NULL, PICKUP_ON_OFF, PICKUP_TYPE, PICKUP_POSITION, pickup_group, G_N_ELEMENTS(pickup_group)},
};

static Effect gnx3k_amp_channel_effect[] = {
    {NULL, -1, -1, -1, gnx3k_amp_channel_group, G_N_ELEMENTS(gnx3k_amp_channel_group)},
};

static Effect tone_lib_effect_a[] = {
    {NULL, -1, TONE_LIB_TYPE, LIB_POSITION_A, tone_lib_group, G_N_ELEMENTS(tone_lib_group)},
    {NULL, -1, FX_LIB_TYPE, LIB_POSITION_A, effects_lib_group, G_N_ELEMENTS(effects_lib_group)},
    {NULL, -1, FX_LIB_LEVEL, LIB_POSITION_A, tone_lib_level_a_group, G_N_ELEMENTS(tone_lib_level_a_group)},
};

static Effect tone_lib_effect_b[] = {
    {NULL, -1, TONE_LIB_TYPE, LIB_POSITION_B, tone_lib_group, G_N_ELEMENTS(tone_lib_group)},
    {NULL, -1, FX_LIB_TYPE, LIB_POSITION_B, effects_lib_group, G_N_ELEMENTS(effects_lib_group)},
    {NULL, -1, FX_LIB_LEVEL, LIB_POSITION_B, tone_lib_level_b_group, G_N_ELEMENTS(tone_lib_level_b_group)},
};

/* in signal chain order */
static EffectList rp150_effects[] = {
    {"Pickup", pickup_misc_effect, G_N_ELEMENTS(pickup_misc_effect)},
    {"Wah", wah_effect, G_N_ELEMENTS(wah_effect)},
    {"Compressor", rp250_comp_effect, G_N_ELEMENTS(rp250_comp_effect)},
    {"Distortion", rp150_dist_effect, G_N_ELEMENTS(rp150_dist_effect)},
    {"Amplifier", rp150_amp_effect, G_N_ELEMENTS(rp150_amp_effect)},
    {"Equalizer", rp250_eq_effect, G_N_ELEMENTS(rp250_eq_effect)},
    {"Noisegate", noisegate_effect, G_N_ELEMENTS(noisegate_effect)},
    {"Chorus/FX", rp150_chorusfx_effect, G_N_ELEMENTS(rp150_chorusfx_effect)},
    {"Delay", rp250_delay_effect, G_N_ELEMENTS(rp250_delay_effect)},
    {"Reverb", reverb_effect, G_N_ELEMENTS(reverb_effect)},
};

static EffectList rp155_effects[] = {
    {"Pickup", pickup_misc_effect, G_N_ELEMENTS(pickup_misc_effect)},
    {"Wah", wah_effect, G_N_ELEMENTS(wah_effect)},
    {"Compressor", rp250_comp_effect, G_N_ELEMENTS(rp250_comp_effect)},
    {"Distortion", rp155_dist_effect, G_N_ELEMENTS(rp155_dist_effect)},
    {"Amplifier", rp155_amp_effect, G_N_ELEMENTS(rp155_amp_effect)},
    {"Equalizer", rp250_eq_effect, G_N_ELEMENTS(rp250_eq_effect)},
    {"Noisegate", noisegate_effect, G_N_ELEMENTS(noisegate_effect)},
    {"Chorus/FX", rp150_chorusfx_effect, G_N_ELEMENTS(rp150_chorusfx_effect)},
    {"Delay", rp250_delay_effect, G_N_ELEMENTS(rp250_delay_effect)},
    {"Reverb", reverb_effect, G_N_ELEMENTS(reverb_effect)},
};

static EffectList rp250_effects[] = {
    {"Wah", wah_effect, G_N_ELEMENTS(wah_effect)},
    {"Amplifier", rp250_amp_effect, G_N_ELEMENTS(rp250_amp_effect)},
    {"Equalizer", rp250_eq_effect, G_N_ELEMENTS(rp250_eq_effect)},
    {"Compressor", rp250_comp_effect, G_N_ELEMENTS(rp250_comp_effect)},
    {"Distortion", rp250_dist_effect, G_N_ELEMENTS(rp250_dist_effect)},
    {"Noisegate", noisegate_effect, G_N_ELEMENTS(noisegate_effect)},
    {"Chorus/FX", rp250_chorusfx_effect, G_N_ELEMENTS(rp250_chorusfx_effect)},
    {"Delay", rp250_delay_effect, G_N_ELEMENTS(rp250_delay_effect)},
    {"Reverb", reverb_effect, G_N_ELEMENTS(reverb_effect)},
    {"Pickup/Misc", pickup_misc_effect, G_N_ELEMENTS(pickup_misc_effect)},
    {"Expression Pedal", expression_pedal_assign_effect, G_N_ELEMENTS(expression_pedal_assign_effect)},
};

/* Almost like rp250, except for Amplifier and Chorus/FX */
static EffectList rp255_effects[] = {
    {"Tone Library", tone_lib_effect_b, G_N_ELEMENTS(tone_lib_effect_b)},
    {"Wah", wah_effect, G_N_ELEMENTS(wah_effect)},
    {"Amplifier", rp255_amp_effect, G_N_ELEMENTS(rp255_amp_effect)},
    {"Equalizer", rp250_eq_effect, G_N_ELEMENTS(rp250_eq_effect)},
    {"Compressor", rp250_comp_effect, G_N_ELEMENTS(rp250_comp_effect)},
    {"Distortion", rp250_dist_effect, G_N_ELEMENTS(rp250_dist_effect)},
    {"Noisegate", noisegate_effect, G_N_ELEMENTS(noisegate_effect)},
    {"Chorus/FX", rp255_chorusfx_effect, G_N_ELEMENTS(rp255_chorusfx_effect)},
    {"Delay", rp250_delay_effect, G_N_ELEMENTS(rp250_delay_effect)},
    {"Reverb", reverb_effect, G_N_ELEMENTS(reverb_effect)},
    {"Pickup/Misc", pickup_misc_effect, G_N_ELEMENTS(pickup_misc_effect)},
    {"Expression Pedal", expression_pedal_assign_effect, G_N_ELEMENTS(expression_pedal_assign_effect)},
};

static EffectList rp355_effects[] = {
    {"Pickup/Misc", pickup_misc_effect, G_N_ELEMENTS(pickup_misc_effect)},
    {"Wah", wah_effect, G_N_ELEMENTS(wah_effect)},
    {"Compressor", rp355_comp_effect, G_N_ELEMENTS(rp355_comp_effect)},
    {"Distortion", rp355_dist_effect, G_N_ELEMENTS(rp355_dist_effect)},
    {"Select Amp", rp355_select_amp_effect, G_N_ELEMENTS(rp355_select_amp_effect)},
    {"Amplifier A", rp355_amp_effect_A, G_N_ELEMENTS(rp355_amp_effect_A)},
    {"Equalizer A", rp355_eq_effect_A, G_N_ELEMENTS(rp355_eq_effect_A)},
    {"Amplifier B", rp355_amp_effect_B, G_N_ELEMENTS(rp355_amp_effect_B)},
    {"Equalizer B", rp355_eq_effect_B, G_N_ELEMENTS(rp355_eq_effect_B)},
    {"Noisegate", noisegate_effect, G_N_ELEMENTS(noisegate_effect)},
    {"Chorus/FX", rp355_chorusfx_effect, G_N_ELEMENTS(rp355_chorusfx_effect)},
    {"Delay", rp355_delay_effect, G_N_ELEMENTS(rp355_delay_effect)},
    {"Reverb", reverb_effect, G_N_ELEMENTS(reverb_effect)},
    {"Pedal1 Assign", expression_pedal_assign_effect, G_N_ELEMENTS(expression_pedal_assign_effect)},
    {"LFO1", rp355_lfo1_effect, G_N_ELEMENTS(rp355_lfo1_effect)},
    {"LFO2", rp355_lfo2_effect, G_N_ELEMENTS(rp355_lfo2_effect)},
    {"Global Settings", global_effect, G_N_ELEMENTS(global_effect)},
    {"Tone Library", tone_lib_effect_a, G_N_ELEMENTS(tone_lib_effect_a)},
};

static EffectList rp500_effects[] = {
    {"Wah", wah_effect, G_N_ELEMENTS(wah_effect)},
    {"Amplifier", rp500_amp_effect, G_N_ELEMENTS(rp500_amp_effect)},
    {"Equalizer", rp500_eq_effect, G_N_ELEMENTS(rp500_eq_effect)},
    {"Compressor", rp500_comp_effect, G_N_ELEMENTS(rp500_comp_effect)},
    {"Distortion", rp500_dist_effect, G_N_ELEMENTS(rp500_dist_effect)},
    {"Noisegate", noisegate_effect, G_N_ELEMENTS(noisegate_effect)},
    {"Chorus/FX", rp500_chorusfx_effect, G_N_ELEMENTS(rp500_chorusfx_effect)},
    {"Delay", rp500_delay_effect, G_N_ELEMENTS(rp500_delay_effect)},
    {"Reverb", reverb_effect, G_N_ELEMENTS(reverb_effect)},
    {"Expression Pedal", expression_pedal_assign_effect, G_N_ELEMENTS(expression_pedal_assign_effect)},
};

static EffectList rp1000_effects[] = {
    {"Wah", wah_effect, G_N_ELEMENTS(wah_effect)},
    {"Amplifier", rp1000_amp_effect, G_N_ELEMENTS(rp1000_amp_effect)},
    {"Equalizer", rp500_eq_effect, G_N_ELEMENTS(rp500_eq_effect)},
    {"Compressor", rp500_comp_effect, G_N_ELEMENTS(rp500_comp_effect)},
    {"Distortion", rp1000_dist_effect, G_N_ELEMENTS(rp1000_dist_effect)},
    {"Noisegate", noisegate_effect, G_N_ELEMENTS(noisegate_effect)},
    {"Chorus/FX", rp1000_chorusfx_effect, G_N_ELEMENTS(rp1000_chorusfx_effect)},
    {"Delay", rp1000_delay_effect, G_N_ELEMENTS(rp1000_delay_effect)},
    {"Reverb", reverb_effect, G_N_ELEMENTS(reverb_effect)},
    {"Expression Pedal", expression_pedal_assign_effect, G_N_ELEMENTS(expression_pedal_assign_effect)},
};

static EffectList gnx4_effects[] = {
    {"Pickup", pickup_effect, G_N_ELEMENTS(pickup_effect)},
    {"Wah", gnx3k_wah_effect, G_N_ELEMENTS(gnx3k_wah_effect)},
    {"Compressor", gnx_comp_effect, G_N_ELEMENTS(gnx_comp_effect)},
    {"Whammy/IPS", gnx3k_whammy_effect, G_N_ELEMENTS(gnx3k_whammy_effect)},
    {"Stompbox", gnx4_dist_effect, G_N_ELEMENTS(gnx4_dist_effect)},
    {"Noisegate", gnx3k_noisegate_effect, G_N_ELEMENTS(gnx3k_noisegate_effect)},
    {"Chorus/Mod", gnx4_chorusfx_effect, G_N_ELEMENTS(gnx4_chorusfx_effect)},
    {"Delay", gnx3k_delay_effect, G_N_ELEMENTS(gnx3k_delay_effect)},
    {"Reverb", gnx3k_reverb_effect, G_N_ELEMENTS(gnx3k_reverb_effect)},
};

static EffectList gnx3000_effects[] = {
    {"Pickup", pickup_effect, G_N_ELEMENTS(pickup_effect)},
    {"Wah", gnx3k_wah_effect, G_N_ELEMENTS(gnx3k_wah_effect)},
    {"Whammy/IPS", gnx3k_whammy_effect, G_N_ELEMENTS(gnx3k_whammy_effect)},
    {"Preset Level", gnx3k_preset_effect, G_N_ELEMENTS(gnx3k_preset_effect)},
    {"Compressor", gnx_comp_effect, G_N_ELEMENTS(gnx_comp_effect)},
    {"Stompbox", gnx3k_dist_effect, G_N_ELEMENTS(gnx3k_dist_effect)},
    {"Noisegate", gnx3k_noisegate_effect, G_N_ELEMENTS(gnx3k_noisegate_effect)},
    {"Chorus/Mod", gnx3k_chorusfx_effect, G_N_ELEMENTS(gnx3k_chorusfx_effect)},
    {"Delay", gnx3k_delay_effect, G_N_ELEMENTS(gnx3k_delay_effect)},
    {"Reverb", gnx3k_reverb_effect, G_N_ELEMENTS(gnx3k_reverb_effect)},
};

static EffectList gnx3000_genetx[] = {
    {"Channel 1", gnx3k_channel_1_effect, G_N_ELEMENTS(gnx3k_channel_1_effect)},
    {"Channel 2", gnx3k_channel_2_effect, G_N_ELEMENTS(gnx3k_channel_2_effect)},
    {"Amp Channel", gnx3k_amp_channel_effect, G_N_ELEMENTS(gnx3k_amp_channel_effect)},
};

static Banks rp_banks[] = {
    {"User Presets", PRESETS_USER},
    {"System Presets", PRESETS_SYSTEM},
};

static Banks gnx4_banks[] = {
    {"Factory", PRESETS_SYSTEM},
    {"User Presets", PRESETS_USER},
    {"Flash Card", PRESETS_MEDIA_CARD},
};

static Banks gnx3k_banks[] = {
    {"User Presets", PRESETS_USER},
    {"Factory 1", PRESETS_SYSTEM},
    {"Factory 2", PRESETS_FACTORY2},
};

static EffectPage rp150_pages[] = {
    {"Effects", rp150_effects, G_N_ELEMENTS(rp150_effects), 2},
};

static EffectPage rp155_pages[] = {
    {"Effects", rp155_effects, G_N_ELEMENTS(rp155_effects), 2},
};

static EffectPage rp250_pages[] = {
    {"Effects", rp250_effects, G_N_ELEMENTS(rp250_effects), 2},
};

static EffectPage rp255_pages[] = {
    {"Effects", rp255_effects, G_N_ELEMENTS(rp255_effects), 2},
};

static EffectPage rp355_pages[] = {
    {"Effects", rp355_effects, G_N_ELEMENTS(rp355_effects), 3},
};

static EffectPage rp500_pages[] = {
    {"Effects", rp500_effects, G_N_ELEMENTS(rp500_effects), 2},
};

static EffectPage rp1000_pages[] = {
    {"Effects", rp1000_effects, G_N_ELEMENTS(rp1000_effects), 2},
};

static EffectPage gnx4_pages[] = {
    {"Effects", gnx4_effects, G_N_ELEMENTS(gnx4_effects), 2},
};

static EffectPage gnx3000_pages[] = {
    {"Effects", gnx3000_effects, G_N_ELEMENTS(gnx3000_effects), 2},
    {"Amp/GeNetX", gnx3000_genetx, G_N_ELEMENTS(gnx3000_genetx), 1},
};

static Device rp150 = {
    .name = "DigiTech RP150",
    .family_id = 0x5E,
    .product_id = 0x01,
    .pages = rp150_pages,
    .n_pages = G_N_ELEMENTS(rp150_pages),
    .banks = rp_banks,
    .n_banks = G_N_ELEMENTS(rp_banks),
};

static Device rp155 = {
    .name = "DigiTech RP155",
    .family_id = 0x5E,
    .product_id = 0x07,
    .pages = rp155_pages,
    .n_pages = G_N_ELEMENTS(rp155_pages),
    .banks = rp_banks,
    .n_banks = G_N_ELEMENTS(rp_banks),
};

static Device rp250 = {
    .name = "DigiTech RP250",
    .family_id = 0x5E,
    .product_id = 0x02,
    .pages = rp250_pages,
    .n_pages = G_N_ELEMENTS(rp250_pages),
    .banks = rp_banks,
    .n_banks = G_N_ELEMENTS(rp_banks),
};

static Device rp255 = {
    .name = "DigiTech RP255",
    .family_id = 0x5E,
    .product_id = 0x08,
    .pages = rp255_pages,
    .n_pages = G_N_ELEMENTS(rp255_pages),
    .banks = rp_banks,
    .n_banks = G_N_ELEMENTS(rp_banks),
};

static Device rp355 = {
    .name = "DigiTech RP355",
    .family_id = 0x5E,
    .product_id = 0x09,
    .pages = rp355_pages,
    .n_pages = G_N_ELEMENTS(rp355_pages),
    .banks = rp_banks,
    .n_banks = G_N_ELEMENTS(rp_banks),
};

static Device rp500 = {
    .name = "DigiTech RP500",
    .family_id = 0x5E,
    .product_id = 0x05,
    .pages = rp500_pages,
    .n_pages = G_N_ELEMENTS(rp500_pages),
    .banks = rp_banks,
    .n_banks = G_N_ELEMENTS(rp_banks),
};

static Device rp1000 = {
    .name = "DigiTech RP1000",
    .family_id = 0x05E,
    .product_id = 0x06,
    .pages = rp1000_pages,
    .n_pages = G_N_ELEMENTS(rp1000_pages),
    .banks = rp_banks,
    .n_banks = G_N_ELEMENTS(rp_banks),
};

static Device gnx4 = {
    .name = "DigiTech GNX4",
    .family_id = 0x5C,
    .product_id = 0x03,
    .pages = gnx4_pages,
    .n_pages = G_N_ELEMENTS(gnx4_pages),
    .banks = gnx4_banks,
    .n_banks = G_N_ELEMENTS(gnx4_banks),
};

static Device gnx3000 = {
    .name = "DigiTech GNX3000",
    .family_id = 0x5C,
    .product_id = 0x04,
    .pages = gnx3000_pages,
    .n_pages = G_N_ELEMENTS(gnx3000_pages),
    .banks = gnx3k_banks,
    .n_banks = G_N_ELEMENTS(gnx3k_banks),
};

Device* supported_devices[] = {
    &rp150,
    &rp155,
    &rp250,
    &rp255,
    &rp355,
    &rp500,
    &rp1000,
    &gnx4,
    &gnx3000,
};

int n_supported_devices = G_N_ELEMENTS(supported_devices);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

typedef struct {
    gchar *label;
    guint id;
    guint position;
    EffectValues *values;
} Modifier;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

static Modifier modifiers[] = {
    {"None", 0, 0, NULL},
    {"Pickup Enable", PICKUP_ON_OFF, PICKUP_POSITION, &values_on_off},
    {"Pickup Type", PICKUP_TYPE, PICKUP_POSITION, &values_pickup_type},
    {"Compressor Enable", COMP_ON_OFF, COMP_POSITION, &values_on_off},
    {"Compressor Sustain", COMP_SUSTAIN, COMP_POSITION, &values_0_to_99},
    {"Compressor Tone", COMP_TONE, COMP_POSITION, &values_0_to_99},
    {"Compressor Level", COMP_LEVEL, COMP_POSITION, &values_0_to_99},
    {"Compressor Attack", COMP_ATTACK, COMP_POSITION, &values_0_to_99},
    {"Compressor Sensitivity", COMP_SENSITIVITY, COMP_POSITION, &values_0_to_99},
    {"Compressor Output", COMP_OUTPUT, COMP_POSITION, &values_0_to_99},
    {"Dist Enable", DIST_ON_OFF, DIST_POSITION, &values_on_off},
    {"Dist Drive", DIST_SCREAMER_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Dist Tone", DIST_SCREAMER_TONE, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_SCREAMER_LVL, DIST_POSITION, &values_0_to_99},
    {"Dist Overdrive", DIST_808_OVERDRIVE, DIST_POSITION, &values_0_to_99},
    {"Dist Tone", DIST_808_TONE, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_808_LVL, DIST_POSITION, &values_0_to_99},
    {"Dist Drive", DIST_TS_MOD_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Dist Tone", DIST_TS_MOD_TONE, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_TS_MOD_LVL, DIST_POSITION, &values_0_to_99},
    {"Dist Drive", DIST_SD_ODRV_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Dist Tone", DIST_SD_ODRV_TONE, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_SD_ODRV_LVL, DIST_POSITION, &values_0_to_99},
    {"Dist Overdrive", DIST_OD_ODRV_OVERDRIVE, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_OD_ODRV_LVL, DIST_POSITION, &values_0_to_99}, 
    {"Dist Gain", DIST_SPARKDRIVE_GAIN, DIST_POSITION, &values_0_to_99},
    {"Dist Tone", DIST_SPARKDRIVE_TONE, DIST_POSITION, &values_0_to_99},
    {"Dist Clean", DIST_SPARKDRIVE_CLEAN, DIST_POSITION, &values_0_to_99},
    {"Dist Volume", DIST_SPARKDRIVE_VOLUME, DIST_POSITION, &values_0_to_99},
    {"Dist Drive", DIST_GUYOD_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_GUYOD_LVL, DIST_POSITION, &values_0_to_99},
    {"Dist Gain", DIST_DOD250_GAIN, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_DOD250_LVL, DIST_POSITION, &values_0_to_99},
    {"Dist Gain", DIST_REDLINE_GAIN, DIST_POSITION, &values_0_to_99},
    {"Dist Low", DIST_REDLINE_LOW, DIST_POSITION, &values_0_to_99},
    {"Dist High", DIST_REDLINE_HIGH, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_REDLINE_LEVEL, DIST_POSITION, &values_0_to_99},
    {"Dist Gain", DIST_AMPDRIVR_GAIN, DIST_POSITION, &values_0_to_99},
    {"Dist Mid Boost", DIST_AMPDRIVR_MIDBOOST, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_AMPDRIVR_LVL, DIST_POSITION, &values_0_to_99},    
    {"Dist Drive", DIST_OC_DRIVE_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Dist Tone", DIST_OC_DRIVE_TONE, DIST_POSITION, &values_0_to_99},
    {"Dist HP/LP", DIST_OC_DRIVE_HP_LP, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_OC_DRIVE_LVL, DIST_POSITION, &values_0_to_99},
    {"Dist Distortion", DIST_RODENT_DIST, DIST_POSITION, &values_0_to_99},
    {"Dist Filter", DIST_RODENT_FILTER, DIST_POSITION, &values_0_to_99},
    {"Dist Volume", DIST_RODENT_LVL, DIST_POSITION, &values_0_to_99},
    {"Dist Distortion", DIST_MX_DIST, DIST_POSITION, &values_0_to_99},
    {"Dist Output", DIST_MX_OUTPUT, DIST_POSITION, &values_0_to_99},
    {"Dist Distortion", DIST_DS_GAIN, DIST_POSITION, &values_0_to_99},
    {"Dist Tone", DIST_DS_TONE, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_DS_LVL, DIST_POSITION, &values_0_to_99},
    {"Dist Gain", DIST_GRUNGE_GRUNGE, DIST_POSITION, &values_0_to_99},
    {"Dist Face", DIST_GRUNGE_FACE, DIST_POSITION, &values_0_to_99},
    {"Dist Loud", DIST_GRUNGE_LOUD, DIST_POSITION, &values_0_to_99},
    {"Dist Butt", DIST_GRUNGE_BUTT, DIST_POSITION, &values_0_to_99},
    {"Dist Gain", DIST_ZONE_GAIN, DIST_POSITION, &values_0_to_99},
    {"Dist Mid Level", DIST_ZONE_MID_LVL, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_ZONE_LEVEL, DIST_POSITION, &values_0_to_99},
    {"Dist Low", DIST_ZONE_LOW, DIST_POSITION, &values_0_to_99},
    {"Dist Mid Freq", DIST_ZONE_MID_FREQ, DIST_POSITION, &values_0_to_99},
    {"Dist High", DIST_ZONE_HIGH, DIST_POSITION, &values_0_to_99},
    {"Dist Low", DIST_DEATH_LOW, DIST_POSITION, &values_0_to_99},
    {"Dist Mid", DIST_DEATH_MID, DIST_POSITION, &values_0_to_99},
    {"Dist Level", DIST_DEATH_LVL, DIST_POSITION, &values_0_to_99},
    {"Dist High", DIST_DEATH_HIGH, DIST_POSITION, &values_0_to_99},
    {"Dist Gunk", DIST_GONK_GONK, DIST_POSITION, &values_0_to_99},
    {"Dist Smear", DIST_GONK_SMEAR, DIST_POSITION, &values_0_to_99},
    {"Dist Suck", DIST_GONK_SUCK, DIST_POSITION, &values_0_to_99},
    {"Dist Heave", DIST_GONK_HEAVE, DIST_POSITION, &values_0_to_99},
    {"Dist Drive", DIST_8TAVIA_DRIVE, DIST_POSITION, &values_0_to_99},
    {"Dist Volume", DIST_8TAVIA_VOLUME, DIST_POSITION, &values_0_to_99},
    {"Dist Fuzz", DIST_FUZZLATOR_FUZZ, DIST_POSITION, &values_0_to_99},
    {"Dist Tone", DIST_FUZZLATOR_TONE, DIST_POSITION, &values_0_to_99},
    {"Dist Loose/Tight", DIST_FUZZLATOR_LOOSETIGHT, DIST_POSITION, &values_0_to_99},
    {"Dist Volume", DIST_FUZZLATOR_VOLUME, DIST_POSITION, &values_0_to_99},
    {"Dist Fuzz", DIST_CLASSIC_FUZZ_FUZZ, DIST_POSITION, &values_0_to_99},
    {"Dist Tone", DIST_CLASSIC_FUZZ_TONE, DIST_POSITION, &values_0_to_99},
    {"Dist Volume", DIST_CLASSIC_FUZZ_VOLUME, DIST_POSITION, &values_0_to_99},
    {"Dist Fuzz", DIST_FUZZY_FUZZ, DIST_POSITION, &values_0_to_99},
    {"Dist Volume", DIST_FUZZY_VOLUME, DIST_POSITION, &values_0_to_99},
    {"Dist Sustain", DIST_MP_SUSTAIN, DIST_POSITION, &values_0_to_99},
    {"Dist Tone", DIST_MP_TONE, DIST_POSITION, &values_0_to_99},
    {"Dist Volume", DIST_MP_VOLUME, DIST_POSITION, &values_0_to_99},
    {"Amp Enable", AMP_ON_OFF, AMP_A_POSITION, &values_on_off},
    {"Amp Gain", AMP_GAIN, AMP_A_POSITION, &values_0_to_99},
    {"Amp Level", AMP_LEVEL, AMP_A_POSITION, &values_0_to_99},

    {"Bass", AMP_BASS, AMP_A_POSITION, &values_1_to_10_step_0p1},
    {"Mid", AMP_MID, AMP_A_POSITION, &values_1_to_10_step_0p1},
    {"Treble", AMP_TREBLE, AMP_A_POSITION, &values_1_to_10_step_0p1},
 
    {"Amp B Enable", AMP_ON_OFF, AMP_B_POSITION, &values_on_off},
    {"Amp B Gain", AMP_GAIN, AMP_B_POSITION, &values_0_to_99},
    {"Amp B Level", AMP_LEVEL, AMP_B_POSITION, &values_0_to_99},
    {"EQ Enable", EQ_ENABLE, EQ_A_POSITION, &values_on_off},
    {"EQ Bass", EQ_BASS, EQ_A_POSITION, &values_eq_db},
    {"EQ Mid", EQ_MID, EQ_A_POSITION, &values_eq_db},
    {"EQ Treb", EQ_TREB, EQ_A_POSITION, &values_eq_db},
    {"EQ Presence", EQ_PRESENCE, EQ_A_POSITION, &values_eq_db},

    {"Low Freq", EQ_LOW_FREQ, EQ_A_POSITION, &values_eq_low_freq},
    {"Mid Freq", EQ_MID_FREQ_RP500, EQ_A_POSITION, &values_eq_mid_freq},
    {"High Freq", EQ_HIGH_FREQ, EQ_A_POSITION, &values_eq_high_freq},

    {"EQ B Enable", EQ_ENABLE, EQ_B_POSITION, &values_on_off},
    {"EQ B Bass", EQ_BASS, EQ_B_POSITION, &values_eq_db},
    {"EQ B Mid", EQ_MID, EQ_B_POSITION, &values_eq_db},
    {"EQ B Treb", EQ_TREB, EQ_B_POSITION, &values_eq_db},
    {"EQ B Presence", EQ_PRESENCE, EQ_B_POSITION, &values_eq_db},
    {"Gate Enable", NOISEGATE_ON_OFF, NOISEGATE_POSITION, &values_on_off},
    {"Gate Pluck Sens", NOISEGATE_SWELL_SENS, NOISEGATE_POSITION, &values_0_to_99},
    {"Gate Threshold", NOISEGATE_GATE_TRESHOLD, NOISEGATE_POSITION, &values_0_to_99},
    {"Gate Attack", NOISEGATE_ATTACK, NOISEGATE_POSITION, &values_0_to_99},
    {"Gate Release", NOISEGATE_RELEASE, NOISEGATE_POSITION, &values_0_to_99},
    {"Gate Attenuation", NOISEGATE_ATTN, NOISEGATE_POSITION, &values_0_to_99},
    {"Chorus/FX Enable", CHORUSFX_ON_OFF, CHORUSFX_POSITION, &values_on_off},
    {"Phaser Speed", PHASER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Phaser Depth", PHASER_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Phaser Regen", PHASER_REGEN, CHORUSFX_POSITION, &values_0_to_99},
    {"Phaser Waveform", PHASER_WAVE, CHORUSFX_POSITION, &values_waveform},
    {"Phaser Level", PHASER_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
    {"Phaser Intensity", MX_PHASER_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Trig Phaser Speed", TRIG_PHASER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Trig Phaser Sens", TRIG_PHASER_SENS, CHORUSFX_POSITION, &values_0_to_99},
    {"Trig Phaser LFO", TRIG_PHASER_LFO_START, CHORUSFX_POSITION, &values_0_to_99},
    {"Trig Phaser Level", TRIG_PHASER_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
    {"EH Phaser Rate", EH_PHASER_RATE, CHORUSFX_POSITION, &values_0_to_99},
    {"EH Phaser Color", EH_PHASER_COLOR, CHORUSFX_POSITION, &values_on_off},
    {"Chorus Speed", CHORUS_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Chorus Depth", CHORUS_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Chorus Level", CHORUS_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
    {"Chorus Waveform", CHORUS_WAVE, CHORUSFX_POSITION, &values_waveform},
    {"Chorus Width", CHORUS_WIDTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Chorus Intensity", CHORUS_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Chorus Rate", CHORUS_RATE, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Speed", FLANGER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Depth", FLANGER_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Regen", FLANGER_REGEN, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Waveform", FLANGER_WAVE, CHORUSFX_POSITION, &values_waveform},
    {"Flanger Level", FLANGER_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Width", MXR_FLANGER_WIDTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Manual", MXR_FLANGER_MANUAL, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Level", TRIG_FLANGER_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Sens", TRIG_FLANGER_SENS, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger LFO Start", TRIG_FLANGER_LFO_START, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Speed", TRIG_FLANGER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Range", EH_FLANGER_RANGE, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Rate", EH_FLANGER_RATE, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Color", EH_FLANGER_COLOR, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Enhance", AD_FLANGER_ENHANCE, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Harmonics", AD_FLANGER_HARMONICS, CHORUSFX_POSITION, &values_0_to_99},
    {"Flanger Frequency", FLTFLANGER_FREQ, CHORUSFX_POSITION, &values_0_to_99},
    {"Vibrato Speed", VIBRATO_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Vibrato Depth", VIBRATO_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Rotary Speed", ROTARY_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Rotary Intensity", ROTARY_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Rotary Doppler", ROTARY_DOPPLER, CHORUSFX_POSITION, &values_0_to_99},
    {"Rotary Crossover", ROTARY_CROSSOVER, CHORUSFX_POSITION, &values_0_to_99},
    {"VibroPan Speed", VIBROPAN_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"VibroPan Depth", VIBROPAN_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"VibroPan VibratoPan", VIBROPAN_VIBRA, CHORUSFX_POSITION, &values_0_to_99},
    {"VibroPan Waveform", VIBROPAN_WAVE, CHORUSFX_POSITION, &values_waveform},
    {"Unovibe Speed", UNOVIBE_PEDAL_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Unovibe Intensity", UNOVIBE_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Unovibe Volume", UNOVIBE_VOLUME, CHORUSFX_POSITION, &values_0_to_99},
    {"Unovibe Chorus/Vibrato", UNOVIBE_CHORUS_VIBRATO, CHORUSFX_POSITION, &values_chorus_vibrato},
    {"Tremolo Speed", TREMOLO_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Tremolo Depth", TREMOLO_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Tremolo Waveform", TREMOLO_WAVE, CHORUSFX_POSITION, &values_waveform},
    {"Panner Speed", PANNER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Panner Depth", PANNER_DEPTH, CHORUSFX_POSITION, &values_0_to_99},
    {"Panner Waveform", PANNER_WAVE, CHORUSFX_POSITION, &values_waveform},
    {"Envelope Sens.", ENVELOPE_SENSITIVITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Envelope Range", ENVELOPE_RANGE, CHORUSFX_POSITION, &values_0_to_99},
    {"Envelope Blend", ENVELOPE_BLEND, CHORUSFX_POSITION, &values_0_to_99},
    {"AutoYa Speed", AUTOYA_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"AutoYa Intensity", AUTOYA_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"AutoYa Range", AUTOYA_RANGE, CHORUSFX_POSITION, &values_0_to_49},
    {"YaYa Pedal", YAYA_PEDAL, CHORUSFX_POSITION, &values_0_to_99},
    {"YaYa Intensity", YAYA_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"YaYa Range", YAYA_RANGE, CHORUSFX_POSITION, &values_0_to_49},
    {"Step Filter Speed", STEP_FILTER_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Step Filter Intensity", STEP_FILTER_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Sample Hold Speed", SAMPLE_HOLD_SPEED, CHORUSFX_POSITION, &values_0_to_99},
    {"Sample Hold Intensity", SAMPLE_HOLD_INTENSITY, CHORUSFX_POSITION, &values_0_to_99},
    {"Synth Talk Attack", SYNTH_TALK_ATTACK, CHORUSFX_POSITION, &values_0_to_99},
    {"Synth Talk Release", SYNTH_TALK_RELEASE, CHORUSFX_POSITION, &values_0_to_99},
    {"Synth Talk Sens", SYNTH_TALK_SENS, CHORUSFX_POSITION, &values_0_to_99},
    {"Synth Talk Vox", SYNTH_TALK_VOX, CHORUSFX_POSITION, &values_0_to_99},
    {"Synth Talk Balance", SYNTH_TALK_BALANCE, CHORUSFX_POSITION, &values_balance},
    {"Whammy Amount", WHAMMY_AMOUNT, CHORUSFX_POSITION, &values_whammy_amount},
    {"Whammy Pedal", WHAMMY_PEDAL, CHORUSFX_POSITION, &values_0_to_99},
    {"Whammy Mix", WHAMMY_MIX, CHORUSFX_POSITION, &values_0_to_99},
    {"Pitch Shift Amount", PITCH_AMOUNT, CHORUSFX_POSITION, &values_m24_to_24},
    {"Pitch Shift Mix", PITCH_MIX, CHORUSFX_POSITION, &values_0_to_99},
    {"Detune Amount", DETUNE_AMOUNT, CHORUSFX_POSITION, &values_m24_to_24},
    {"Detune Level", DETUNE_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
    {"IPS Amount", IPS_SHIFT_AMOUNT, CHORUSFX_POSITION, &values_ips_shift},
    {"IPS Key", IPS_KEY, CHORUSFX_POSITION, &values_ips_key},
    {"IPS Scale", IPS_SCALE, CHORUSFX_POSITION, &values_ips_scale},
    {"IPS Level", IPS_LEVEL, CHORUSFX_POSITION, &values_0_to_99},
    {"Octaver Octave 1", OCTAVER_OCTAVE1, CHORUSFX_POSITION, &values_0_to_99},
    {"Octaver Octave 2", OCTAVER_OCTAVE2, CHORUSFX_POSITION, &values_0_to_99},
    {"Octaver Dry Level", OCTAVER_DRY_LEVEL, CHORUSFX_POSITION, &values_0_to_99},

    {"Delay Enable", DELAY_ON_OFF, DELAY_POSITION, &values_on_off},
    {"Delay Time", DELAY_TIME, DELAY_POSITION, &values_delay_time},
    {"Delay Repeats", DELAY_REPEATS, DELAY_POSITION, &values_delay_repeats},
    {"Delay Repeats", DELAY_REPEATS_0_99, DELAY_POSITION, &values_delay_repeats},
    {"Delay Level", DELAY_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Delay Volume", DELAY_VOLUME, DELAY_POSITION, &values_0_to_99},
    {"Delay Mix", DELAY_MIX, DELAY_POSITION, &values_0_to_99},
    {"Delay Tap Ratio", DELAY_TAP_RATIO, DELAY_POSITION, &values_0_to_99},
    {"Delay Duck Thresh", DELAY_DUCK_THRESH, DELAY_POSITION, &values_0_to_99},
    {"Delay Duck Level", DELAY_DUCK_LEVEL, DELAY_POSITION, &values_0_to_99},
    {"Delay Mod Depth", DELAY_DEPTH, DELAY_POSITION, &values_0_to_99},
    {"Delay Tape Wow", DELAY_TAPE_WOW, DELAY_POSITION, &values_0_to_99},
    {"Delay Tape Flut", DELAY_TAPE_FLUTTER, DELAY_POSITION, &values_0_to_99},
    {"Reverb Enable", REVERB_ON_OFF, REVERB_POSITION, &values_on_off},
    {"Reverb Decay", REVERB_DECAY, REVERB_POSITION, &values_0_to_99},
    {"Reverb Liveliness", REVERB_LIVELINESS, REVERB_POSITION, &values_0_to_99},
    {"Reverb Level", REVERB_LEVEL, REVERB_POSITION, &values_0_to_99},
    {"Reverb Predelay", REVERB_PREDELAY, REVERB_POSITION, &values_0_to_15},
    {"Volume Pre FX", PRESET_LEVEL, VOLUME_PRE_FX_POSITION, &values_0_to_99},
    {"Volume Post FX", PRESET_LEVEL, VOLUME_POST_FX_POSITION, &values_0_to_99},
    
    {"Delay Intensity", DELAY_INTENSITY, DELAY_POSITION, &values_0_to_99},
    {"Delay Tempo Division", DELAY_MULTIPLIER, DELAY_POSITION, &values_delay_mult},
    {"Delay Echo", DELAY_ECHO, DELAY_POSITION, &values_0_to_99},
    
    {"Amp Loop Enable", AMP_LOOP_ON_OFF, AMP_LOOP_POSITION, &values_on_off},
    {"Stomp Loop Enable", STOMP_LOOP_ON_OFF, STOMP_LOOP_POSITION, &values_0_to_1},
};

int n_modifiers = G_N_ELEMENTS(modifiers);

/*
 * Structures for mapping presets to XML. There's duplication here, but this
 * method is general and device independent.
 */

static XmlLabel xml_on_off_labels[] = {
    {0, "Off"},
    {1, "On"},
};

static XmlLabel xml_pickup_labels[] = {
    {PICKUP_TYPE_HB_SC, "HB>SC"},
    {PICKUP_TYPE_SC_HB, "SC>HB"},
};

static XmlLabel xml_comp_labels[] = {
    {COMP_TYPE_DIGI, "Digi Comp"},
    {COMP_TYPE_CS, "CS Comp"},
    {COMP_TYPE_DYNA, "Dyna Comp"},
};

static XmlLabel xml_dist_labels[] = {
    {DIST_TYPE_SCREAMER, "Screamer"},
    {DIST_TYPE_808, "808"},
    {DIST_TYPE_TS_MOD, "TS Mod"},
    {DIST_TYPE_SD_ODRV, "SD Overdrive"},
    {DIST_TYPE_OD_ODRV, "OD Overdrive"},
    {DIST_TYPE_SPARKDRIVE, "Sparkdrive"},
    {DIST_TYPE_GUYOD, "Guy Overdrive"},
    {DIST_TYPE_DOD250, "DOD250"},
    {DIST_TYPE_REDLINE, "Redline"},
    {DIST_TYPE_AMPDRIVR, "Amp Driver"},
    {DIST_TYPE_OC_DRIVE, "OC Drive"},
    {DIST_TYPE_RODENT, "Rodent"},
    {DIST_TYPE_MX, "MX Dist"},
    {DIST_TYPE_DS, "DS Dist"},
    {DIST_TYPE_GRUNGE, "Grunge"},
    {DIST_TYPE_ZONE, "Zone"},
    {DIST_TYPE_DEATH, "Death"},
    {DIST_TYPE_GONK, "Gonk"},
    {DIST_TYPE_8TAVIA, "8tavia"},
    {DIST_TYPE_FUZZLATOR, "Fuzzlator"},
    {DIST_TYPE_CLASSIC_FUZZ, "Classic Fuzz"},
    {DIST_TYPE_FUZZY, "Fuzzy"},
    {DIST_TYPE_MP, "Big Pi"},
};

static XmlLabel xml_amp_channel_labels[] = {
    {AMP_CHANNEL_A, "A"},
    {AMP_CHANNEL_B, "B"},
    {AMP_CHANNEL_WARP, "Warped"},
};

static XmlLabel xml_amp_labels[] = {
    {AMP_TYPE_TWEED_CHAMP, "'57 Tweed Champ\xc2\xae"},
    {AMP_TYPE_TWEED_DELUXE, "Tweed Deluxe"},
    {AMP_TYPE_TWEED_BASSMAN, "Tweed Bassman"},
    {AMP_TYPE_BROWN_BASSMAN, "Brown Bassman"},
    {AMP_TYPE_BLACKFACE_TWIN, "'65 Blackface Twin"},
    {AMP_TYPE_BLACKFACE_DELUXE, "'65Blackface Deluxe\xc2\xae"},
    {AMP_TYPE_PLEXI_JTM_45, "Plexi JTM-45"},
    {AMP_TYPE_SUPER_LEAD_PLEXI, "'68 Plexi Lead 100"},
    {AMP_TYPE_68_MARSHALL_JUMP, "'68 Marshall Jump"},
    {AMP_TYPE_MASTER_VOLUME, "Master Volume"},
    {AMP_TYPE_JCM800, "JCM800"},
    {AMP_TYPE_JCM900, "JCM900"},
    {AMP_TYPE_JCM2000, "JCM2000"},
    {AMP_TYPE_AC15, "AC-15"},
    {AMP_TYPE_AC30TB, "AC-30 TB"},
    {AMP_TYPE_HIWATT_100, "Hiwatt 100"},
    {AMP_TYPE_BOOGIE_MARK_II, "Boogie Mark IIC"},
    {AMP_TYPE_BOOGIE_MARK_IV, "Boogie Mark IV"},
    {AMP_TYPE_DUAL_RECTIFIER, "Dual Rectifier"},
    {AMP_TYPE_TRIPLE_RECTIFIER, "Triple Rectifier"},
    {AMP_TYPE_22_CALIBR, ".22 Caliber"},
    {AMP_TYPE_LEGACY_VL100, "Legacy VL-100"},
    {AMP_TYPE_MATCHLESS_HC30, "Matchless HC30"},
    {AMP_TYPE_CHIEF, "Matchless Chieftan"},
    {AMP_TYPE_SOLDANO_100, "Soldano 100"},
    {AMP_TYPE_SUPERGROUP, "Supergroup"},
    {AMP_TYPE_GA40, "GA-40"},
    {AMP_TYPE_OR120, "OR-120"},
    {AMP_TYPE_PV5150II, "PV 5150II"},
    {AMP_TYPE_RG100, "RG100"},
    {AMP_TYPE_JC120_JAZZ, "JC-120 Jazz"},
    {AMP_TYPE_SOLAR100, "Solar 100"},
    {AMP_TYPE_SOLO, "Solo"},
    {AMP_TYPE_METAL, "Metal"},
    {AMP_TYPE_BRIGHT, "Bright Clean"},
    {AMP_TYPE_CHUNK, "Chunk"},
    {AMP_TYPE_DIGITECH_CLEAN, "DigiTech\xc2\xae Clean"},
    {AMP_TYPE_HIGH_GAIN, "High Gain"},
    {AMP_TYPE_BLUES, "Blues"},
    {AMP_TYPE_FUZZ, "Fuzz"},
    {AMP_TYPE_SPANK, "Spank"},
    {AMP_TYPE_GSP2101_CLEAN_TUBE, "GSP2101 Clean Tube"},
    {AMP_TYPE_GSP2101_SAT_TUBE, "GSP2101 Sat Tube"},
    {AMP_TYPE_CRUNCH, "Crunch"},
    {AMP_TYPE_MONSTER, "Monster"},
    {AMP_TYPE_TWEEDFACE, "Tweedface"},
    {AMP_TYPE_BLACKBASS, "Blackbass"},
    {AMP_TYPE_STONER_ROCK, "Stoner Rock"},
    {AMP_TYPE_DARK_METAL, "Dark Metal"},
    {AMP_TYPE_TRANSISTOR, "Transistor"},
    {AMP_TYPE_BROWN_SOUND, "Brown Sound"},
    {AMP_TYPE_MOSH, "Mosh"},
    {AMP_TYPE_ACOUSTIC, "Dread Acoustic"},
    {AMP_TYPE_JUMBO_ACOUSTIC, "Jumbo Acoustic"},
    {AMP_TYPE_DIRECT, "Direct"},
};

static XmlLabel xml_amp_cab_labels[] = {
    {AMP_CAB_DIRECT, "Direct"},
    {AMP_CAB_CHAMP, "Champ\xc2\xae 1x8"},
    {AMP_CAB_DELUXE, "Deluxe\xc2\xae 1x12"},
    {AMP_CAB_DELUXE_REVERB, "Deluxe Reverb 1x12"},
    {AMP_CAB_BRITISH1_12, "British 1x12"},
    {AMP_CAB_GA1_12, "GA 1x12"},
    {AMP_CAB_BLONDE2_12, "Blonde 2x12"},
    {AMP_CAB_TWIN, "Twin 2x12"},
    {AMP_CAB_BRITISH2_12, "British 2x12"},
    {AMP_CAB_JAZZ2_12, "Jazz 2x12"},
    {AMP_CAB_JBL_215, "JBL/Lansing Enclosure"},
    {AMP_CAB_BASSMAN, "Bassman 4x10"},
    {AMP_CAB_BRITISH4_12, "British 4x12"},
    {AMP_CAB_BRITISH_GREEN, "British Green 4x12"},
    {AMP_CAB_FANE4_12, "Fane 4x12"},
    {AMP_CAB_BOUTIQUE4_12, "Boutique 4x12"},
    {AMP_CAB_VINTAGE, "Vintage 4x12"},
    {AMP_CAB_RECTO4_12, "Recto 4x12"},
    {AMP_CAB_DIGI_SOLO, "DigiTech\xc2\xae Solo 4x12"},
    {AMP_CAB_DIGI_BRIGHT, "DigiTech\xc2\xae Bright 2x12"},
    {AMP_CAB_DIGI_METAL, "DigiTech\xc2\xae Metal 4x12"},
    {AMP_CAB_DIGI_ROCK, "DigiTech\xc2\xae Rock 4x12"},
    {AMP_CAB_DIGI_ALT, "DigiTech\xc2\xae Alt 4x12"},
    {AMP_CAB_DIGI_VNTG, "DigiTech\xc2\xae Vintage 4x12"},
    {AMP_CAB_DIGI_CHUNK, "DigiTech\xc2\xae Chunk 4x12"},
    {AMP_CAB_DIGI_SPANK2_12, "DigiTech\xc2\xae Spank 2x12"},
    {AMP_CAB_DIGI_SPKR_COMP, "DigiTech\xc2\xae Spkr Comp"},

    {GNX_AMP_CAB_DIRECT, "Direct"},
    {GNX_AMP_CAB_TWEED1_8, "Tweed 1x8"},
    {GNX_AMP_CAB_TWEED1_12, "Tweed 1x12"},
    {GNX_AMP_CAB_BLACKFACE1_12, "Blackface 1x12"},
    {GNX_AMP_CAB_BRITISH1_12, "British 1x12"},
    {GNX_AMP_CAB_BLACKFACE2_12, "Blackface 2x12"},
    {GNX_AMP_CAB_BLONDE2_12, "Blonde 2x12"},
    {GNX_AMP_CAB_BRITISH2_12, "British 2x12"},
    {GNX_AMP_CAB_TWEED4_10, "Tweed 4x10"},
    {GNX_AMP_CAB_BRITISH_70_4_12, "British 70 4x12"},
    {GNX_AMP_CAB_BRITISH_GREEN4_12, "British Green 4x12"},
    {GNX_AMP_CAB_STRAIGHT_V30_4_12, "Straight V30 4x12"},
    {GNX_AMP_CAB_SLANT_V30_4_12, "Slant V30 4x12"},
    {GNX_AMP_CAB_FANE4_12, "Fane 4x12"},
    {GNX_AMP_CAB_2101_SPKR_COMP, "2101 Spkr Comp"},
    {GNX_AMP_CAB_DIGI_SPANK, "Digitech Spank 4x12"},
    {GNX_AMP_CAB_DIGI_SOLO, "Digitech Solo 4x12"},
    {GNX_AMP_CAB_DIGI_METAL, "Digitech Metal 4x12"},
    {GNX_AMP_CAB_DIGI_BRIGHT, "Digitech Bright 4x12"},
    {GNX_AMP_CAB_DIGI_CHUNK, "Digitech Chunk 4x12"},
    {GNX_AMP_CAB_JUMBO_ACOUSTIC, "Jumbo Acoustic"},
    {GNX_AMP_CAB_DREAD_ACOUSTIC, "Dread Acoustic"},
    {GNX_AMP_CAB_HART_BASS1_15, "Hart Bass 1x15"},
    {GNX_AMP_CAB_BASIC_BASS1_15, "Basic Bass 1x15"},
    {GNX_AMP_CAB_PORTA_BASS1_15, "Porta Bass 1x15"},
    {GNX_AMP_CAB_REFLEX1_18, "Reflex 1x18"},
    {GNX_AMP_CAB_SOLAR_BASS2_15, "Solar Bass 2x15"},
    {GNX_AMP_CAB_DE_BASS4_10, "DE Bass 4x10"},
    {GNX_AMP_CAB_ASH_BASS4_10, "Ash Bass 4x10"},
    {GNX_AMP_CAB_GOLIATH_BASS4_10, "Goliath Bass 4x10"},
    {GNX_AMP_CAB_HART_BASS4_10, "Hart Bass 4x10"},
    {GNX_AMP_CAB_SVT_BASS8_10, "SVT Bass 8x10"},
};

static XmlLabel xml_noisegate_labels[] = {
    {NOISEGATE_GATE, "Gate"},
    {NOISEGATE_SWELL, "Swell"},
};

static XmlLabel xml_pre_post_labels[] = {
    {CHORUSFX_PRE, "Pre"},
    {CHORUSFX_POST, "Post"},
};

static XmlLabel xml_chorusfx_labels[] = {
    {CHORUS_TYPE_CE, "CE Chorus"},
    {CHORUS_TYPE_TC, "TC Chorus"},
    {CHORUS_TYPE_DUAL, "Dual Chorus"},
    {CHORUS_TYPE_GLISTEN, "Glisten Chorus"},
    {CHORUS_TYPE_MULTI, "Multi Chorus"},
    {CHORUS_TYPE_VOO_DOO, "Analog Chorus"},
    {CHORUS_TYPE_CLONE, "Small Clone"},
    {CHORUS_TYPE_FLANGER, "Flanger"},
    {CHORUS_TYPE_TRIGGERED_FLANGER, "Triggered Flanger"},
    {CHORUS_TYPE_FLTFLANGER, "Filter Flanger"},
    {CHORUS_TYPE_MXR_FLANGER, "MXR FLANGER"},
    {CHORUS_TYPE_EH_FLANGER, "EH Flanger"},
    {CHORUS_TYPE_AD_FLANGER, "AD Flanger"},
    {CHORUS_TYPE_PHASER, "Phaser"},
    {CHORUS_TYPE_TRIGGERED_PHASER, "Triggered Phaser"},
    {CHORUS_TYPE_MX_PHASER, "MX Phaser"},
    {CHORUS_TYPE_EH_PHASER, "EH Phaser"},
    {CHORUS_TYPE_VIBRATO, "Vibrato"},
    {CHORUS_TYPE_ROTARY, "Rotary"},
    {CHORUS_TYPE_VIBROPAN, "Vibropan"},
    {CHORUS_TYPE_UNOVIBE, "Unovibe"},
    {CHORUS_TYPE_TREMOLO, "Tremolo"},
    {CHORUS_TYPE_SCATTER_TREM, "ScatterTrem"},
    {CHORUS_TYPE_OPTO_TREMOLO, "Opto Tremolo"},
    {CHORUS_TYPE_BIAS_TREMOLO, "Bias Tremolo"},
    {CHORUS_TYPE_PANNER, "Panner"},
    {CHORUS_TYPE_ENVELOPE, "Envelope"},
    {CHORUS_TYPE_FX25, "FX25"},
    {CHORUS_TYPE_AUTOYA, "AutoYa"},
    {CHORUS_TYPE_YAYA, "YaYa"},
    {CHORUS_TYPE_SYNTH_TALK, "Synth Talk"},
    {CHORUS_TYPE_STEP_FILTER, "Step Filter"},
    {CHORUS_TYPE_SAMPLE_HOLD, "Sample/Hold"},
    {CHORUS_TYPE_WHAMMY, "Whammy"},
    {CHORUS_TYPE_PITCH_SHIFT, "Pitch"},
    {CHORUS_TYPE_DETUNE, "Detune"},
    {CHORUS_TYPE_IPS, "Harmony Pitch"},
    {CHORUS_TYPE_OCTAVER, "Octaver"},
};

static XmlLabel xml_waveform_labels[] = {
    {CHORUS_WAVEFORM_TRI, "Tri"},
    {CHORUS_WAVEFORM_SINE, "Sine"},
    {CHORUS_WAVEFORM_SQUARE, "Square"},
};

static XmlLabel xml_chorus_vibrato_labels[] = {
    {0, "Chorus"},
    {1, "Vibrato"},
};

static XmlLabel xml_whammy_amount_labels[] = {
    {WHAMMY_TYPE_OCT_UP, "OctUp"},
    {WHAMMY_TYPE_2OCT_UP, "2OctUp"},
    {WHAMMY_TYPE_2ND_DN, "2ndDn"},
    {WHAMMY_TYPE_RV2ND_DN, "Rv2nc"},
    {WHAMMY_TYPE_4TH_DN, "4thDn"},
    {WHAMMY_TYPE_OCT_DN, "OctDn"},
    {WHAMMY_TYPE_2OCT_DN, "2OctDn"},
    {WHAMMY_TYPE_DIV_BMB, "DivBmb"},
    {WHAMMY_TYPE_M3_GT_MA3, "M3>Ma3"},
    {WHAMMY_TYPE_2ND_MA3, "2ndMa3"},
    {WHAMMY_TYPE_3RD_4TH, "3rd4th"},
    {WHAMMY_TYPE_4TH_5TH, "5thOct"},
    {WHAMMY_TYPE_5TH_OCT, "5thOct"},
    {WHAMMY_TYPE_HOCT_UP, "HOctUp"},
    {WHAMMY_TYPE_HOCT_DN, "HOctDn"},
    {WHAMMY_TYPE_OCT_GT_D, "OctU>D"},
};

static XmlLabel xml_ips_shift_labels[] = {
    {IPS_SHIFT_OCT_DN, "Oct Dn"},
    {IPS_SHIFT_7TH_DN, "7th Dn"},
    {IPS_SHIFT_6TH_DN, "6th Dn"},
    {IPS_SHIFT_5TH_DN, "5th Dn"},
    {IPS_SHIFT_4TH_DN, "4th Dn"},
    {IPS_SHIFT_3RD_DN, "3rd Dn"},
    {IPS_SHIFT_2ND_DN, "2nd Dn"},
    {IPS_SHIFT_2ND_UP, "2nd Up"},
    {IPS_SHIFT_3RD_UP, "3rd Up"},
    {IPS_SHIFT_4TH_UP, "4th Up"},
    {IPS_SHIFT_5TH_UP, "5th Up"},
    {IPS_SHIFT_6TH_UP, "6th Up"},
    {IPS_SHIFT_7TH_UP, "7th Up"},
    {IPS_SHIFT_OCT_UP, "Oct Up"},
};

static XmlLabel xml_ips_key_labels[] = {
    {IPS_KEY_E, "E"},
    {IPS_KEY_F, "F"},
    {IPS_KEY_Gb, "Gb"},
    {IPS_KEY_G, "G"},
    {IPS_KEY_Ab, "Ab"},
    {IPS_KEY_A, "A"},
    {IPS_KEY_Bb, "Bb"},
    {IPS_KEY_B, "B"},
    {IPS_KEY_C, "C"},
    {IPS_KEY_Db, "Db"},
    {IPS_KEY_D, "D"},
    {IPS_KEY_Eb, "Eb"},
};

static XmlLabel xml_ips_scale_labels[] = {
    {IPS_SCALE_MAJOR, "Major"},
    {IPS_SCALE_MINOR, "Minor"},
    {IPS_SCALE_DORIAN, "Dorian"},
    {IPS_SCALE_MIXOLYDIAN, "Mixolydian"},
    {IPS_SCALE_LYDIAN, "Lydian"},
    {IPS_SCALE_HMINOR, "HMinor"},
};

static XmlLabel xml_delay_labels[] = {

    {DELAY_TYPE_ANALOG, "Analog"},
    {DELAY_TYPE_DM, "DM Delay"},
    {DELAY_TYPE_DIGITAL, "Digital"},
    {DELAY_TYPE_MODULATED, "Modulated"},
    {DELAY_TYPE_PONG, "Pong"},
    {DELAY_TYPE_TAPE, "Tape"},
    {DELAY_TYPE_ECHOPLEX, "Echo Plex"},

    {DELAY_RP500_TYPE_DIGITAL, "Digital"},
    {DELAY_RP500_TYPE_ANALOG, "Analog"},
    {DELAY_RP500_TYPE_DM, "DM Delay"},
    {DELAY_RP500_TYPE_ECHOPLEX, "Echo Plex"},
    {DELAY_RP500_TYPE_MODULATED, "Modulated"},
    {DELAY_RP500_TYPE_PONG, "Pong"},
    {DELAY_RP500_TYPE_REVERSE, "Reverse"},
    {DELAY_RP500_TYPE_TAPE, "Tape"},
    {DELAY_RP1000_TYPE_LO_FI, "Lo Fidelity"},
    {DELAY_RP1000_TYPE_2_TAP, "2-tap"},

    {DELAY_GNX3K_TYPE_MONO, "Mono"},
    {DELAY_GNX3K_TYPE_PINGPONG, "Ping-Pong"},
    {DELAY_GNX3K_TYPE_ANALOG, "Analog"},
    {DELAY_GNX3K_TYPE_ANAPONG, "Analog-Pong"},
    {DELAY_GNX3K_TYPE_SPREAD, "Spread"},
};

static XmlLabel xml_reverb_labels[] = {
    {REVERB_TYPE_TWIN, "Twin"},
    {REVERB_TYPE_LEX_AMBIENCE, "Lexicon Ambience"},
    {REVERB_TYPE_LEX_STUDIO, "Lexicon Studio"},
    {REVERB_TYPE_LEX_ROOM, "Lexicon Room"},
    {REVERB_TYPE_LEX_HALL, "Lexicon Hall"},
    {REVERB_TYPE_EMT240_PLATE, "EMT240 Plate"},

    {GNX3K_REVERB_TYPE_STUDIO, "Studio"},
    {GNX3K_REVERB_TYPE_ROOM, "Room"},
    {GNX3K_REVERB_TYPE_CLUB, "Club"},
    {GNX3K_REVERB_TYPE_PLATE, "Plate"},
    {GNX3K_REVERB_TYPE_HALL, "Hall"},
    {GNX3K_REVERB_TYPE_AMPHITHEATER, "Amphitheater"},
    {GNX3K_REVERB_TYPE_CHURCH, "Church"},
    {GNX3K_REVERB_TYPE_GARAGE, "Garage"},
    {GNX3K_REVERB_TYPE_ARENA, "Arena"},
    {GNX3K_REVERB_TYPE_SPRING, "Spring"},
};

static XmlLabel xml_wah_labels[] = {
    {WAH_TYPE_CRY, "Cry Wah"},
    {WAH_TYPE_FULLRANGE, "Fullrange Wah"},
    {WAH_TYPE_CLYDE, "Clyde Wah"},

    {GNX3K_WAH_TYPE_CRY, "Cry"},
    {GNX3K_WAH_TYPE_BOUTIQUE, "Boutique"},
    {GNX3K_WAH_TYPE_FULLRANGE, "Full-Range"},
};

static XmlLabel xml_exp_assign_labels[] = {
   {EXP_VOLUME_PRE_FX, "Volume Pre FX"},
   {EXP_VOLUME_POST_FX, "Volume Post FX"},
};

static XmlLabel xml_vswitch_toggle_labels[] = {
    {VSWITCH_TYPE_TOGGLE, "Toggle"},
};

static XmlLabel xml_vswitch_pedal_assign_labels[] = {
    {VSWITCH_PEDAL_ASSIGN_WAH, "Wah Position"},
};

static XmlLabel xml_vswitch_assign_labels[] = {
    {VSWITCH_ASSIGN_WAH_ENABLE, "Wah Enable"},
};

static XmlLabel xml_lfo_assign_labels[] = {
    {LFO_ASSIGN_NONE, "None"},
};

static XmlLabel xml_eq_labels[] = {
    {EQ_TYPE_BRIGHT, "Bright"},
    {EQ_TYPE_MIDBOOST, "Mid Boost"},
    {EQ_TYPE_SCOOP, "Scoop"},
    {EQ_TYPE_WARM, "Warm"},
};

static XmlLabel xml_tone_lib_labels[] = {
    {TONE_LIB_OVERDRIVE, "Overdrive"},
    {TONE_LIB_ROCK1, "Rock 1"},
    {TONE_LIB_ROCK2, "Rock 2"},
    {TONE_LIB_BLUES1, "Blues 1"},
    {TONE_LIB_BLUES2, "Blues 2"},
    {TONE_LIB_METAL1, "Metal 1"},
    {TONE_LIB_METAL2, "Metal 2"},
    {TONE_LIB_COUNTRY1, "Country 1"},
    {TONE_LIB_COUNTRY2, "Country 2"},
    {TONE_LIB_WARM_DRIVE, "Warm Drive"},
    {TONE_LIB_CRUNCH, "Crunch"},
    {TONE_LIB_TEXAS_TONE, "Texas Tone"},
    {TONE_LIB_ROCKABILLY, "Rockabilly"},
    {TONE_LIB_SOLO1, "Solo 1"},
    {TONE_LIB_SOLO2, "Solo 2"},
    {TONE_LIB_ROCKWAH, "Rock Wah"},
    {TONE_LIB_CHUNKY, "Chunky"},
    {TONE_LIB_SMOOTH, "Smooth"},
    {TONE_LIB_HEAVY, "Heavy"},
    {TONE_LIB_CLEAN1, "Clean 1"},
    {TONE_LIB_CLEAN2, "Clean 2"},
    {TONE_LIB_BRITISH1, "British 1"},
    {TONE_LIB_BRITISH2, "British 2"},
    {TONE_LIB_AMERICAN1, "American 1"},
    {TONE_LIB_AMERICAN2, "American 2"},
    {TONE_LIB_TUBE_DRIVE, "Tube Drive"},
    {TONE_LIB_DISTORTION, "Distortion"},
    {TONE_LIB_SCOOPED, "Scooped"},
    {TONE_LIB_PUNCHY, "Punchy"},
    {TONE_LIB_BRIGHT_CLEAN, "Bright Clean"},
    {TONE_LIB_CUSTOM, "Custom"},
};

static XmlLabel xml_fx_lib_labels[] = {
    {EFFECTS_LIB_CUSTOM, "Custom"},
    {EFFECTS_LIB_CHORUS, "Chorus"},
    {EFFECTS_LIB_PHASER, "Phaser"},
    {EFFECTS_LIB_FLANGER, "Flanger"},
    {EFFECTS_LIB_PITCH, "Pitch"},
    {EFFECTS_LIB_TREMOLO, "Tremolo"},
    {EFFECTS_LIB_ROTARY, "Rotary"},
    {EFFECTS_LIB_ENVELOPE, "Envelope Filter"},
    {EFFECTS_LIB_DIGITAL, "Digital Delay"},
    {EFFECTS_LIB_ANALOG, "Analog Delay"},
    {EFFECTS_LIB_PONG, "Pong Delay"},
    {EFFECTS_LIB_MOD, "Mod Delay"},
    {EFFECTS_LIB_TAPE, "Tape Delay"},
    {EFFECTS_LIB_HALL, "Hall Reverb"},
    {EFFECTS_LIB_PLATE, "Plate Reverb"},
    {EFFECTS_LIB_SPRING, "Spring Reverb"},
    {EFFECTS_LIB_CHORUS_DIGITAL, "Chorus + Digital Delay"},
    {EFFECTS_LIB_CHORUS_DELAY_REVERB, "Chorus + Delay + Reverb"},
    {EFFECTS_LIB_FLANGER_ANALOG, "Flanger + Analog Delay"},
    {EFFECTS_LIB_PHASER_TAPE, "Phaser + Tape Delay"},
    {EFFECTS_LIB_PHASER_MOD, "Phaser + Mod Delay"},
    {EFFECTS_LIB_PHASER_ROOM, "Phaser + Room Reverb"},
    {EFFECTS_LIB_DIGITAL_HALL, "Digital Delay + Hall Reverb"},
    {EFFECTS_LIB_ANALOG_SPRING, "Analog Delay + Spring Reverb"},
    {EFFECTS_LIB_CHORUS_HALL, "Chorus + Hall Reverb"},
    {EFFECTS_LIB_PONG_HALL, "Pong Delay + Hall Reverb"},
    {EFFECTS_LIB_TAPE_SPRING, "Tape Delay + Spring Reverb"},
    {EFFECTS_LIB_TREMOLO_TAPE, "Tremolo + Tape Delay"},
    {EFFECTS_LIB_PITCH_DIGITAL, "Pitch + Digital Delay"},
    {EFFECTS_LIB_MOD_PLATE, "Mod Delay + Plate Reverb"},
    {EFFECTS_LIB_ROTARY_TAPE, "Rotary + Tape Delay"},
};

static XmlLabel xml_rhold_labels[] = {
    {100, "RHold"},
};
static XmlLabel xml_eq_low_freq_labels[] = {
    {0, "60Hz"},
    {1, "63Hz"},
    {2, "67Hz"},
    {3, "71Hz"},
    {4, "75Hz"},
    {5, "80Hz"},
    {6, "85Hz"},
    {7, "90Hz"},
    {8, "95Hz"},
    {9, "100Hz"},
    {11, "106Hz"},
    {12, "112Hz"},
    {13, "118Hz"},
    {14, "125Hz"},
    {15, "132Hz"},
    {16, "140Hz"},
    {17, "150Hz"},
    {18, "160Hz"},
    {19, "170Hz"},
    {20, "180Hz"},
    {21, "190Hz"},
    {22, "200Hz"},
    {23, "212Hz"},
    {24, "224Hz"},
    {25, "236Hz"},
    {26, "250Hz"},
    {27, "265Hz"},
    {28, "280Hz"},
    {29, "300Hz"},
    {30, "315Hz"},
    {31, "335Hz"},
    {32, "355Hz"},
    {33, "375Hz"},
    {34, "400Hz"},
    {35, "425Hz"},
    {36, "450Hz"},
    {37, "475Hz"},
    {38, "500Hz"},
};

static XmlLabel xml_eq_mid_freq_labels[] = {
    {0, "300Hz"},
    {1, "315Hz"},
    {2, "335Hz"},
    {3, "355Hz"},
    {4, "375Hz"},
    {5, "400Hz"},
    {6, "425Hz"},
    {7, "450Hz"},
    {8, "475Hz"},
    {9, "500Hz"},
    {0, "530Hz"},
    {11, "560Hz"},
    {12, "600Hz"},
    {13, "630Hz"},
    {15, "670Hz"},
    {16, "710Hz"},
    {17, "750Hz"},
    {18, "800Hz"},
    {19, "850Hz"},
    {20, "900Hz"},
    {21, "950Hz"},
    {22, "1kHz"},
    {23, "1.06kHz"},
    {24, "1.12kHz"},
    {25, "1.18kHz"},
    {26, "1.25kHz"},
    {27, "1.32kHz"},
    {28, "1.4kHz"},
    {29, "1.5kHz"},
    {30, "1.6kHz"},
    {31, "1.7kHz"},
    {32, "1.8kHz"},
    {33, "1.9kHz"},
    {34, "2kHz"},
    {35, "2.12kHz"},
    {36, "2.24kHz"},
    {37, "2.36kHz"},
    {38, "2.5kHz"},
    {39, "2.65kHz"},
    {40, "2.8kHz"},
    {41, "3kHz"},
    {42, "3.15kHz"},
    {43, "3.35kHz"},
    {44, "3.55kHz"},
    {45, "3.75kHz"},
    {46, "4kHz"},
};

static XmlLabel xml_eq_high_freq_labels[] = {
    {0, "2kHz"},
    {1, "2.12kHz"},
    {2,"2.24kHz"},
    {3, "2.36kHz"},
    {4, "2.5kHz"},
    {5, "2.65kHz"},
    {6, "2.8kHz"},
    {7, "3kHz"},
    {8, "3.15kHz"},
    {9, "3.35kHz"},
    {10, "3.55kHz"},
    {11, "3.75kHz"},
    {12, "4kHz"},
    {13, "4.25kHz"},
    {14, "4.5kHz"},
    {15, "4.75kHz"},
    {16, "5kHz"},
    {17, "5.3kHz"},
    {18, "5.6kHz"},
    {19, "6kHz"},
    {20, "6.3kHz"},
    {21, "6.7kHz"},
    {22, "7.1kHz"},
    {23, "7.5kHz"},
    {24, "8kHz"},
};

static XmlLabel xml_eq_bandwidth_labels[] = {
    {0, "Wide"},
    {1, "Medium"},
    {2, "Narrow"},
};

static XmlLabel xml_delay_mult_labels[] = {
    {DELAY_HALF, "Half"},
    {DELAY_QUARTER, "Quarter"},
    {DELAY_DOTEIGHT, "Dot Eighth"},
    {DELAY_EIGHT, "Eighth"},
    {DELAY_3_QUARTR, "3 Quarter"},
};

/* Array to map id/position pairs to labels and settings. */
XmlSettings xml_settings[] = {
    {0, 0, "None", NULL,},

    {PICKUP_ON_OFF, PICKUP_POSITION, "Pickup Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {PICKUP_TYPE, PICKUP_POSITION, "EQ Type", &values_pickup_type, xml_pickup_labels, G_N_ELEMENTS(xml_pickup_labels)},

    {COMP_ON_OFF, COMP_POSITION, "Compressor Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {COMP_TYPE, COMP_POSITION, "Comp Type", &values_comp_type, xml_comp_labels, G_N_ELEMENTS(xml_comp_labels)},
    {COMP_SUSTAIN, COMP_POSITION, "Compressor Sustain", &values_0_to_99,},
    {COMP_TONE, COMP_POSITION, "Compressor Tone", &values_0_to_99,},
    {COMP_LEVEL, COMP_POSITION, "Compressor Level", &values_0_to_99,},
    {COMP_ATTACK, COMP_POSITION, "Compressor Attack", &values_0_to_99,},
    {COMP_OUTPUT, COMP_POSITION, "Compressor Output", &values_0_to_99,},
    {COMP_SENSITIVITY, COMP_POSITION, "Compressor Sensitivity", &values_0_to_99,},

    {DIST_TYPE, DIST_POSITION, "Dist Type", &values_dist_type, xml_dist_labels, G_N_ELEMENTS(xml_dist_labels)},
    {DIST_ON_OFF, DIST_POSITION, "Dist Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {DIST_SCREAMER_DRIVE, DIST_POSITION, "Dist Drive", &values_0_to_99,},
    {DIST_SCREAMER_TONE, DIST_POSITION, "Dist Tone", &values_0_to_99,},
    {DIST_SCREAMER_LVL, DIST_POSITION, "Dist Level", &values_0_to_99,},
    {DIST_808_OVERDRIVE, DIST_POSITION, "Dist Overdrive", &values_0_to_99,},
    {DIST_808_TONE, DIST_POSITION, "Dist Tone", &values_0_to_99,},
    {DIST_808_LVL, DIST_POSITION, "Dist Level", &values_0_to_99,},
    {DIST_GUYOD_DRIVE, DIST_POSITION, "Dist Drive", &values_0_to_99,},
    {DIST_GUYOD_LVL, DIST_POSITION, "Dist Level", &values_0_to_99,},
    {DIST_DOD250_GAIN, DIST_POSITION, "Dist Gain", &values_0_to_99,},
    {DIST_DOD250_LVL, DIST_POSITION, "Dist Level", &values_0_to_99,},
    {DIST_RODENT_DIST, DIST_POSITION, "Dist Distortion", &values_0_to_99,},
    {DIST_RODENT_FILTER, DIST_POSITION, "Dist Filter", &values_0_to_99,},
    {DIST_RODENT_LVL, DIST_POSITION, "Dist Volume", &values_0_to_99,},
    {DIST_MX_DIST, DIST_POSITION, "Dist Distortion", &values_0_to_99,},
    {DIST_MX_OUTPUT, DIST_POSITION, "Dist Output", &values_0_to_99,},
    {DIST_DS_GAIN, DIST_POSITION, "Dist Distortion", &values_0_to_99,},
    {DIST_DS_TONE, DIST_POSITION, "Dist Tone", &values_0_to_99,},
    {DIST_DS_LVL, DIST_POSITION, "Dist Level", &values_0_to_99,},
    {DIST_GRUNGE_GRUNGE, DIST_POSITION, "Dist Gain", &values_0_to_99,},
    {DIST_GRUNGE_FACE, DIST_POSITION, "Dist Face", &values_0_to_99,},
    {DIST_GRUNGE_LOUD, DIST_POSITION, "Dist Loud", &values_0_to_99,},
    {DIST_GRUNGE_BUTT, DIST_POSITION, "Dist Butt", &values_0_to_99,},
    {DIST_ZONE_GAIN, DIST_POSITION, "Dist Gain", &values_0_to_99,},
    {DIST_ZONE_MID_LVL, DIST_POSITION, "Dist Mid Level", &values_0_to_99,},
    {DIST_ZONE_LEVEL, DIST_POSITION, "Dist Level", &values_0_to_99,},
    {DIST_ZONE_LOW, DIST_POSITION, "Dist Low", &values_0_to_99,},
    {DIST_ZONE_MID_FREQ, DIST_POSITION, "Dist Mid Freq", &values_0_to_99,},
    {DIST_ZONE_HIGH, DIST_POSITION, "Dist High", &values_0_to_99,},
    {DIST_DEATH_LOW, DIST_POSITION, "Dist Low", &values_0_to_99,},
    {DIST_DEATH_MID, DIST_POSITION, "Dist Mid", &values_0_to_99,},
    {DIST_DEATH_LVL, DIST_POSITION, "Dist Level", &values_0_to_99,},
    {DIST_DEATH_HIGH, DIST_POSITION, "Dist High", &values_0_to_99,},
    {DIST_GONK_GONK, DIST_POSITION, "Dist Gunk", &values_0_to_99,},
    {DIST_GONK_SMEAR, DIST_POSITION, "Dist Smear", &values_0_to_99,},
    {DIST_GONK_SUCK, DIST_POSITION, "Dist Suck", &values_0_to_99,},
    {DIST_GONK_HEAVE, DIST_POSITION, "Dist Heave", &values_0_to_99,},
    {DIST_FUZZY_FUZZ, DIST_POSITION, "Dist Fuzz", &values_0_to_99,},
    {DIST_FUZZY_VOLUME, DIST_POSITION, "Dist Volume", &values_0_to_99,},
    {DIST_MP_SUSTAIN, DIST_POSITION, "Dist Sustain", &values_0_to_99,},
    {DIST_MP_TONE, DIST_POSITION, "Dist Tone", &values_0_to_99,},
    {DIST_MP_VOLUME, DIST_POSITION, "Dist Volume", &values_0_to_99,},

    {AMP_CHANNEL, AMP_CHANNEL_POSITION, "Amp Channel", &values_a_b, xml_amp_channel_labels, G_N_ELEMENTS(xml_amp_channel_labels)},

    {AMP_TYPE, AMP_A_POSITION, "Amp A Type", &values_amp_type, xml_amp_labels, G_N_ELEMENTS(xml_amp_labels)},
    {AMP_ON_OFF, AMP_A_POSITION, "Amp A Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {AMP_GAIN, AMP_A_POSITION, "Amp A Gain", &values_0_to_99,},
    {AMP_LEVEL, AMP_A_POSITION, "Amp A Level", &values_0_to_99,},

    {AMP_BYPASS_ON_OFF, AMP_BYPASS_POSITION, "Amp Bypass", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},

    {AMP_TYPE, AMP_B_POSITION, "Amp B Type", &values_amp_type, xml_amp_labels, G_N_ELEMENTS(xml_amp_labels)},
    {AMP_ON_OFF, AMP_B_POSITION, "Amp B Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {AMP_GAIN, AMP_B_POSITION, "Amp B Gain", &values_0_to_99,},
    {AMP_LEVEL, AMP_B_POSITION, "Amp B Level", &values_0_to_99,},

    {AMP_BASS, AMP_A_POSITION, "Amp B Level", &values_1_to_10_step_0p1,},
    {AMP_MID, AMP_A_POSITION, "Amp B Level", &values_1_to_10_step_0p1,},
    {AMP_TREBLE, AMP_A_POSITION, "Amp B Level", &values_1_to_10_step_0p1,},

    {AMP_CAB_TYPE, AMP_CAB_POSITION, "Cab A Type", &values_cab_type, xml_amp_cab_labels, G_N_ELEMENTS(xml_amp_cab_labels)},
    {AMP_CAB_TYPE, AMP_CAB_B_POSITION, "Cab B Type", &values_cab_type, xml_amp_cab_labels, G_N_ELEMENTS(xml_amp_cab_labels)},

    {NOISEGATE_TYPE, NOISEGATE_POSITION, "Gate Type", &values_gate_type, xml_noisegate_labels, G_N_ELEMENTS(xml_noisegate_labels)},
    {NOISEGATE_ON_OFF, NOISEGATE_POSITION, "Gate Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {NOISEGATE_SWELL_SENS, NOISEGATE_POSITION, "Gate Pluck Sens", &values_0_to_99,},
    {NOISEGATE_GATE_TRESHOLD, NOISEGATE_POSITION, "Gate Threshold", &values_0_to_99,},
    {NOISEGATE_ATTACK, NOISEGATE_POSITION, "Gate Attack", &values_0_to_99,},
    {NOISEGATE_RELEASE, NOISEGATE_POSITION, "Gate Release", &values_0_to_99,},
    {NOISEGATE_ATTN, NOISEGATE_POSITION, "Gate Attenuation", &values_0_to_99,},

    {MOD_PRE_POST, CHORUSFX_POSITION, "Mod Pre/Post", &values_pre_post, xml_pre_post_labels, G_N_ELEMENTS(xml_pre_post_labels)},

    {CHORUSFX_ON_OFF, CHORUSFX_POSITION, "Chorus/FX Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {CHORUSFX_PRE_POST, CHORUSFX_POSITION, "Mod Pre/Post", &values_pre_post, xml_pre_post_labels, G_N_ELEMENTS(xml_pre_post_labels)},
    {CHORUSFX_TYPE, CHORUSFX_POSITION, "Mod Type", &values_mod_type, xml_chorusfx_labels, G_N_ELEMENTS(xml_chorusfx_labels)},

    {PHASER_SPEED, CHORUSFX_POSITION, "Phaser Speed", &values_0_to_99,},
    {PHASER_DEPTH, CHORUSFX_POSITION, "Phaser Depth", &values_0_to_99,},
    {PHASER_REGEN, CHORUSFX_POSITION, "Phaser Regen", &values_0_to_99,},
    {PHASER_WAVE, CHORUSFX_POSITION, "Phaser Waveform", &values_waveform, xml_waveform_labels, G_N_ELEMENTS(xml_waveform_labels)},
    {PHASER_LEVEL, CHORUSFX_POSITION, "Phaser Level", &values_0_to_99,},

    {EH_PHASER_RATE, CHORUSFX_POSITION, "Phaser Rate", &values_0_to_99,},
    {EH_PHASER_COLOR, CHORUSFX_POSITION, "Phaser xml Color", &values_on_off, xml_on_off_labels,G_N_ELEMENTS(xml_on_off_labels)},

    {MX_PHASER_INTENSITY, CHORUSFX_POSITION, "Intensity", &values_1_to_4,},

    {TRIG_PHASER_SPEED, CHORUSFX_POSITION, "Trig Phaser Speed", &values_0_to_99,},
    {TRIG_PHASER_SENS, CHORUSFX_POSITION, "Trig Phaser Sens", &values_0_to_99,},
    {TRIG_PHASER_LFO_START, CHORUSFX_POSITION, "Trig Phaser LFO", &values_0_to_99,},
    {TRIG_PHASER_LEVEL, CHORUSFX_POSITION, "Trig Phaser Level", &values_0_to_99,},

    {CHORUS_SPEED, CHORUSFX_POSITION, "Chorus Speed", &values_0_to_99,},
    {CHORUS_DEPTH, CHORUSFX_POSITION, "Chorus Depth", &values_0_to_99,},
    {CHORUS_LEVEL, CHORUSFX_POSITION, "Chorus Level", &values_0_to_99,},
    {CHORUS_WIDTH, CHORUSFX_POSITION, "Chorus Width", &values_0_to_99,},
    {CHORUS_INTENSITY, CHORUSFX_POSITION, "Chorus Intensity", &values_0_to_99,},
    {CHORUS_WAVE, CHORUSFX_POSITION, "Chorus Waveform", &values_waveform, xml_waveform_labels, G_N_ELEMENTS(xml_waveform_labels)},

    {FLANGER_SPEED, CHORUSFX_POSITION, "Flanger Speed", &values_0_to_99,},
    {FLANGER_DEPTH, CHORUSFX_POSITION, "Flanger Depth", &values_0_to_99,},
    {FLANGER_REGEN, CHORUSFX_POSITION, "Flanger Regen", &values_0_to_99,},
    {FLANGER_WAVE, CHORUSFX_POSITION, "Flanger Waveform", &values_waveform,  xml_waveform_labels, G_N_ELEMENTS(xml_waveform_labels)},
    {FLANGER_LEVEL, CHORUSFX_POSITION, "Flanger Level", &values_0_to_99,},

    {TRIG_FLANGER_SPEED, CHORUSFX_POSITION, "Trig Flanger Speed", &values_0_to_99,},
    {TRIG_FLANGER_SENS, CHORUSFX_POSITION, "Trig Flanger Sens", &values_0_to_99,},
    {TRIG_FLANGER_LFO_START, CHORUSFX_POSITION, "Trig Flanger LFO Start", &values_0_to_99,},
    {TRIG_FLANGER_LEVEL, CHORUSFX_POSITION, "Trig Flanger Level", &values_0_to_99,},
    
    {EH_FLANGER_RATE, CHORUSFX_POSITION, "EH Flanger Rate", &values_0_to_99,},
    {EH_FLANGER_RANGE, CHORUSFX_POSITION, "EH Flanger Range", &values_0_to_99,},
    {EH_FLANGER_COLOR, CHORUSFX_POSITION, "EH Flanger Color", &values_0_to_99,},

    {MXR_FLANGER_WIDTH, CHORUSFX_POSITION, "Flanger Width", &values_0_to_99,},
    {MXR_FLANGER_MANUAL, CHORUSFX_POSITION, "Flanger Manual", &values_0_to_99,},

    {VIBRATO_SPEED, CHORUSFX_POSITION, "Vibrato Speed", &values_0_to_99,},
    {VIBRATO_DEPTH, CHORUSFX_POSITION, "Vibrato Depth", &values_0_to_99,},

    {ROTARY_SPEED, CHORUSFX_POSITION, "Rotary Speed", &values_0_to_99,},
    {ROTARY_INTENSITY, CHORUSFX_POSITION, "Rotary Intensity", &values_0_to_99,},
    {ROTARY_DOPPLER, CHORUSFX_POSITION, "Rotary Doppler", &values_0_to_99,},
    {ROTARY_CROSSOVER, CHORUSFX_POSITION, "Rotary Crossover", &values_0_to_99,},

    {VIBROPAN_SPEED, CHORUSFX_POSITION, "VibroPan Speed", &values_0_to_99,},
    {VIBROPAN_DEPTH, CHORUSFX_POSITION, "VibroPan Depth", &values_0_to_99,},
    {VIBROPAN_VIBRA, CHORUSFX_POSITION, "VibroPan VibratoPan", &values_0_to_99,},
    {VIBROPAN_WAVE, CHORUSFX_POSITION, "VibroPan Waveform", &values_waveform, xml_waveform_labels, G_N_ELEMENTS(xml_waveform_labels)},

    {UNOVIBE_PEDAL_SPEED, CHORUSFX_POSITION, "Unovibe Speed", &values_0_to_99,},
    {UNOVIBE_INTENSITY, CHORUSFX_POSITION, "Unovibe Intensity", &values_0_to_99,},
    {UNOVIBE_VOLUME, CHORUSFX_POSITION, "Unovibe Volume", &values_0_to_99,},
    {UNOVIBE_CHORUS_VIBRATO, CHORUSFX_POSITION, "Unovibe Chorus/Vibrato", &values_chorus_vibrato, xml_chorus_vibrato_labels, G_N_ELEMENTS(xml_chorus_vibrato_labels)},

    {TREMOLO_SPEED, CHORUSFX_POSITION, "Tremolo Speed", &values_0_to_99,},
    {TREMOLO_DEPTH, CHORUSFX_POSITION, "Tremolo Depth", &values_0_to_99,},
    {TREMOLO_WAVE, CHORUSFX_POSITION, "Tremolo Waveform", &values_waveform, xml_waveform_labels, G_N_ELEMENTS(xml_waveform_labels)},

    {PANNER_SPEED, CHORUSFX_POSITION, "Panner Speed", &values_0_to_99,},
    {PANNER_DEPTH, CHORUSFX_POSITION, "Panner Depth", &values_0_to_99,},
    {PANNER_WAVE, CHORUSFX_POSITION, "Panner Waveform", &values_waveform, xml_waveform_labels, G_N_ELEMENTS(xml_waveform_labels)},

    {ENVELOPE_SENSITIVITY, CHORUSFX_POSITION, "Envelope Sens.", &values_0_to_99,},
    {ENVELOPE_RANGE, CHORUSFX_POSITION, "Envelope Range", &values_0_to_99,},
    {ENVELOPE_BLEND, CHORUSFX_POSITION, "Envelope Blend", &values_0_to_99,},

    {AUTOYA_SPEED, CHORUSFX_POSITION, "AutoYa Speed", &values_0_to_99,},
    {AUTOYA_INTENSITY, CHORUSFX_POSITION, "AutoYa Intensity", &values_0_to_99,},
    {AUTOYA_RANGE, CHORUSFX_POSITION, "AutoYa Range", &values_0_to_49,},

    {YAYA_PEDAL, CHORUSFX_POSITION, "YaYa Pedal", &values_0_to_99,},
    {YAYA_INTENSITY, CHORUSFX_POSITION, "YaYa Intensity", &values_0_to_99,},
    {YAYA_RANGE, CHORUSFX_POSITION, "YaYa Range", &values_0_to_49,},

    {STEP_FILTER_SPEED, CHORUSFX_POSITION, "Step Filter Speed", &values_0_to_99,},
    {STEP_FILTER_INTENSITY, CHORUSFX_POSITION, "Step Filter Intensity", &values_0_to_99,},

    {WHAMMY_AMOUNT, CHORUSFX_POSITION, "Whammy Amount", &values_whammy_amount, xml_whammy_amount_labels, G_N_ELEMENTS(xml_whammy_amount_labels)},
    {WHAMMY_PEDAL, CHORUSFX_POSITION, "Whammy Pedal", &values_0_to_99,},
    {WHAMMY_MIX, CHORUSFX_POSITION, "Whammy Mix", &values_0_to_99,},

    {PITCH_AMOUNT, CHORUSFX_POSITION, "Pitch Shift Amount", &values_m24_to_24,},
    {PITCH_MIX, CHORUSFX_POSITION, "Pitch Shift Mix", &values_0_to_99,},

    {DETUNE_AMOUNT, CHORUSFX_POSITION, "Detune Amount", &values_m24_to_24,},
    {DETUNE_LEVEL, CHORUSFX_POSITION, "Detune Level", &values_0_to_99,},

    {IPS_SHIFT_AMOUNT, CHORUSFX_POSITION, "IPS Amount", &values_ips_shift, xml_ips_shift_labels, G_N_ELEMENTS(xml_ips_shift_labels)},
    {IPS_KEY, CHORUSFX_POSITION, "IPS Key", &values_ips_key, xml_ips_key_labels, G_N_ELEMENTS(xml_ips_key_labels)},
    {IPS_SCALE, CHORUSFX_POSITION, "IPS Scale", &values_ips_scale, xml_ips_scale_labels, G_N_ELEMENTS(xml_ips_scale_labels)},
    {IPS_LEVEL, CHORUSFX_POSITION, "IPS Level", &values_0_to_99,},


    {SYNTH_TALK_ATTACK, CHORUSFX_POSITION, "Synth Talk Attack", &values_0_to_99,},
    {SYNTH_TALK_RELEASE, CHORUSFX_POSITION, "Synth Talk Release", &values_0_to_99,},
    {SYNTH_TALK_SENS, CHORUSFX_POSITION, "Synth Talk Sens", &values_0_to_99,},
    {SYNTH_TALK_VOX, CHORUSFX_POSITION, "Synth Talk Vox", &values_0_to_99,},
    {SYNTH_TALK_BALANCE, CHORUSFX_POSITION, "Synth Talk Balance", &values_0_to_99,},

    {GNX3K_SYNTH_TALK_RELEASE, CHORUSFX_POSITION, "Synth Talk Release", &values_0_to_99,},

    {OCTAVER_OCTAVE1 , CHORUSFX_POSITION, "Octaver Octave 1", &values_0_to_99},
    {OCTAVER_OCTAVE2 , CHORUSFX_POSITION, "Octaver Octave 2", &values_0_to_99},
    {OCTAVER_DRY_LEVEL, CHORUSFX_POSITION, "Octaver Dry Level", &values_0_to_99},

    {DELAY_TYPE, DELAY_POSITION, "Delay Type", &values_delay_type, xml_delay_labels, G_N_ELEMENTS(xml_delay_labels)},
    {DELAY_ON_OFF, DELAY_POSITION, "Delay Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {DELAY_TIME, DELAY_POSITION, "Delay Time", &values_delay_time,},
    {DELAY_REPEATS, DELAY_POSITION, "Delay Repeats", &values_delay_repeats, xml_rhold_labels, G_N_ELEMENTS(xml_rhold_labels)},
    {DELAY_LEVEL, DELAY_POSITION, "Delay Level", &values_0_to_99,},
    {DELAY_DUCK_THRESH, DELAY_POSITION, "Delay Duck Thresh", &values_0_to_99,},
    {DELAY_DUCK_LEVEL, DELAY_POSITION, "Delay Duck Level", &values_0_to_99,},
    {DELAY_DEPTH, DELAY_POSITION, "Delay Mod Depth", &values_0_to_99,},
    {DELAY_TAPE_WOW, DELAY_POSITION, "Delay Tape Wow", &values_0_to_99,},
    {DELAY_TAPE_FLUTTER, DELAY_POSITION, "Delay Tape Flut", &values_0_to_99,},
    {DELAY_TAP_TIME_0_4990, DELAY_POSITION, "Tap Time", &values_delay_time_0_4990,},

    {REVERB_TYPE, REVERB_POSITION, "Reverb Type", &values_reverb_type, xml_reverb_labels, G_N_ELEMENTS(xml_reverb_labels)},
    {REVERB_ON_OFF, REVERB_POSITION, "Reverb Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {REVERB_DECAY, REVERB_POSITION, "Reverb Decay", &values_0_to_99,},
    {REVERB_LIVELINESS, REVERB_POSITION, "Reverb Liveliness", &values_0_to_99,},
    {REVERB_LEVEL, REVERB_POSITION, "Reverb Level", &values_0_to_99,},
    {REVERB_PREDELAY, REVERB_POSITION, "Reverb Predelay", &values_0_to_15,},

    {PRESET_LEVEL, VOLUME_PRE_FX_POSITION, "Volume Pre FX", &values_0_to_99,},
    {PRESET_LEVEL, VOLUME_POST_FX_POSITION, "Volume Post FX", &values_0_to_99,}, 

    {WAH_TYPE, WAH_POSITION, "Wah Type", &values_wah_type, xml_wah_labels, G_N_ELEMENTS(xml_wah_labels)},
    {WAH_ON_OFF, WAH_POSITION, "Wah Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {WAH_PEDAL_POSITION, WAH_POSITION, "Wah Position", &values_0_to_99,},
    {WAH_VOLUME_BOOST, WAH_POSITION, "Wah Vol. Boost", &values_db_boost,},

    {PRESET_LEVEL, PRESET_POSITION, "Preset Level", &values_0_to_99,},

    {EXP_ASSIGN1, EXP_POSITION, "Pedal Assign 1", &values_exp_assign, xml_exp_assign_labels, G_N_ELEMENTS(xml_exp_assign_labels)},
    {EXP_MIN, EXP_POSITION, "Pedal Min 1", &values_0_to_99,},
    {EXP_MAX, EXP_POSITION, "Pedal Max 1", &values_0_to_99,},

    {EXP_TYPE, WAH_POSITION_MIN_MAX, "V-Switch Pedal Assign", &values_vswitch_pedal_assign, xml_vswitch_pedal_assign_labels, G_N_ELEMENTS(xml_vswitch_assign_labels)},
    {EXP_MIN, WAH_POSITION_MIN_MAX, "Wah Min", &values_0_to_99,},
    {EXP_MAX, WAH_POSITION_MIN_MAX, "Wah Min", &values_0_to_99,},

    {VSWITCH_ASSIGN, VSWITCH_ASSIGN_POSITION, "V-Switch Assign", &values_vswitch_assign, xml_vswitch_assign_labels, G_N_ELEMENTS(xml_vswitch_assign_labels)},
    {VSWITCH_MIN, VSWITCH_ASSIGN_POSITION, "V-Switch Min", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {VSWITCH_MAX, VSWITCH_ASSIGN_POSITION, "V-Switch Max", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {VSWITCH_TYPE, VSWITCH_ASSIGN_POSITION, "V-Switch Type", &values_vswitch_type, xml_vswitch_toggle_labels, G_N_ELEMENTS(xml_vswitch_toggle_labels)},
    {VSWITCH_ENABLE, VSWITCH_ASSIGN_POSITION, "V-Switch Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},

    {LFO_TYPE, LFO1_POSITION, "LFO1 Assign", &values_lfo_assign, xml_lfo_assign_labels, G_N_ELEMENTS(xml_lfo_assign_labels)},
    {LFO_MIN, LFO1_POSITION, "LFO1 Min", &values_lfo_none,},
    {LFO_MAX, LFO1_POSITION, "LFO1 Max", &values_lfo_none,},
    {LFO_SPEED, LFO1_POSITION, "LFO1 Speed", &values_lfo_speed,},
    {LFO_WAVEFORM, LFO1_POSITION, "LFO1 Waveform", &values_lfo_waveform, xml_waveform_labels, G_N_ELEMENTS(xml_waveform_labels)},

    {LFO_TYPE, LFO2_POSITION, "LFO2 Assign", &values_lfo_assign, xml_lfo_assign_labels, G_N_ELEMENTS(xml_lfo_assign_labels)},
    {LFO_MIN, LFO2_POSITION, "LFO2 Min", &values_lfo_none,},
    {LFO_MAX, LFO2_POSITION, "LFO2 Max", &values_lfo_none,},
    {LFO_SPEED, LFO2_POSITION, "LFO2 Speed", &values_lfo_speed,},
    {LFO_WAVEFORM, LFO2_POSITION, "LFO2 Waveform", &values_lfo_waveform, xml_waveform_labels, G_N_ELEMENTS(xml_waveform_labels)},

    {EQ_ENABLE, EQ_A_POSITION, "EQ A Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {EQ_TYPE, EQ_A_POSITION, "EQ A Type", &values_eq_type, xml_eq_labels, G_N_ELEMENTS(xml_eq_labels)},

    {EQ_BASS, EQ_A_POSITION, "EQ A Bass", &values_eq_db,},
    {EQ_MID, EQ_A_POSITION, "EQ A Mid", &values_eq_db,},
    {EQ_TREB, EQ_A_POSITION, "EQ A Treb", &values_eq_db,},

    {EQ_PRESENCE, EQ_A_POSITION, "EQ A Presence", &values_eq_db,},
    {EQ_MID_FREQ, EQ_A_POSITION, "EQ A Mid Freq", &values_eq_mid_hz,},
    {EQ_TREB_FREQ, EQ_A_POSITION, "EQ A Treb Freq", &values_eq_treb_hz,},

    // RP500 values
    {EQ_LOW_FREQ, EQ_A_POSITION, "EQ A Low Freq", &values_eq_low_freq, xml_eq_low_freq_labels, G_N_ELEMENTS(xml_eq_low_freq_labels)},
    {EQ_MID_FREQ_RP500, EQ_A_POSITION, "EQ A Mid Freq", &values_eq_mid_freq, xml_eq_mid_freq_labels, G_N_ELEMENTS(xml_eq_mid_freq_labels)},
    {EQ_HIGH_FREQ, EQ_A_POSITION, "EQ A High Freq", &values_eq_high_freq, xml_eq_high_freq_labels, G_N_ELEMENTS(xml_eq_high_freq_labels)},

    {EQ_LOW_BANDWIDTH, EQ_A_POSITION, "Low Bandwidth", &values_eq_bandwidth, xml_eq_bandwidth_labels, G_N_ELEMENTS(xml_eq_bandwidth_labels)},
    {EQ_MID_BANDWIDTH, EQ_A_POSITION, "Mid Bandwidth", &values_eq_bandwidth, xml_eq_bandwidth_labels, G_N_ELEMENTS(xml_eq_bandwidth_labels)},
    {EQ_HIGH_BANDWIDTH, EQ_A_POSITION, "High Bandwidth", &values_eq_bandwidth, xml_eq_bandwidth_labels, G_N_ELEMENTS(xml_eq_bandwidth_labels)},

    {EQ_ENABLE, EQ_B_POSITION, "EQ B Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {EQ_TYPE, EQ_B_POSITION, "EQ B Type", &values_eq_type, xml_eq_labels, G_N_ELEMENTS(xml_eq_labels)},
    {EQ_BASS, EQ_B_POSITION, "EQ B Bass", &values_eq_db,},
    {EQ_MID, EQ_B_POSITION, "EQ B Mid", &values_eq_db,},
    {EQ_TREB, EQ_B_POSITION, "EQ B Treb", &values_eq_db,},
    {EQ_PRESENCE, EQ_B_POSITION, "EQ B Presence", &values_eq_db,},
    {EQ_MID_FREQ, EQ_B_POSITION, "EQ B Mid Freq", &values_eq_mid_hz,},
    {EQ_TREB_FREQ, EQ_B_POSITION, "EQ B Treb Freq", &values_eq_treb_hz,},

    {TONE_LIB_TYPE, LIB_POSITION_A, "Tone Lib Type", &values_tone_lib_type, xml_tone_lib_labels, G_N_ELEMENTS(xml_tone_lib_labels)},
    {FX_LIB_TYPE, LIB_POSITION_A, "FX Lib Type", &values_fx_lib_type, xml_fx_lib_labels, G_N_ELEMENTS(xml_fx_lib_labels)},
    {FX_LIB_LEVEL, LIB_POSITION_A, "FxLiblvl", &values_0_to_99,},
    {FX_LIB_LEVEL_MAX1, LIB_POSITION_A, "FxLibLvlMax1", &values_0_to_99,},
    {FX_LIB_LEVEL_MAX2, LIB_POSITION_A, "FxLibLvlMax2", &values_0_to_99,},
    {FX_LIB_LEVEL_MAX3, LIB_POSITION_A, "FxLibLvlMax3", &values_0_to_99,},

    {TONE_LIB_TYPE, LIB_POSITION_B, "Tone Lib B Type", &values_tone_lib_type, xml_tone_lib_labels, G_N_ELEMENTS(xml_tone_lib_labels)},
    {FX_LIB_TYPE, LIB_POSITION_B, "FX Lib B Type", &values_fx_lib_type, xml_fx_lib_labels, G_N_ELEMENTS(xml_fx_lib_labels)},
    {FX_LIB_LEVEL, LIB_POSITION_B, "FxLib B lvl", &values_0_to_99,},
    {FX_LIB_LEVEL_MAX1, LIB_POSITION_B, "FxLib B LvlMax1", &values_0_to_99,},
    {FX_LIB_LEVEL_MAX2, LIB_POSITION_B, "FxLib B LvlMax2", &values_0_to_99,},
    {FX_LIB_LEVEL_MAX3, LIB_POSITION_B, "FxLib B LvlMax3", &values_0_to_99,},
    
    // RP1000 values
    {DELAY_TAP_TIME, DELAY_POSITION, "Delay Tap Time", &values_delay_time,},
    {DELAY_MULTIPLIER, DELAY_POSITION, "Delay Tempo Division", &values_delay_mult, xml_delay_mult_labels, G_N_ELEMENTS(xml_delay_mult_labels)},
    {MOD_PRE_POST, STOMP_LOOP_POSITION, "Stomp Pre/Post", &values_pre_post, xml_pre_post_labels, G_N_ELEMENTS(xml_pre_post_labels)},
    {STOMP_LOOP_ON_OFF, STOMP_LOOP_POSITION, "Stomp Loop Enable", &values_0_to_1,},
    {AMP_LOOP_ON_OFF, AMP_LOOP_POSITION, "Amp Loop Enable", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    
    {VSWITCH_ASSIGN, FOOTSWITCH_6_POSITION, "Footswitch 6 Param", &values_vswitch_assign, xml_vswitch_assign_labels, G_N_ELEMENTS(xml_vswitch_assign_labels)},
    {VSWITCH_MIN, FOOTSWITCH_6_POSITION, "Footswitch 6 Min", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {VSWITCH_MAX, FOOTSWITCH_6_POSITION, "Footswitch 6 Max", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {VSWITCH_ASSIGN, FOOTSWITCH_7_POSITION, "Footswitch 7 Param", &values_vswitch_assign, xml_vswitch_assign_labels, G_N_ELEMENTS(xml_vswitch_assign_labels)},
    {VSWITCH_MIN, FOOTSWITCH_7_POSITION, "Footswitch 7 Min", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {VSWITCH_MAX, FOOTSWITCH_7_POSITION, "Footswitch 7 Max", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {VSWITCH_ASSIGN, FOOTSWITCH_8_POSITION, "Footswitch 8 Param", &values_vswitch_assign, xml_vswitch_assign_labels, G_N_ELEMENTS(xml_vswitch_assign_labels)},
    {VSWITCH_MIN, FOOTSWITCH_8_POSITION, "Footswitch 8 Min", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {VSWITCH_MAX, FOOTSWITCH_8_POSITION, "Footswitch 8 Max", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {VSWITCH_ASSIGN, FOOTSWITCH_9_POSITION, "Footswitch 9 Param", &values_vswitch_assign, xml_vswitch_assign_labels, G_N_ELEMENTS(xml_vswitch_assign_labels)},
    {VSWITCH_MIN, FOOTSWITCH_9_POSITION, "Footswitch 9 Min", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {VSWITCH_MAX, FOOTSWITCH_9_POSITION, "Footswitch 9 Max", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {VSWITCH_ASSIGN, FOOTSWITCH_10_POSITION, "Footswitch 10 Param", &values_vswitch_assign, xml_vswitch_assign_labels, G_N_ELEMENTS(xml_vswitch_assign_labels)},
    {VSWITCH_MIN, FOOTSWITCH_10_POSITION, "Footswitch 10 Min", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},
    {VSWITCH_MAX, FOOTSWITCH_10_POSITION, "Footswitch 10 Max", &values_on_off, xml_on_off_labels, G_N_ELEMENTS(xml_on_off_labels)},


    // Global settings, not part of presets or standard XML.
    {TUNING_REFERENCE, GLOBAL_POSITION, "Tuning Reference", &values_0_to_99,},
    {USB_AUDIO_PLAYBACK_MIX, GLOBAL_POSITION, "USB Audio Playback Mix", &values_0_to_99,},
    {USB_AUDIO_LEVEL, GLOBAL_POSITION, "USB Audio Level", &values_0_to_99,},
    {GUI_MODE_ON_OFF, GLOBAL_POSITION, "GUI Mode", &values_0_to_99,},
    {EXP_PEDAL_LEVEL, GLOBAL_POSITION, "EXP Pedal Level", &values_0_to_99,},
    {STOMP_MODE, GLOBAL_POSITION, "Stomp Mode", &values_0_to_99,},
};

guint n_xml_settings = G_N_ELEMENTS(xml_settings);

gchar *Positions[] = {
    [ GLOBAL_POSITION ] = "Global",
    [ PICKUP_POSITION ] = "Pickup",
    [ WAH_POSITION ] = "Wah",
    [ COMP_POSITION ] = "Compressor",
    [ GNX3K_WHAM_POSITION ] = "Gnx3K Wham",
    [ DIST_POSITION ] = "Distortion",
    [ AMP_CHANNEL_POSITION ] = "Amp Channel",
    [ GNX_CHANNEL_POSITION ] = "Gnx Channel",
    [ AMP_A_POSITION ] = "Amp A",
    [ AMP_CAB_POSITION ] = "Amp Cab A",
    [ AMP_B_POSITION ] = "Amp B",
    [ AMP_CAB_B_POSITION ] = "Amp Cab B",
    [ NOISEGATE_POSITION ] = "Noise Gate",
    [ VOLUME_PRE_FX_POSITION ] = "Volume Pre Fx",
    [ CHORUSFX_POSITION ] = "Chorus Fx",
    [ DELAY_POSITION ] = "Delay",
    [ REVERB_POSITION ] = "Reverb",
    [ VOLUME_POST_FX_POSITION ] = "Volume Post Fx",
    [ PRESET_POSITION ] = "Preset",
    [ EXP_POSITION ] = "Expression",
    [ WAH_POSITION_MIN_MAX ] = "Wah Min Max",
    [ VSWITCH_ASSIGN_POSITION ] = "Vswitch",
    [ LFO1_POSITION ] = "LFO 1",
    [ LFO2_POSITION ] = "LFO 2",
    [ EQ_A_POSITION ] = "EQ A",
    [ EQ_B_POSITION ] = "EQ B",
    [ LIB_POSITION_A ] = "Library A",
    [ LIB_POSITION_B ] = "Library B",
    [ AMP_LOOP_POSITION ] = "Amp Loop",
    [ STOMP_LOOP_POSITION ] = "Stomp Loop",
};

guint max_position = G_N_ELEMENTS(Positions);

gchar *
get_position (guint position)
{
    if (position > max_position) {
        return "";
    }

    return Positions[position];
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/**
 *  \param id modifier ID
 *  \param position modifier position
 *
 *  Gets modifier info.
 *
 *  \return Modifier which must not be freed, or NULL if no matching Modifier has been found.
*/
static Modifier *get_modifier(guint id, guint position)
{
    gint x;

    for (x=0; x<n_modifiers; x++)
        if ((modifiers[x].id == id) && (modifiers[x].position == position))
            return &(modifiers[x]);

    g_warning("Failed to find modifier for id %d position %d", id, position);

    return NULL;
}

/**
 *  \param values possible setting values
 *
 *  Creates EffectSettings containing expression pedal min and max settings.
 *
 *  \return EffectSettings which must be freed using effect_settings_free.
 **/
static EffectSettings *get_modifier_settings(EffectValues *values)
{
    if (values == NULL)
        return NULL;

    /** \todo reuse exsisting settings if values is the same */
    EffectSettings *settings = g_slice_alloc0(2 * sizeof(EffectSettings));
    settings[0].id = EXP_MIN;
    settings[1].id = EXP_MAX;

    settings[0].label = "Min";
    settings[1].label = "Max";

    settings[0].position = settings[1].position = EXP_POSITION;

    settings[0].values = settings[1].values = values;

    return settings;
}

/**
 *  \param settings settings to be freed
 *
 *  Frees all memory used by EffectSettings.
 **/
static void effect_settings_free(EffectSettings *settings)
{
    g_slice_free1(2 * sizeof(EffectSettings), settings);
}

/**
 * Global holding the list of linkable parameters.
 *
 * Used for Pedal Assignment and the LFO's.
 */
ModifierGroup *ModifierLinkableList;

EffectGroup *get_modifier_group(void)
{
    EffectGroup *group = NULL;
    if (ModifierLinkableList) {
        group = ModifierLinkableList->group;
    }
    return group;
}

guint get_modifier_amt(void)
{
    guint amt = 0;
    if (ModifierLinkableList) {
        amt = ModifierLinkableList->group_amt;
    }
    return amt;
}

/**
 *  \param modifier_group group to be freed
 *
 *  Frees all memory used by ModifierGroup.
 **/
static void modifier_group_free(ModifierGroup *modifier_group)
{
    g_return_if_fail(modifier_group != NULL);

    int x;
    for (x=0; x<modifier_group->group_amt; x++) {
        if (modifier_group->group[x].settings)
            /* The settings for the EXP_POSITION are dynamically allocated. */
            modifier_settings_exp_free(modifier_group->group[x].settings);
            effect_settings_free(modifier_group->group[x].settings);
    }
    g_slice_free1(modifier_group->group_amt * sizeof(EffectGroup),
                  modifier_group->group);
    g_slice_free(ModifierGroup, modifier_group);
}
/**
 *  Retrieves modifier linkable group from device and updates the
 *  global list of linkable parameters. The old list is freed.
 *
 *  \param msg    A buffer containing the message with the list of
 *                linkable parameters.
 *  
 **/
void update_modifier_linkable_list(GString *msg)
{
    guint group_id;
    guint count;
    guint i;

    unsigned char *str = (unsigned char*)msg->str;

    group_id = (str[8] << 8) | str[9];
    count = (str[10] << 8) | str[11];

    ModifierGroup *modifier_group = g_slice_new(ModifierGroup);

    modifier_group->type = EXP_TYPE;
    modifier_group->position = EXP_POSITION;

    debug_msg(DEBUG_MSG2HOST|DEBUG_GROUP,
              "RECEIVE_MODIFIER_LINKABLE_LIST: Group %d count %d",
              group_id, count);

    EffectGroup *group = g_slice_alloc(count * sizeof(EffectGroup));

    for (i=0; i<count; i++) {
        guint id = (str[12 + (i*3)] << 8) | str[13 + (i*3)];
        guint position = str[14 + (i*3)];

        group[i].type = (position << 16) | id;

        Modifier *modifier = get_modifier(id, position);
        if (modifier) {
            group[i].label = modifier->label;
            group[i].settings = get_modifier_settings(modifier->values);
            group[i].settings_amt = 2;
        } else {
            // The string is leaked when the modifier list is updated. 
            group[i].label = g_strdup_printf("Unknown pos %d id %d", position, id);
            group[i].settings = NULL;
        }

        if (group[i].settings == NULL)
            group[i].settings_amt = 0;

        debug_msg(DEBUG_MSG2HOST|DEBUG_GROUP,
                  "Position : %d\nID       : %d\nName     : %s\n",
                  position, id, modifier ? modifier->label : NULL);
    }

    modifier_group->group = group;
    modifier_group->group_amt = count;

    if (ModifierLinkableList) {
        modifier_group_free(ModifierLinkableList);
        ModifierLinkableList = NULL;
    }
    ModifierLinkableList = modifier_group;
}


/**
 *  \param values EffectValues to examine
 *  \param min return location for minimum value
 *  \param max return location for maximum value
 *  \param custom return location for custom flag
 *
 *  Retrieves information about provided EffectValues, custom is set to TRUE if values type isn't VALUE_TYPE_PLAIN.
 **/
void get_values_info(EffectValues *values,
                     gdouble *min, gdouble *max, gboolean *custom)
{
    g_return_if_fail(values != NULL);

    *min = values->min;
    *custom = (values->type != VALUE_TYPE_PLAIN);

    while ((values->type & VALUE_TYPE_EXTRA) && (values->extra != NULL))
        values = values->extra;

    *max = values->max;
}

/**
 *  \param device_id Device ID
 *  \param family_id Family ID
 *  \param product_id Product ID
 *  \param device Variable to hold device information
 *
 *  Gets appropiate effect list basing on device, family and product IDs.
 *
 *  \return TRUE if list and n_list were set, FALSE otherwise.
 **/
gboolean get_device_info(unsigned char device_id, unsigned char family_id,
                         unsigned char product_id,
                         Device **device)
{
    int x;
    for (x = 0; x < G_N_ELEMENTS(supported_devices); x++) {
        if (supported_devices[x]->product_id == product_id && supported_devices[x]->family_id == family_id) {
            *device = supported_devices[x];
            return TRUE;
        }
    }
    return FALSE;
}

