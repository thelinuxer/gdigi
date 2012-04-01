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

#ifndef GDIGI_H
#define GDIGI_H

#include <glib.h>
#include <glib-object.h>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

typedef enum {
    DEBUG_MSG2DEV   = (1 << 0),     // Device bound messages.
    DEBUG_MSG2HOST  = (1 << 1),     // Host bound messages.
    DEBUG_STARTUP   = (1 << 2),
    DEBUG_GROUP     = (1 << 3),     // Modifier group
    DEBUG_HEX       = (1 << 4),     // Dump message contents in hex.
    DEBUG_XML       = (1 << 5),     
    DEBUG_VERBOSE   = (1 << 6),     
} debug_flags_t;

void debug_msg (debug_flags_t, char *fmt, ...);
gboolean debug_flag_is_set (debug_flags_t flag);

#define GNX_CHANNEL_POSITION 7
#define GNX_CHANNEL_AMP 260
#define GNX_WARP 261
#define GNX_AMP_WARP 262
#define GNX_CABINET_WARP 263
#define GNX_CHANNEL_FS_MODE 264

unsigned char product_id;

enum {
  GNX3K_WAH_TYPE_CRY = 129,
  GNX3K_WAH_TYPE_BOUTIQUE = 130,
  GNX3K_WAH_TYPE_FULLRANGE = 131,

  WAH_TYPE_CRY = 132,
  WAH_TYPE_FULLRANGE = 133,
  WAH_TYPE_CLYDE = 134
};

#define WAH_POSITION_MIN_MAX 20

#define WAH_MIN 8195
#define WAH_MAX 8196

#define WAH_TYPE 128
#define WAH_ON_OFF 129
#define WAH_POSITION 3

#define WAH_PEDAL_POSITION 132
#define WAH_VOLUME_BOOST 133

#define WAH_LEVEL 133

enum {
  COMP_TYPE_DIGI = 195,
  COMP_TYPE_CS = 196,
  COMP_TYPE_DYNA = 197
};

#define GNX3K_WHAM_TYPE 768
#define GNX3K_WHAM_ENABLE 769
#define GNX3K_WHAM_POSITION 5
#define GNX3K_DETUNE_AMOUNT 1670
#define GNX3K_PITCH_AMOUNT 1732
#define GNX3K_PITCH_LEVEL 1731
#define GNX3K_TALK_LEVEL 2818

enum {
  GNX3K_WHAM_TYPE_WHAMMY = 1344,
  GNX3K_WHAM_TYPE_IPS = 1345,
  GNX3K_WHAM_TYPE_DETUNE = 1346,
  GNX3K_WHAM_TYPE_PITCH = 1347,
  GNX3K_WHAM_TYPE_TALK1 = 1348,
  GNX3K_WHAM_TYPE_TALK2 = 1349,
  GNX3K_WHAM_TYPE_TALK3 = 1350,
  GNX3K_WHAM_TYPE_TALK4 = 1351,
  GNX3K_WHAM_TYPE_TALK5 = 1352
};

#define COMP_TYPE 207
#define COMP_ON_OFF 193
#define COMP_POSITION 4

#define GNX3K_COMP_ATTACK 194
#define GNX3K_COMP_RATIO 195
#define GNX3K_COMP_THRESHOLD 200
#define GNX3K_COMP_GAIN 201

#define COMP_SUSTAIN 208
#define COMP_TONE 209
#define COMP_ATTACK 211
#define COMP_LEVEL 210
#define COMP_SENSITIVITY 213
#define COMP_OUTPUT 212

enum {
  PICKUP_TYPE_SC_HB = 65,
  PICKUP_TYPE_HB_SC = 66,
};

#define PICKUP_TYPE 64
#define PICKUP_ON_OFF 65
#define PICKUP_POSITION 2

enum {
  DIST_TYPE_SCREAMER = 1280,
  DIST_TYPE_808 = 1292,
  DIST_TYPE_TS_MOD = 1301,
  DIST_TYPE_SD_ODRV = 1302,
  DIST_TYPE_OD_ODRV = 1299,
  DIST_TYPE_SPARKDRIVE = 1286,
  DIST_TYPE_GUYOD = 1285,
  DIST_TYPE_DOD250 = 1283,
  DIST_TYPE_REDLINE = 1297,
  DIST_TYPE_AMPDRIVR = 1298,
  DIST_TYPE_OC_DRIVE = 1300,
  DIST_TYPE_RODENT = 1281,
  DIST_TYPE_MX = 1291,
  DIST_TYPE_DS = 1282,
  DIST_TYPE_GRUNGE = 1287,
  DIST_TYPE_ZONE = 1289,
  DIST_TYPE_DEATH = 1294,
  DIST_TYPE_GONK = 1293,
  DIST_TYPE_8TAVIA = 1290,
  DIST_TYPE_FUZZLATOR = 1295,
  DIST_TYPE_CLASSIC_FUZZ = 1296,
  DIST_TYPE_FUZZY = 1288,
  DIST_TYPE_MP = 1284
};

#define DIST_TYPE 2432
#define DIST_ON_OFF 2433
#define DIST_POSITION 6

#define DIST_SCREAMER_DRIVE 2434
#define DIST_SCREAMER_TONE  2435
#define DIST_SCREAMER_LVL   2436

#define DIST_808_OVERDRIVE  2473
#define DIST_808_TONE       2474
#define DIST_808_LVL        2475

#define DIST_TS_MOD_DRIVE 2562
#define DIST_TS_MOD_TONE  2564
#define DIST_TS_MOD_LVL   2563

#define DIST_SD_ODRV_DRIVE 2565
#define DIST_SD_ODRV_TONE  2566
#define DIST_SD_ODRV_LVL   2567

#define DIST_OD_ODRV_OVERDRIVE 2568
#define DIST_OD_ODRV_LVL   2569

#define DIST_SPARKDRIVE_GAIN 2450
#define DIST_SPARKDRIVE_TONE 2451
#define DIST_SPARKDRIVE_CLEAN 2452
#define DIST_SPARKDRIVE_VOLUME 2453

#define DIST_GUYOD_DRIVE    2448
#define DIST_GUYOD_LVL      2449

#define DIST_DOD250_GAIN    2443
#define DIST_DOD250_LVL     2444

#define DIST_REDLINE_GAIN   2488
#define DIST_REDLINE_LOW    2489
#define DIST_REDLINE_HIGH   2490
#define DIST_REDLINE_LEVEL  2491

#define DIST_AMPDRIVR_GAIN  2570
#define DIST_AMPDRIVR_MIDBOOST  2571
#define DIST_AMPDRIVR_LVL   2572

#define DIST_OC_DRIVE_DRIVE 2492
#define DIST_OC_DRIVE_TONE  2494
#define DIST_OC_DRIVE_HP_LP 2493
#define DIST_OC_DRIVE_LVL   2495

#define DIST_RODENT_DIST    2437
#define DIST_RODENT_FILTER  2438
#define DIST_RODENT_LVL     2439

#define DIST_MX_DIST        2468
#define DIST_MX_OUTPUT      2469

#define DIST_DS_GAIN        2440
#define DIST_DS_TONE        2441
#define DIST_DS_LVL         2442

#define DIST_GRUNGE_GRUNGE  2454
#define DIST_GRUNGE_FACE    2456
#define DIST_GRUNGE_LOUD    2457
#define DIST_GRUNGE_BUTT    2455

#define DIST_ZONE_GAIN      2460
#define DIST_ZONE_LOW       2463
#define DIST_ZONE_MID_LVL   2462
#define DIST_ZONE_MID_FREQ  2461
#define DIST_ZONE_HIGH      2464
#define DIST_ZONE_LEVEL     2465

#define DIST_DEATH_LOW      2477
#define DIST_DEATH_MID      2476
#define DIST_DEATH_HIGH     2479
#define DIST_DEATH_LVL      2478

#define DIST_GONK_GONK      2480
#define DIST_GONK_SMEAR     2471
#define DIST_GONK_SUCK      2470
#define DIST_GONK_HEAVE     2472

#define DIST_8TAVIA_DRIVE   2466
#define DIST_8TAVIA_VOLUME  2467

#define DIST_FUZZLATOR_FUZZ 2481
#define DIST_FUZZLATOR_TONE 2482
#define DIST_FUZZLATOR_LOOSETIGHT 2483
#define DIST_FUZZLATOR_VOLUME 2484

#define DIST_CLASSIC_FUZZ_FUZZ 2485
#define DIST_CLASSIC_FUZZ_TONE 2486
#define DIST_CLASSIC_FUZZ_VOLUME 2487

#define DIST_FUZZY_FUZZ     2458
#define DIST_FUZZY_VOLUME   2459

#define DIST_MP_SUSTAIN     2445
#define DIST_MP_TONE        2446
#define DIST_MP_VOLUME      2447

#define VOLUME_PRE_FX_POSITION 13
#define VOLUME_POST_FX_POSITION 17

#define PRESET_POSITION 18
#define PRESET_LEVEL 2626

enum {
  AMP_TYPE_TWEED_CHAMP = 307,
  AMP_TYPE_TWEED_DELUXE = 308,
  AMP_TYPE_TWEED_BASSMAN = 309,
  AMP_TYPE_BROWN_BASSMAN = 310,
  AMP_TYPE_BLACKFACE_TWIN = 311,
  AMP_TYPE_BLACKFACE_DELUXE = 312,
  AMP_TYPE_PLEXI_JTM_45 = 313,
  AMP_TYPE_SUPER_LEAD_PLEXI = 314,
  AMP_TYPE_68_MARSHALL_JUMP = 315,
  AMP_TYPE_MASTER_VOLUME = 316,
  AMP_TYPE_JCM800 = 317,
  AMP_TYPE_JCM900 = 318,
  AMP_TYPE_JCM2000 = 319,
  AMP_TYPE_AC15 = 322,
  AMP_TYPE_AC30TB = 323,
  AMP_TYPE_HIWATT_100 = 324,
  AMP_TYPE_BOOGIE_MARK_II = 320,
  AMP_TYPE_BOOGIE_MARK_IV = 371,
  AMP_TYPE_DUAL_RECTIFIER = 321,
  AMP_TYPE_TRIPLE_RECTIFIER = 370,
  AMP_TYPE_22_CALIBR = 386,
  AMP_TYPE_LEGACY_VL100 = 327,
  AMP_TYPE_MATCHLESS_HC30 = 326,
  AMP_TYPE_CHIEF = 385,
  AMP_TYPE_SOLDANO_100 = 325,
  AMP_TYPE_SUPERGROUP = 381,
  AMP_TYPE_GA40 = 380,
  AMP_TYPE_OR120 = 372,
  AMP_TYPE_PV5150II = 373,
  AMP_TYPE_RG100 = 374,
  AMP_TYPE_JC120_JAZZ = 375,
  AMP_TYPE_SOLAR100 = 376,
  AMP_TYPE_SOLO = 331,
  AMP_TYPE_METAL = 332,
  AMP_TYPE_BRIGHT = 333,
  AMP_TYPE_CHUNK = 334,
  AMP_TYPE_DIGITECH_CLEAN = 335,
  AMP_TYPE_HIGH_GAIN = 337,
  AMP_TYPE_BLUES = 338,
  AMP_TYPE_FUZZ = 339,
  AMP_TYPE_SPANK = 330,
  AMP_TYPE_GSP2101_CLEAN_TUBE = 328,
  AMP_TYPE_GSP2101_SAT_TUBE = 329,
  AMP_TYPE_CRUNCH = 336,
  AMP_TYPE_MONSTER = 377,
  AMP_TYPE_TWEEDFACE = 378,
  AMP_TYPE_BLACKBASS = 379,
  AMP_TYPE_STONER_ROCK = 368,
  AMP_TYPE_DARK_METAL = 369,
  AMP_TYPE_TRANSISTOR = 382,
  AMP_TYPE_BROWN_SOUND = 383,
  AMP_TYPE_MOSH = 384,
  AMP_TYPE_ACOUSTIC = 341,
  AMP_TYPE_JUMBO_ACOUSTIC = 340,
  AMP_TYPE_DIRECT = 306,
  AMP_TYPE_SVT_ROCK_BASS = 342,
  AMP_TYPE_SVT_CLASSIC_BASS = 343,
  AMP_TYPE_PEG_B15_BASS = 344,
  AMP_TYPE_BASIC_BASS = 345,
  AMP_TYPE_SHOWMAN_BASS = 346,
  AMP_TYPE_ASH_MODERN_BASS = 347,
  AMP_TYPE_BRIT_BASS = 348,
  AMP_TYPE_SOLAR_BASS = 349,
  AMP_TYPE_BOOGIE_BASS = 350,
  AMP_TYPE_HART_BASS = 351,
};

enum {
  EQ_TYPE_BRIGHT = 1474,
  EQ_TYPE_MIDBOOST = 1472,
  EQ_TYPE_SCOOP = 1473,
  EQ_TYPE_WARM = 1475
};

#define AMP_TYPE 2496
#define AMP_ON_OFF 265
#define AMP_A_POSITION 8
#define AMP_B_POSITION 10

#define AMP_LOOP_ON_OFF 3649
#define AMP_LOOP_POSITION 33

#define AMP_BYPASS_ON_OFF 12361
#define AMP_BYPASS_POSITION 0

#define AMP_CHANNEL 256
#define AMP_CHANNEL_POSITION 7

#define AMP_CHANNEL_A 0
#define AMP_CHANNEL_B 1
#define AMP_CHANNEL_WARP 2

#define AMP_GAIN 2497
#define AMP_LEVEL 2498
#define AMP_BASS_FREQ 2499
#define AMP_BASS_LEVEL 2500
#define AMP_MID_FREQ 2501
#define AMP_MID_LEVEL 2502
#define AMP_TREBLE_FREQ 2503
#define AMP_TREBLE_LEVEL 2504
#define AMP_EQ_ON_OFF 2505
#define AMP_PRESENCE 2506
#define AMP_BASS 2507
#define AMP_MID 2508
#define AMP_TREBLE 2509

#define AMP_CAB_TYPE 2560
#define AMP_CAB_TUNING 2561
#define AMP_CAB_POSITION 9
#define AMP_CAB_B_POSITION 11

enum {
  AMP_CAB_DIRECT = 570,
  AMP_CAB_CHAMP = 571,
  AMP_CAB_DELUXE = 572,
  AMP_CAB_DELUXE_REVERB = 573,
  AMP_CAB_BRITISH1_12 = 623,
  AMP_CAB_GA1_12 = 624,
  AMP_CAB_BLONDE2_12 = 577,
  AMP_CAB_TWIN = 576,
  AMP_CAB_BRITISH2_12 = 613,
  AMP_CAB_JAZZ2_12 = 626,
  AMP_CAB_JBL_215 = 627,
  AMP_CAB_BASSMAN = 579,
  AMP_CAB_BRITISH4_12 = 614,
  AMP_CAB_BRITISH_GREEN = 616,
  AMP_CAB_FANE4_12 = 584,
  AMP_CAB_BOUTIQUE4_12 = 583,
  AMP_CAB_VINTAGE = 622,
  AMP_CAB_RECTO4_12 = 625,
  AMP_CAB_DIGI_SOLO = 609,
  AMP_CAB_DIGI_BRIGHT = 611,
  AMP_CAB_DIGI_METAL = 618,
  AMP_CAB_DIGI_ROCK = 619,
  AMP_CAB_DIGI_ALT = 620,
  AMP_CAB_DIGI_VNTG = 621,
  AMP_CAB_DIGI_CHUNK = 612,
  AMP_CAB_DIGI_SPANK2_12 = 608,
  AMP_CAB_DIGI_SPKR_COMP = 585
};

enum {
  GNX_AMP_CAB_DIRECT = 570,
  GNX_AMP_CAB_TWEED1_8 = 571,
  GNX_AMP_CAB_TWEED1_12 = 572,
  GNX_AMP_CAB_BLACKFACE1_12 = 573,
  GNX_AMP_CAB_BRITISH1_12 = 574,
  GNX_AMP_CAB_BLACKFACE2_12 = 576,
  GNX_AMP_CAB_BLONDE2_12 = 577,
  GNX_AMP_CAB_BRITISH2_12 = 578,
  GNX_AMP_CAB_TWEED4_10 = 579,
  GNX_AMP_CAB_BRITISH_70_4_12 = 580,
  GNX_AMP_CAB_BRITISH_GREEN4_12 = 581,
  GNX_AMP_CAB_STRAIGHT_V30_4_12 = 582,
  GNX_AMP_CAB_SLANT_V30_4_12 = 583,
  GNX_AMP_CAB_FANE4_12 = 584,
  GNX_AMP_CAB_2101_SPKR_COMP = 585,
  GNX_AMP_CAB_JUMBO_ACOUSTIC = 606,
  GNX_AMP_CAB_DREAD_ACOUSTIC = 607,
  GNX_AMP_CAB_DIGI_SPANK = 608,
  GNX_AMP_CAB_DIGI_SOLO = 609,
  GNX_AMP_CAB_DIGI_METAL = 610,
  GNX_AMP_CAB_DIGI_BRIGHT = 611,
  GNX_AMP_CAB_DIGI_CHUNK = 612,
  GNX_AMP_CAB_HART_BASS1_15 = 586,
  GNX_AMP_CAB_BASIC_BASS1_15 = 587,
  GNX_AMP_CAB_PORTA_BASS1_15 = 588,
  GNX_AMP_CAB_REFLEX1_18 = 589,
  GNX_AMP_CAB_SOLAR_BASS2_15 = 590,
  GNX_AMP_CAB_DE_BASS4_10 = 591,
  GNX_AMP_CAB_ASH_BASS4_10 = 592,
  GNX_AMP_CAB_GOLIATH_BASS4_10 = 593,
  GNX_AMP_CAB_HART_BASS4_10 = 594,
  GNX_AMP_CAB_SVT_BASS8_10 = 595,
};

#define EQ_A_POSITION 24
#define EQ_B_POSITION 25

#define EQ_TYPE 3202
#define EQ_BASS 3203
#define EQ_MID 3204
#define EQ_TREB 3205
#define EQ_MID_FREQ 3206
#define EQ_PRESENCE 3207
#define EQ_TREB_FREQ 3211
#define EQ_ENABLE 3212

#define EQ_LOW_FREQ 3213
#define EQ_MID_FREQ_XXX 3214
#define EQ_HIGH_FREQ 3215

#define EQ_TREBLE_FREQ 3215
#define EQ_LOW_BANDWIDTH 3216
#define EQ_MID_BANDWIDTH 3217
#define EQ_HIGH_BANDWIDTH 3218

enum {
  NOISEGATE_GATE = 768,
  NOISEGATE_SWELL = 769
};

#define NOISEGATE_TYPE 704
#define NOISEGATE_ON_OFF 705
#define NOISEGATE_POSITION 12

#define GNX3K_GATE_ATTACK 706

/* available only in Gate mode */
#define NOISEGATE_GATE_TRESHOLD 710
/* available only in Swell mode */
#define NOISEGATE_SWELL_SENS    711
/* available in both Gate and Swell modes */
#define NOISEGATE_ATTACK        712
#define NOISEGATE_RELEASE       713
#define NOISEGATE_ATTN          714

enum {
  GNX3K_MOD_TYPE_CHORUS = 857,
  GNX3K_MOD_TYPE_FLANGER = 858,
  GNX3K_MOD_TYPE_TRIGFLANGER = 859,
  GNX3K_MOD_TYPE_PHASER = 860,
  GNX3K_MOD_TYPE_TRIGPHASER = 861,
  GNX3K_MOD_TYPE_TREMOLO = 862,
  GNX3K_MOD_TYPE_PANNER = 863,
  GNX3K_MOD_TYPE_VIBRATO = 864,
  GNX3K_MOD_TYPE_ROTARY = 865,
  GNX3K_MOD_TYPE_AUTOYA = 866,
  GNX3K_MOD_TYPE_YAYA = 867,
  GNX3K_MOD_TYPE_SYNTHTALK = 868,
  GNX3K_MOD_TYPE_ENVELOPE = 869,
  GNX3K_MOD_TYPE_DETUNE = 870,
  GNX3K_MOD_TYPE_PITCH = 871,
  GNX3K_MOD_TYPE_UNOVIBE = 880,
};

enum {
  CHORUS_TYPE_CE = 891,
  CHORUS_TYPE_TC = 892,
  CHORUS_TYPE_DUAL = 889,
  CHORUS_TYPE_GLISTEN = 914,
  CHORUS_TYPE_MULTI = 890,
  CHORUS_TYPE_VOO_DOO = 918,
  CHORUS_TYPE_CLONE = 919,
  CHORUS_TYPE_FLANGER = 893,
  CHORUS_TYPE_TRIGGERED_FLANGER = 894,
  CHORUS_TYPE_FLTFLANGER = 920,
  CHORUS_TYPE_MXR_FLANGER = 895,
  CHORUS_TYPE_EH_FLANGER = 896,
  CHORUS_TYPE_AD_FLANGER = 915,
  CHORUS_TYPE_PHASER = 897,
  CHORUS_TYPE_TRIGGERED_PHASER = 898,
  CHORUS_TYPE_MX_PHASER = 899,
  CHORUS_TYPE_EH_PHASER = 900,
  CHORUS_TYPE_VIBRATO = 864,
  CHORUS_TYPE_ROTARY = 865,
  CHORUS_TYPE_VIBROPAN = 911,
  CHORUS_TYPE_UNOVIBE = 912,
  CHORUS_TYPE_TREMOLO = 862,
  CHORUS_TYPE_SCATTER_TREM = 916,
  CHORUS_TYPE_OPTO_TREMOLO = 904,
  CHORUS_TYPE_BIAS_TREMOLO = 905,
  CHORUS_TYPE_PANNER = 863,
  CHORUS_TYPE_ENVELOPE = 906,
  CHORUS_TYPE_FX25 = 910,
  CHORUS_TYPE_AUTOYA = 907,
  CHORUS_TYPE_YAYA = 908,
  CHORUS_TYPE_SYNTH_TALK = 913,
  CHORUS_TYPE_STEP_FILTER = 909,
  CHORUS_TYPE_SAMPLE_HOLD = 917,
  CHORUS_TYPE_WHAMMY = 1344,
  CHORUS_TYPE_PITCH_SHIFT = 1347,
  CHORUS_TYPE_DETUNE = 1346,
  CHORUS_TYPE_IPS = 1345, // Also known as Harmony
  CHORUS_TYPE_OCTAVER = 901,
};

#define MOD_TYPE 768
#define MOD_POSITION 768
#define MOD_PRE_POST 1798

#define CHORUSFX_TYPE 768
#define CHORUSFX_ON_OFF 769
#define CHORUSFX_PRE_POST 770

#define CHORUSFX_POSITION 14
#define CHORUSFX_PRE 1543
#define CHORUSFX_POST 1544

#define CHORUS_SPEED 837
#define CHORUS_DEPTH 838
#define CHORUS_PREDELAY 839

#define CHORUS_WIDTH 848
#define CHORUS_INTENSITY 849

enum {
    CHORUS_WAVEFORM_TRI = 0,
    CHORUS_WAVEFORM_SINE = 1,
    CHORUS_WAVEFORM_SQUARE = 2,
};

#define CHORUS_LEVEL 836
#define CHORUS_WAVE 840
#define CHORUS_BALANCE 841

#define CHORUS_RATE 850

#define FLANGER_SPEED 902
#define FLANGER_DEPTH 903
#define FLANGER_REGEN 904
#define FLANGER_LEVEL 901
#define FLANGER_WAVE 905
#define FLANGER_BALANCE 906

#define TRIG_FLANGER_SPEED 1030
#define TRIG_FLANGER_SENS 1031
#define TRIG_FLANGER_LFO_START 1028
#define TRIG_FLANGER_MIX 1029
#define TRIG_FLANGER_LEVEL 1032

#define FLTFLANGER_FREQ 922

#define MXR_FLANGER_WIDTH 914
#define MXR_FLANGER_MANUAL 917

#define EH_FLANGER_RATE 918
#define EH_FLANGER_RANGE 919
#define EH_FLANGER_COLOR 916

#define AD_FLANGER_ENHANCE 920
#define AD_FLANGER_HARMONICS 921

#define PHASER_SPEED 962
#define PHASER_DEPTH 963
#define PHASER_REGEN 966
#define PHASER_LEVEL 965
#define PHASER_WAVE 967
#define PHASER_BALANCE 968

#define TRIG_PHASER_SPEED 1094
#define TRIG_PHASER_SENS 1095
#define TRIG_PHASER_LFO_START 1092
#define TRIG_PHASER_MIX 1093
#define TRIG_PHASER_LEVEL 1096

#define MX_PHASER_INTENSITY 976

#define EH_PHASER_RATE 979
#define EH_PHASER_COLOR 977

#define VIBRATO_SPEED 1284
#define VIBRATO_DEPTH 1285
#define VIBRATO_WAVEFORM 1286

#define ROTARY_SPEED 1346
#define ROTARY_INTENSITY 1348
#define ROTARY_MIX 1349
#define ROTARY_DOPPLER 1350
#define ROTARY_CROSSOVER 1351
#define ROTARY_BALANCE 1352

#define VIBROPAN_SPEED 1314
#define VIBROPAN_DEPTH 1315
#define VIBROPAN_VIBRA 1316
#define VIBROPAN_WAVE 1317

#define UNOVIBE_PEDAL_SPEED 2884
#define UNOVIBE_INTENSITY 2883
#define UNOVIBE_CHORUS_VIBRATO 2882
#define UNOVIBE_VOLUME 2885

#define TREMOLO_SPEED 1156
#define TREMOLO_DEPTH 1155
#define TREMOLO_WAVE 1157

#define PANNER_SPEED 1220
#define PANNER_DEPTH 1219
#define PANNER_WAVE 1221

#define ENVELOPE_MIX 1604
#define ENVELOPE_SENSITIVITY 1606
#define ENVELOPE_RANGE 1605
#define ENVELOPE_BALANCE 1607
#define ENVELOPE_BLEND 1608

#define GNX3K_AUTOYA_RANGE 1476
#define AUTOYA_MIX 1477
#define AUTOYA_SPEED 1478
#define AUTOYA_DEPTH 1479
#define AUTOYA_BALANCE 1481
#define AUTOYA_INTENSITY 1482
#define AUTOYA_RANGE 1483

#define YAYA_PEDAL 1410
#define GNX3K_YAYA_RANGE 1412
#define YAYA_MIX 1413
#define YAYA_DEPTH 1414
#define YAYA_BALANCE 1416
#define YAYA_INTENSITY 1417
#define YAYA_RANGE 1418

#define SYNTH_TALK_ATTACK 1542
#define GNX3K_SYNTH_TALK_RELEASE 1543
#define SYNTH_TALK_RELEASE 1547
#define SYNTH_TALK_SENS 1544
#define SYNTH_TALK_VOX 1540
#define SYNTH_TALK_BALANCE 1545

#define STEP_FILTER_SPEED 3010
#define STEP_FILTER_INTENSITY 3011

#define SAMPLE_HOLD_SPEED 3012
#define SAMPLE_HOLD_INTENSITY 3013

#define WHAMMY_AMOUNT 1797
#define WHAMMY_PEDAL 1795
#define WHAMMY_MIX 1796

enum whammy_amt {
    WHAMMY_TYPE_OCT_UP = 0,
    WHAMMY_TYPE_2OCT_UP = 1,
    WHAMMY_TYPE_2ND_DN = 2,
    WHAMMY_TYPE_RV2ND_DN = 3,
    WHAMMY_TYPE_4TH_DN = 4,
    WHAMMY_TYPE_OCT_DN = 5,
    WHAMMY_TYPE_2OCT_DN = 6,
    WHAMMY_TYPE_DIV_BMB = 7,
    WHAMMY_TYPE_M3_GT_MA3 = 8,
    WHAMMY_TYPE_2ND_MA3 = 9,
    WHAMMY_TYPE_3RD_4TH = 10,
    WHAMMY_TYPE_4TH_5TH = 11,
    WHAMMY_TYPE_5TH_OCT = 12,
    WHAMMY_TYPE_HOCT_UP = 13,
    WHAMMY_TYPE_HOCT_DN = 14,
    WHAMMY_TYPE_OCT_GT_D = 15,
};

#define PITCH_AMOUNT 1730
#define PITCH_BALANCE 1733
#define PITCH_MIX 1745

#define DETUNE_LEVEL 1667
#define DETUNE_AMOUNT 1668
#define DETUNE_BALANCE 1669

#define IPS_SHIFT_AMOUNT 2754
#define IPS_KEY 2756
#define IPS_SCALE 2755
#define IPS_LEVEL 2757

enum {
    IPS_KEY_E = 0,
    IPS_KEY_F = 1,
    IPS_KEY_Gb = 2,
    IPS_KEY_G = 3,
    IPS_KEY_Ab = 4,
    IPS_KEY_A = 5,
    IPS_KEY_Bb = 6,
    IPS_KEY_B = 7,
    IPS_KEY_C = 8,
    IPS_KEY_Db = 9,
    IPS_KEY_D = 10,
    IPS_KEY_Eb = 11,
};

enum {
    IPS_SHIFT_OCT_DN = 0,
    IPS_SHIFT_7TH_DN = 1,
    IPS_SHIFT_6TH_DN = 2,
    IPS_SHIFT_5TH_DN = 3,
    IPS_SHIFT_4TH_DN = 4,
    IPS_SHIFT_3RD_DN = 5,
    IPS_SHIFT_2ND_DN = 6,
    IPS_SHIFT_2ND_UP = 7,
    IPS_SHIFT_3RD_UP = 8,
    IPS_SHIFT_4TH_UP = 9,
    IPS_SHIFT_5TH_UP = 10,
    IPS_SHIFT_6TH_UP = 11,
    IPS_SHIFT_7TH_UP = 12,
    IPS_SHIFT_OCT_UP = 13,
};

enum {
    IPS_SCALE_MAJOR = 0,
    IPS_SCALE_MINOR = 1,
    IPS_SCALE_DORIAN = 2,
    IPS_SCALE_MIXOLYDIAN = 3,
    IPS_SCALE_LYDIAN = 4,
    IPS_SCALE_HMINOR = 5,
};
    
#define OCTAVER_OCTAVE1 1746
#define OCTAVER_OCTAVE2 1747
#define OCTAVER_DRY_LEVEL 1748

enum {
  DELAY_TYPE_ANALOG = 1046,
  DELAY_TYPE_DIGITAL = 1045,
  DELAY_TYPE_MODULATED = 1047,
  DELAY_TYPE_PONG = 1048,
  DELAY_TYPE_TAPE = 1049,
  DELAY_TYPE_ECHOPLEX = 1050,
  DELAY_TYPE_DM = 1051,

  DELAY_RP500_TYPE_DIGITAL = 1052,
  DELAY_RP500_TYPE_ANALOG = 1053,
  DELAY_RP500_TYPE_DM = 1058,
  DELAY_RP500_TYPE_ECHOPLEX = 1057,
  DELAY_RP500_TYPE_MODULATED = 1054,
  DELAY_RP500_TYPE_PONG = 1055,
  DELAY_RP500_TYPE_REVERSE = 1064,
  DELAY_RP500_TYPE_TAPE = 1056,

  DELAY_RP1000_TYPE_LO_FI = 1065,
  DELAY_RP1000_TYPE_2_TAP = 1066,

  DELAY_GNX3K_TYPE_MONO = 1027,
  DELAY_GNX3K_TYPE_PINGPONG = 1028,
  DELAY_GNX3K_TYPE_ANALOG = 1029,
  DELAY_GNX3K_TYPE_ANAPONG = 1030,
  DELAY_GNX3K_TYPE_SPREAD = 1031,
};

#define DELAY_TYPE 1856
#define DELAY_ON_OFF 1857
#define DELAY_POSITION 15

#define DELAY_TIME 1888

#define DELAY_MULTIPLIER 1904
#define DELAY_3_QUARTR 2180
#define DELAY_EIGHT 2179
#define DELAY_DOTEIGHT 2178
#define DELAY_QUARTER 2177
#define DELAY_HALF 2176

#define DELAY_TAPE_WOW 1891
#define DELAY_TAPE_FLUTTER 1892

#define DELAY_LEVEL 1860
#define DELAY_REPEATS 1863
#define DELAY_TAP_TIME 1868
#define DELAY_DUCK_THRESH 1889
#define DELAY_DUCK_LEVEL 1890
#define DELAY_REPEAT_RATE 1898
#define DELAY_REPEAT_RATE_DM 1894
#define DELAY_ECHO 1895
#define DELAY_INTENSITY 1896
#define DELAY_ECHOPLEX_TIME 1897
#define DELAY_TIME_0_760 1899
#define DELAY_VOLUME 1893
#define DELAY_REPEATS_0_99 1874
#define DELAY_DEPTH 1873
#define DELAY_TAP_TIME_0_4990 1900
#define DELAY_MIX 1902
#define DELAY_TIME_0_4650 1901
#define DELAY_TAP_RATIO 1905

#define GNX3K_DELAY_TIME 1862
#define GNX3K_DELAY_FEEDBACK 1863
#define GNX3K_DELAY_DUCK_THRESH 1864
#define GNX3K_DELAY_DUCK_ATTEN 1865
#define GNX3K_DELAY_BALANCE 1866
#define GNX3K_DELAY_SPREAD 1867

enum {
  GNX3K_REVERB_TYPE_STUDIO = 1107,
  GNX3K_REVERB_TYPE_ROOM = 1108,
  GNX3K_REVERB_TYPE_CLUB = 1109,
  GNX3K_REVERB_TYPE_PLATE = 1110,
  GNX3K_REVERB_TYPE_HALL = 1111,
  GNX3K_REVERB_TYPE_AMPHITHEATER = 1112,
  GNX3K_REVERB_TYPE_CHURCH = 1113,
  GNX3K_REVERB_TYPE_GARAGE = 1114,
  GNX3K_REVERB_TYPE_ARENA = 1115,
  GNX3K_REVERB_TYPE_SPRING = 1116,

  REVERB_TYPE_TWIN = 1146,
  REVERB_TYPE_LEX_AMBIENCE = 1150,
  REVERB_TYPE_LEX_STUDIO = 1149,
  REVERB_TYPE_LEX_ROOM = 1148,
  REVERB_TYPE_LEX_HALL = 1147,
  REVERB_TYPE_EMT240_PLATE = 1151
};

#define REVERB_TYPE 1920
#define REVERB_ON_OFF 1921
#define REVERB_POSITION 16

#define REVERB_PREDELAY 1922
#define REVERB_DAMPING 1924
#define REVERB_DECAY 1927
#define REVERB_BALANCE 1928
#define REVERB_LIVELINESS 1933
#define REVERB_LEVEL 1925

#define EXP_TYPE 8194
#define EXP_ASSIGN1 8194
#define EXP_POSITION 19

#define EXP_VOLUME_PRE_FX 854594
#define EXP_VOLUME_POST_FX 1116738 

#define EXP_MIN 8195
#define EXP_MAX 8196

#define LFO_TYPE 8258
#define LFO_MIN 8259
#define LFO_MAX 8260
#define LFO_SPEED 8262
#define LFO_WAVEFORM 8263

#define LFO_WAVEFORM_TRI 0
#define LFO_WAVEFORM_SINE 1
#define LFO_WAVEFORM_SQUARE 2 

#define LFO1_POSITION 22
#define LFO2_POSITION 23

// The LFO and VSWITCH defines are temporary.
#define LFO_ASSIGN_NONE 0
#define LFO_ASSIGN_PICKUP_ON 131137
#define LFO_ASSIGN_COMP_ON 262337
#define LFO_ASSIGN_SUSTAN 262352 

#define VSWITCH_ASSIGN 8384
#define VSWITCH_MIN 8385
#define VSWITCH_MAX 8386
#define VSWITCH_TYPE 8393
#define VSWITCH_ENABLE 8449
#define VSWITCH_ASSIGN_POSITION 21

#define VSWITCH_TYPE_TOGGLE 0
#define VSWITCH_PEDAL_ASSIGN_WAH 196740
#define VSWITCH_ASSIGN_WAH_ENABLE 196737

#define LIBRARY_TONE 8704
#define LIBRARY_EFFECTS 8705
#define EFFECTS_LEVEL 8706

#define LIBRARY_POSITION 25
#define LIB_POSITION 26

#define TONE_LIB_TYPE 8704
#define FX_LIB_TYPE 8705
#define FX_LIB_LEVEL 8706      // This influences pitch shift mix, delay level,
                               // and reverb level, in proportion, as
                               // specified by FX_LIB_LEVEL_MAX1,2,3.
                               // 
#define FX_LIB_LEVEL_MAX1 8708
#define FX_LIB_LEVEL_MAX2 8710
#define FX_LIB_LEVEL_MAX3 8712

enum {
  TONE_LIB_OVERDRIVE = 1793,
  TONE_LIB_ROCK1 = 1794,
  TONE_LIB_ROCK2 = 1795,
  TONE_LIB_BLUES1 = 1796,
  TONE_LIB_BLUES2 = 1797,
  TONE_LIB_METAL1 = 1798,
  TONE_LIB_METAL2 = 1799,
  TONE_LIB_COUNTRY1 = 1800,
  TONE_LIB_COUNTRY2 = 1801,
  TONE_LIB_WARM_DRIVE = 1802,
  TONE_LIB_CRUNCH = 1803,
  TONE_LIB_TEXAS_TONE = 1804,
  TONE_LIB_ROCKABILLY = 1805,
  TONE_LIB_SOLO1 = 1806,
  TONE_LIB_SOLO2 = 1807,
  TONE_LIB_ROCKWAH = 1808,
  TONE_LIB_CHUNKY = 1809,
  TONE_LIB_SMOOTH = 1810,
  TONE_LIB_HEAVY = 1811,
  TONE_LIB_CLEAN1 = 1812,
  TONE_LIB_CLEAN2 = 1813,
  TONE_LIB_BRITISH1 = 1814,
  TONE_LIB_BRITISH2 = 1815,
  TONE_LIB_AMERICAN1 = 1816,
  TONE_LIB_AMERICAN2 = 1817,
  TONE_LIB_TUBE_DRIVE = 1818,
  TONE_LIB_DISTORTION = 1819,
  TONE_LIB_SCOOPED = 1820,
  TONE_LIB_PUNCHY = 1821,
  TONE_LIB_BRIGHT_CLEAN = 1822,

  /* setting LIBRARY_TONE to this option seems to crash device */
  TONE_LIB_CUSTOM = 1792
};

enum {
  EFFECTS_LIB_CHORUS = 1857,
  EFFECTS_LIB_PHASER = 1858,
  EFFECTS_LIB_FLANGER = 1859,
  EFFECTS_LIB_PITCH = 1860,
  EFFECTS_LIB_TREMOLO = 1861,
  EFFECTS_LIB_ROTARY = 1862,
  EFFECTS_LIB_ENVELOPE = 1863,
  EFFECTS_LIB_DIGITAL = 1864,
  EFFECTS_LIB_ANALOG = 1865,
  EFFECTS_LIB_PONG = 1866,
  EFFECTS_LIB_MOD = 1867,
  EFFECTS_LIB_TAPE = 1868,
  EFFECTS_LIB_HALL = 1869,
  EFFECTS_LIB_PLATE = 1870,
  EFFECTS_LIB_SPRING = 1871,
  EFFECTS_LIB_CHORUS_DIGITAL = 1872,
  EFFECTS_LIB_CHORUS_DELAY_REVERB = 1873,
  EFFECTS_LIB_FLANGER_ANALOG = 1874,
  EFFECTS_LIB_PHASER_TAPE = 1875,
  EFFECTS_LIB_PHASER_MOD = 1876,
  EFFECTS_LIB_PHASER_ROOM = 1877,
  EFFECTS_LIB_DIGITAL_HALL = 1878,
  EFFECTS_LIB_ANALOG_SPRING = 1879,
  EFFECTS_LIB_CHORUS_HALL = 1880,
  EFFECTS_LIB_PONG_HALL = 1881,
  EFFECTS_LIB_TAPE_SPRING = 1882,
  EFFECTS_LIB_TREMOLO_TAPE = 1883,
  EFFECTS_LIB_PITCH_DIGITAL = 1884,
  EFFECTS_LIB_MOD_PLATE = 1885,
  EFFECTS_LIB_ROTARY_TAPE = 1886,

  /* setting EFFECTS_LIBRARY to this option seems to crash device */
  EFFECTS_LIB_CUSTOM = 1856
};

#define GLOBAL_POSITION 0

#define TUNING_REFERENCE 12288

#define USB_AUDIO_PLAYBACK_MIX 12297
#define USB_AUDIO_LEVEL 12307

#define GUI_MODE_ON_OFF 12298

#define EXP_PEDAL_LEVEL 12300
#define STOMP_MODE 12370

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

typedef enum {
    PRESETS_SYSTEM = 0,
    PRESETS_USER = 1,
    PRESETS_ARTIST = 2,

    /* Version 1 and later */
    PRESETS_MEDIA_CARD = 3,
    PRESETS_EDIT_BUFFER = 4, /* Current preset edit buffer, index must be 0 */
    PRESETS_FACTORY2 = 5,

    /* Version 2 and later */
    PRESETS_EXTERNAL = 6
} PresetBank;

typedef enum {
    /* Version 0 only */
    NOTIFY_PRESET_LOADED = 0,
    NOTIFY_PRESET_STORED = 1,

    NOTIFY_MODIFIER_GROUP_CHANGED = 2,

    /* Version 1 */
    NOTIFY_PRESET_MOVED = 3,
    NOTIFY_OBJECT_MOVED = 4,
    NOTIFY_OBJECT_RENAMED = 5,
    NOTIFY_MEDIA_CARD_PRESENT_CHANGED = 6,
    NOTIFY_ALL_GLOBALS_CHANGED = 7,
    NOTIFY_PRESET_INDEX_TABLE_CHANGED = 8,
    NOTIFY_PRESET_RENAMED = 9
} NotifyCode;

typedef enum {
    REQUEST_WHO_AM_I = 0x01,
    RECEIVE_WHO_AM_I = 0x02,

    REQUEST_DEVICE_CONFIGURATION = 0x08,
    RECEIVE_DEVICE_CONFIGURATION = 0x09,

    REQUEST_GLOBAL_PARAMETERS = 0x10,
    RECEIVE_GLOBAL_PARAMETERS = 0x11,

    REQUEST_BULK_DUMP = 0x18,
    RECEIVE_BULK_DUMP_START = 0x19,
    RECEIVE_BULK_DUMP_END = 0x1B,

    REQUEST_PRESET_NAMES = 0x21,
    RECEIVE_PRESET_NAMES = 0x22,

    REQUEST_PRESET_NAME = 0x28,
    RECEIVE_PRESET_NAME = 0x29,

    REQUEST_PRESET = 0x2A,
    RECEIVE_PRESET_START = 0x2B,
    RECEIVE_PRESET_END = 0x2C,
    RECEIVE_PRESET_PARAMETERS = 0x2D,

    LOAD_EDIT_BUFFER_PRESET = 0x38, /* version 0 only
                                       use move preset in later versions */

    MOVE_PRESET = 0x39,

    REQUEST_MODIFIER_LINKABLE_LIST = 0x3A,
    RECEIVE_MODIFIER_LINKABLE_LIST = 0x3B,

    REQUEST_PARAMETER_VALUE = 0x40,
    RECEIVE_PARAMETER_VALUE = 0x41,

    /* version 1 and later */
    REQUEST_OBJECT_NAMES = 0x50,
    RECEIVE_OBJECT_NAMES = 0x51,
    REQUEST_OBJECT_NAME = 0x52,
    RECEIVE_OBJECT_NAME = 0x53,
    REQUEST_OBJECT = 0x54,
    RECEIVE_OBJECT = 0x55,
    MOVE_OBJECT = 0x56,
    DELETE_OBJECT = 0x57,
    REQUEST_TABLE = 0x5A,
    RECEIVE_TABLE = 0x5B,

    RECEIVE_DEVICE_NOTIFICATION = 0x70,

    ACK = 0x7E,
    NACK = 0x7F
} MessageID;

typedef enum {
    SECTION_GENETX_AMP = 0,
    SECTION_GENETX_CABINET = 1,
    SECTION_DRUM_PATTERN = 2,
    SECTION_DRUM_KIT = 3,
    SECTION_DRUM_SAMPLES = 4,
    SECTION_SONG = 5,
    SECTION_FOOTSWITCH = 6,
    SECTION_GENETX2_AMP = 7,
    SECTION_GENETX2_CABINET = 8,
    SECTION_DEVICE_GUID = 9,
    SECTION_DEVICE_NAME = 10,
} SectionID;

typedef struct {
    int id;
    int position;
    int value;
} SettingParam;

enum {
    GENETX_VERSION_1,
    GENETX_VERSION_2
};

enum {
    GENETX_TYPE_NOT_SET = -1,
    GENETX_TYPE_AMP,
    GENETX_TYPE_CABINET
};

enum {
    GENETX_CHANNEL1 = 0,
    GENETX_CHANNEL2 = 1,
    GENETX_CHANNEL1_CUSTOM = 2,
    GENETX_CHANNEL2_CUSTOM = 3,
    GENETX_CHANNEL_CURRENT = 4
} ChannelBankIndex;

typedef struct {
    int version;
    int type;
    int channel;
    gchar *name;
    GString *data;
} SettingGenetx;

void send_message(gint procedure, gchar *data, gint len);
MessageID get_message_id(GString *msg);
void append_value(GString *msg, guint value);
GString *get_message_by_id(MessageID id);
SettingParam *setting_param_new();
SettingParam *setting_param_new_from_data(gchar *str, gint *len);
SettingGenetx *setting_genetx_new();
void setting_genetx_free(SettingGenetx *genetx);
void setting_param_free(SettingParam *param);
SectionID get_genetx_section_id(gint version, gint type);
void set_option(guint id, guint position, guint value);
void get_option(guint id, guint position);
void send_object(SectionID section, guint bank, guint index,
                 gchar *name, GString *data);
void send_preset_parameters(GList *params);
void switch_preset(guint bank, guint x);
void store_preset_name(int x, const gchar *name);
void set_preset_level(int level);
GStrv query_preset_names(gchar bank);
void message_list_free(GList *list);
GList *get_current_preset();

#endif /* GDIGI_H */
