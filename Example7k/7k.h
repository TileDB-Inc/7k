// Teledyne Marine
// 7k Data Format Definitions
// Version 3.12

// Use and Disclosure of Data
//
// EU Uncontrolled Technology: Information contained herein is uncontrolled
// under the E.U. Regulation (EC) No 428/2009.
// However, export, reexport or diversion contrary to law is prohibited.


#ifndef DEFINITIONS7K_H
#define DEFINITIONS7K_H

#pragma once

typedef char c8;
typedef signed char i8;
typedef short i16;
typedef long long i64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

#ifndef __LP64__
typedef long i32;
typedef unsigned long u32;
#else
typedef int i32;
typedef unsigned int u32;
#endif

#define PROTOCOL_VERSION 5  // DFD 0.54
#define RECORDS_VERSION  1  // DFD 0.54

// Control Flags (R7000 and R7503)
#define CONTROL_AUTO_RANGE_BITS                         0x0000000F  // bit 0-3
#define CONTROL_BOTTOM_DETECT_FILTER_METHOD_BITS        0x000000F0  // bit 4-7
#define CONTROL_BOTTOM_DETECT_RANGE_FILTER_BIT          0x00000100  // bit 8
#define CONTROL_BOTTOM_DETECT_DEPTH_FILTER_BIT          0x00000200  // bit 9
#define CONTROL_RECEIVER_GAIN_BITS                      0x00001C00  // bit 10-12
#define CONTROL_RECEIVER_GAIN_AUTO_BIT                  0x00000400  // bit 10
#define CONTROL_RECEIVER_GAIN_FIXED_BIT                 0x00000800  // bit 11
#define CONTROL_RECEIVER_GAIN_RESERVED_BIT              0x00001000  // bit 12
#define CONTROL_DEBUG_REPEATED_PING                     0x00002000  // bit 13
#define CONTROL_TRIGGER_RX_DURATION                     0x00004000  // bit 14
#define CONTROL_SYSTEM_ACTIVE                           0x00008000  // bit 15
#define CONTROL_ADAPTIVE_FILTER_ACTIVE                  0x00080000  // bit 19

#define CONTROL_BOTTOM_DETECT_PIPE_FILTER_BIT           0x00100000  // bit 20
#define CONTROL_BOTTOM_DETECT_AG_DEPTH_FILTER_FIXED_BIT 0x00200000  // bit 21
#define CONTROL_BOTTOM_DETECT_AG_ENABLE_BIT             0x00400000  // bit 22
#define CONTROL_BOTTOM_DETECT_AG_DEPTH_FILTER_BIT       0x00800000  // bit 23

#define CONTROL_TRIGGER_OUT                             0x01000000  // bit 24
#define CONTROL_TRIGGER_IN_EDGE                         0x02000000  // bit 25
#define CONTROL_PPS_EDGE                                0x04000000  // bit 26

#define CONTROL_TIME_STATE_BITS                         0x18000000  // bit 27-28
#define CONTROL_TIME_STATE_NA                           0x00000000  // enum 0
#define CONTROL_TIME_STATE_ERROR                        0x08000000  // enum 1
#define CONTROL_TIME_STATE_WARNING                      0x10000000  // enum 2
#define CONTROL_TIME_STATE_OK                           0x18000000  // enum 3

#define CONTROL_BOTTOM_DETECT_DEPTH_FILTER_FOLLOW_BIT   0x20000000  // bit 29
#define CONTROL_CSS_REDUCE_COVERAGE_BIT                 0x40000000  // bit 30
#define CONTROL_SIMULATOR                               0x80000000  // bit 31

#define CONTROL_BOTTOM_DETECTION_BITS              (CONTROL_BOTTOM_DETECT_FILTER_METHOD_BITS | \
                                                    CONTROL_BOTTOM_DETECT_RANGE_FILTER_BIT | \
                                                    CONTROL_BOTTOM_DETECT_DEPTH_FILTER_BIT | \
                                                    CONTROL_BOTTOM_DETECT_DEPTH_FILTER_FOLLOW_BIT | \
                                                    CONTROL_BOTTOM_DETECT_PIPE_FILTER_BIT | \
                                                    CONTROL_BOTTOM_DETECT_AG_DEPTH_FILTER_FIXED_BIT | \
                                                    CONTROL_BOTTOM_DETECT_AG_ENABLE_BIT | \
                                                    CONTROL_BOTTOM_DETECT_AG_DEPTH_FILTER_BIT)

// Receive flags (for receive_flags field in R7000 and R7503)
#define RECEIVE_MOTION_STABILIZATION_BITS          0x0000000F  // bit 0-3
#define RECEIVE_MOTION_ROLL_BIT                    0x00000001  // bit 0
#define RECEIVE_MOTION_HEAVE_BIT                   0x00000004  // bit 2
#define RECEIVE_DYNAMIC_FOCUS_BITS                 0x000000F0  // bit 4-7
#define RECEIVE_DOPPLER_COMP_BITS                  0x00000F00  // bit 8-11
#define RECEIVE_MATCH_FILTERING_BITS               0x0000F000  // bit 12-15
#define RECEIVE_TVG_METHOD_BITS                    0x000F0000  // bit 16-19
#define RECEIVE_MULTI_PING_BITS                    0x00F00000  // bit 20-23
#define RECEIVE_UNUSED_1                           0xFF000000  // bit 24-31

// Port flags for messages R7500sub10020, R7500sub10024, R10060, R10063
#define PORT_FLAG_ENABLED                          0x1  // bit 0
#define PORT_FLAG_CONFIGURED                       0x2  // bit 1

// Transmit flags (for transmit_flags field in R7000 and R7503)
#define TRANSMIT_MOTION_PITCH_BITS                 0x0000000F  // bit 0-3
#define TRANSMIT_MOTION_YAW_BITS                   0x000000F0  // bit 4-7
#define TRANSMIT_ERAS_BIT                          0x00000100  // bit 8

enum PING_STATE
{
	PING_STATE_OFF      = 0,
	PING_STATE_ON       = 1,
	PING_STATE_EXTERNAL = 2,
};

// Motion orientation (for orientation field in R7500sub1037)
#define MOTION_PORT_UP   0
#define MOTION_PORT_DOWN 1

enum DUTY_CYCLE_LIMIT_TYPE
{
	DCLT_PING_RATE,
	DCLT_POWER,
	DCLT_LAST,
};

enum SYSMODE
{
	SYSMODE_MANUAL,
	SYSMODE_AUTO_PILOT,
	SYSMODE_CALIBRATE_IQ,
	SYSMODE_PLAYBACK,
};

// Transmit Pulse Envelope
enum TTransmitEnvelopeFunc
{
	EnvelopeRect        = 0,
	EnvelopeTukey       = 1,
	EnvelopeHamming     = 2,
	EnvelopeHan         = 3,
	EnvelopeRectangular = 4,
};

// Match Filter Replica & Vernier
enum TWindowFunc
{
	WindowRect      = 0,
	WindowKaiser    = 1,
	WindowHamming   = 2,
	WindowBlackmann = 3,
	WindowTri       = 4,
	WindowX         = 5,
	WindowNONE      = 99,
};
#define  N_WINDOW_TYPES 7

// Gain mode for control_flags bits 10-12 in R7000 and R7503
enum GAINMODE
{
	GAINMODE_TVG   = 0,
	GAINMODE_AUTO  = 1,
	GAINMODE_FIXED = 2,
	GAINMODE_LAST  = 3,
};

enum BEAMSPACINGTYPE
{
	BS_DEFAULT,
	BS_EQUIANGLE,
	BS_EQUIDISTANT,
	BS_FLEX,
	BS_INTERMEDIATE,
	BS_EQUIANGLE_FLEX,
};

enum DualHeadMode
{
	DH_NORMAL = 0,
	DH_MASTER,
	DH_SLAVE,
};

enum VERNIER_MODE
{
	VM_UNKNOWN      = -1,
	VM_VERNIER      = 0,
	VM_SINGLE_ARRAY = 1,
	VM_TRIPLE_ARRAY = 3,
};

enum IQRATE
{
	IQR_SR17K   = 0,
	IQR_SR34K   = 1,
	IQR_SR50K   = 2,
	IQR_SR60K   = 3,
	IQR_SR80K   = 4,
	IQR_SR100K  = 5,
	IQR_NUM     = 6,
};

enum SONAR_TYPE
{
	SONARTYPE_BATHY = 0,
	SONARTYPE_FORWARD_LOOKING,
	SONARTYPE_SBES,
};

enum SB_TRACKER_ID
{
	SB_TRACKER_ID_UNUSED        = 0,
	SB_TRACKER_ID_RANGE         = 1,
	SB_TRACKER_ID_GAIN          = 2,
	SB_TRACKER_ID_SPREADING     = 3,
	SB_TRACKER_ID_ABSORPTION    = 4,
	SB_TRACKER_ID_PULSE_LENGTH  = 5,
	SB_TRACKER_ID_POWER         = 6,
	SB_TRACKER_ID_PULSE_TYPE    = 7,
	SB_TRACKER_ID_MAX_PING_RATE = 8,
};

enum SB_TRACKER_MODE
{
	SB_TRACKER_AUTO   = 0,
	SB_FIXED          = 1,
	SB_TRACKER_MANUAL = 1000,
	SB_TRACKER_TWEAK  = 1001,
};

enum PULSE_TYPE
{
	PULSE_TYPE_CW = 0,
	PULSE_TYPE_FM = 1,
};

#pragma pack(push, 1)

// Time
struct TIME_7K
{
	u16 year;
	u16 day;
	f32 seconds;
	u8 hours;
	u8 minutes;
};

#define RF_FLAG_CHECKSUM   0x0001  // bit 0
#define RF_FLAG_RDR        0x8000  // bit 15

// Data Record Frame - DRF
struct RECORD_FRAME
{
	u16 version;
	u16 offset;
	u32 sync_pattern;
	u32 size;
	u32 offset_optional;
	u32 identifier_optional;
	TIME_7K time_stamp;
	u16 records_version;
	u32 record_type;
	u32 device_identifier;
	u16 reserved1;
	u16 system_enumerator;
	u32 record_count;
	u16 flags;
	u16 reserved2;
	u32 reserved3;
	u32 total_records;
	u32 fragment_number;
};

#define SYNC_PATTERN 0x0000FFFF
#define SYNC_PATTERN_OFFSET offsetof(RECORD_FRAME, sync_pattern)
#define CHECKSUM_SIZE sizeof(u32)

// Network Frame - NF
struct NETWORK_FRAME
{
	u16 version;
	u16 offset;
	u32 total_packets;
	u16 total_records;
	u16 transmission_identifier;
	u32 packet_size;
	u32 total_size;
	u32 sequence_number;
	u32 destination_device_identifier;
	u16 destination_system_enumerator;
	u16 source_system_enumerator;
	u32 source_device_identifier;
};

// Reference Point
struct R1000
{
	f32 offset_x;
	f32 offset_y;
	f32 offset_z;
	f32 water_level;
};

// Sensor Offset Position
struct R1001
{
	f32 offset_x;
	f32 offset_y;
	f32 offset_z;
	f32 roll;
	f32 pitch;
	f32 yaw;
};

// Sensor Offset Position Calibrated
struct R1002
{
	f32 offset_x;
	f32 offset_y;
	f32 offset_z;
	f32 roll;
	f32 pitch;
	f32 yaw;
};

// Position
struct R1003
{
	u32 datum_id;
	f32 latency;
	f64 latitude_northing;
	f64 longitude_easting;
	f64 height;
	u8 position_type_flag;
	u8 utm_zone;
	u8 quality_flag;
	u8 position_method;
	u8 number_of_satellites;
};

// Custom Attitude Information
struct R1004
{
	u8 field_mask;
	u8 reserved;
	u16 samples;
	f32 frequency;
};

// Tide
struct R1005
{
	f32 tide;
	u16 source;
	u8 flags;
	u16 gauge_id;
	u32 datum_id;
	f32 latency;
	f64 latitude_northing;
	f64 longitude_easting;
	f64 height;
	u8 position_type;
	u8 utm_zone;
};

// Altitude
struct R1006
{
	f32 distance;
};

// Motion Over Ground
struct R1007
{
	u8 field_mask;
	u8 reserved;
	u16 number_fields;
	f32 frequency;
};

// Depth
struct R1008
{
	u8 depth_descriptor;
	u8 correction_flag;
	u16 reserved;
	f32 depth;
};

// Sound Velocity Profile
struct R1009
{
	u8 position_flag;
	u8 reserved1;
	u16 reserved2;
	f64 latitude;
	f64 longitude;
	u32 samples;
};

struct R1009SVPDATA
{
	f32 depth;
	f32 sound_velocity;
};

// CTD
struct R1010
{
	f32 frequency;
	u8 sound_velocity_source_flag;
	u8 sound_velocity_algorithm;
	u8 conductivity_flag;
	u8 pressure_flag;
	u8 position_flag;
	u8 sample_content_validity;
	u16 reserved;
	f64 latitude;
	f64 longitude;
	f32 sample_rate;
	u32 samples;
};

struct R1010CTDDATA
{
	f32 conductivity_salinity;
	f32 water_temp;
	f32 pressure_depth;
	f32 sound_velocity;
	f32 absorption;
};

// Geodesy
struct R1011
{
	c8 spheroid_name[32];
	f64 semi_major_axis;
	f64 inverse_flattening;
	u8 reserved1[16];
	c8 datum_name[32];
	u32 data_calculation_method;
	u8 parameter_transformation;
	f64 shift_x;
	f64 shift_y;
	f64 shift_z;
	f64 rotation_x;
	f64 rotation_y;
	f64 rotation_z;
	f64 scale;
	u8 reserved2[35];
	c8 grid_name[32];
	u8 grid_distance_units;
	u8 grid_angular_units;
	f64 latitude_of_origin;
	f64 central_meridian;
	f64 false_easting;
	f64 false_northing;
	f64 central_scale_factor;
	i32 custom_id;
	u8 reserved3[50];
};

// Roll Pitch Heave
struct R1012
{
	f32 roll;
	f32 pitch;
	f32 heave;
};

// Heading
struct R1013
{
	f32 heading;
};

// Survey Line
struct R1014
{
	u16 way_point;
	u16 position_type;
	f32 radius;
	c8 line_name[64];
};

// Navigation
struct R1015
{
	u8 vertical_reference;
	f64 latitude;
	f64 longitude;
	f32 horz_accuracy;
	f32 vessel_height;
	f32 height_accuracy;
	f32 speed_over_ground;
	f32 course_over_ground;
	f32 heading;
};

// Attitude
struct R1016
{
	u8 number_sets;
};

struct R1016DATA
{
	u16 time_difference;
	f32 roll;
	f32 pitch;
	f32 heave;
	f32 heading;
};

// Pan Tilt
struct R1017
{
	f32 pan;
	f32 tilt;
};

// X Y Z offset struct
struct OffsetTriplet
{
	f32 x, y, z;
};

struct MBESXYZ
{
	f32 length;
	f32 width;
	f32 height;
	f32 radius;
	OffsetTriplet offset;
	f32 offset_roll;
	f32 offset_pitch;
	f32 offset_yaw;
};

// Sonar Installation Identifiers
struct R1020
{
	u32 sonar_id;
	u32 tx_id;
	u32 rx_id;
	u32 configuration;
	u32 config_params;
	MBESXYZ tx;
	MBESXYZ rx;
	f32 frequency;
	OffsetTriplet vessel_offset;
	u32 cable_length;
	u32 reserved[11];
};

struct R2004Point
{
	f32 x;
	f32 y;
	f32 z;
	f32 angle;
	f32 sample;
};

// Sonar Pipe Environment
struct R2004
{
	u32 pipe_number;
	TIME_7K ping_time;
	u32 ping_number;
	u32 multiping_sequence;
	f32 pipe_diameter;
	f32 ping_sound_velocity;
	f32 ping_sample_rate;
	u8 finished;
	u32 num_points;
	u32 point_size;
	u32 data_quality;
	u32 reserved[9];
};

// Target / Contact Output
struct R3001
{
	u32 target_id;
	u32 ping_number;
	TIME_7K operation_time;
	c8 operator_name[128];
	u32 contact_state;
	f32 range;
	f32 bearing;
	u32 information_flags;
	f64 latitude;
	f64 longitude;
	f32 azimuth;
	f32 contact_length;
	f32 contact_width;
	c8 classification[128];
	c8 description[128];
};

// Range
struct R7500sub1003
{
	f32 range;
};

// Max Ping Rate
struct R7500sub1004
{
	f32 max_ping_rate;
};

// Transmit Power
struct R7500sub1005
{
	f32 power;
};

// Pulse Length
struct R7500sub1006
{
	f32 pulse_length;
};

// Pulse Type
struct R7500sub1007
{
	u32 pulse_type;  // see enum PULSE_TYPE
};

// Receiver Gain
struct R7500sub1008
{
	f32 gain;
};

// Bottom Detection Mask
struct R7500sub1009
{
	u32 flags;
};

#define RC1009_FLAGS_RANGE_FILTER_ENABLE_BIT       0x00000100  // bit 8
#define RC1009_FLAGS_DEPTH_FILTER_ENABLE_BIT       0x00000200  // bit 9
#define RC1009_FLAGS_ADAPTIVE_GATE_ENABLE_BIT      0x00000400  // bit 10
#define RC1009_FLAGS_AG_DEPTH_FILTER_ENABLE_BIT    0x00000800  // bit 11
#define RC1009_FLAGS_AG_DEPTH_FILTER_FIXED_BIT     0x00001000  // bit 12
#define RC1009_FLAGS_DEPTH_FILTER_FOLLOW_BIT       0x00002000  // bit 13

// Bottom Detection Filter Information
struct R7500sub1010
{
	f32 min_range;
	f32 max_range;
	f32 min_depth;
	f32 max_depth;
	f32 depth_gate_tilt;
};

// Projector Selection
struct R7500sub1011
{
	u32 projector;
};

// System Mode
struct R7500sub1014
{
	u16 center_mode;  // see enum SYSMODE
	u16 flags;
};

#define RC1014_AUTORANGE_LEGACY_AUTOPILOT_BIT       0x8000  // bit 15

// Bottom Detection Adaptive Gate Window and Filters
struct R7500sub1016
{
	i32 ag_window;
	f32 ag_min_depth;
	f32 ag_max_depth;
};

// Vernier Processing Parameters
struct R7500sub1019
{
	u16 field_flags;
	u32 mode;  // see enum VERNIER_MODE
	u8 decimation_factor;
	u32 first_sample;
	u32 smoothing_window_type;  // see enum TWindowFunc
	u16 smoothing_window_length;
	u8 reference_array;
	u32 reserved[4];
};

#define RC1019_FLAGS_MODE_BIT                      0x01  // bit 0
#define RC1019_FLAGS_DECIMATION_BIT                0x02  // bit 1
#define RC1019_FLAGS_FIRST_SAMPLE_BIT              0x04  // bit 2
#define RC1019_FLAGS_SMOOTH_WIN_TYPE_BIT           0x08  // bit 3
#define RC1019_FLAGS_SMOOTH_WIN_LEN_BIT            0x10  // bit 4
#define RC1019_FLAGS_REFERENCE_ARRAY_BIT           0x20  // bit 5

// Transmit Pulse Envelope Window Shading
struct R7500sub1020
{
	u32 envelope_type;  // see enum TTransmitEnvelopeFunc
	f32 shading_value;
	u32 reserved[4];
};

// Projector Beam Steering
struct R7500sub1021
{
	f32 projector_beam_steer_x;
	f32 projector_beam_steer_z;
};

// Projector Beam Widths
struct R7500sub1022
{
	f32 projector_beam_width_x;
	f32 projector_beam_width_z;
};

// Transmit Center Frequency
struct R7500sub1026
{
	f32 frequency;
};

// Transmit Frequencies for Chirps
struct R7500sub1027
{
	f32 start_frequency;
	f32 stop_frequency;
};

// Motion Compensation
struct R7500sub1033
{
	u8 roll;
	u8 pitch;
	u8 heave;
	u8 speed;
	u8 reserved[8];
};

// Match Filter Parameters
struct R7500sub1034
{
	u32 window_type;
	f32 shading_value;
	u32 reserved[4];
};

// Coverage Sector
struct R7500sub1035
{
	f32 coverage_angle;
	f32 steering_angle;
};

// Motion Sensor Configuration
struct R7500sub1037
{
	u8 format;
	u8 baud;
	u8 parity;
	u8 data;
	u8 stop;
	u8 orientation;
	u8 reserved1;
	f32 motion_latency;
	u8 reserved2[20];
};

// FlexMode Parameters
struct R7500sub1038
{
	f32 flex_sector_coverage;
	f32 flex_sector_steering;
	f32 was_flex_outside_spacing;
};

// Beam Mode Selection
struct R7500sub1039
{
	u16 beam_mode_selection;
};

// System Sample Rate
struct R7500sub1040
{
	u32 iq_rate;  // see enum IQRATE
};

// Custom Beams
struct R7500sub1043
{
	u16 custom_beams;
};

// Constant Spacing
struct R7500sub1044
{
	f32 constant_spacing;
	u32 flags;
};

#define RC1044_FLAGS_REDUCE_COVERAGE_BIT 0x00000001  // bit 0

// Multi-Detect Parameters
struct R7500sub1045
{
	u16 use_multi_detect;
	u16 object_size;
	u16 sensitivity;
	u16 max_detections;
	u16 reserved[2];
};

#define  MD_MAX_DETECTIONS_PER_BEAM    10

enum PowerSaveModeType
{
	PSM_MAX_POWER,
	PSM_NORMAL,
	PSM_RANGE_BLANK,
	PSM_SLEEP,
	PSM_HIBERNATE,
};

// Power Saving
struct R7500sub1046
{
	u8 mode;  // see enum PowerSaveModeType
	u8 flags;
	u16 percent;
};

// AUV Configuration Options
struct R7500sub1047
{
	u8 startup_norm;
	u8 restore_ping_rate;
	u8 restore_power;
	u8 sv_interlock;
	u8 ignore_pps_errors;
	u8 restore_recording;
	u8 restore_tracker;
	u8 reserved1;
	u32 reserved2[3];
};

// Duty-Cycle Limitation Control Method
struct R7500sub1048
{
	u16 method;  // see enum DUTY_CYCLE_LIMIT_TYPE
};

// Single Record Request
struct R7500sub1050
{
	u32 record_type;
};

// Record Subscription
struct R7500sub1051
{
	u32 record_count;
};

// Third Party Data Connection
struct R7500sub1053
{
	u32 address;
	u16 port;
	u16 connect_type;
	u32 num_records;
	u32 records[1];
};

// Data Feed, Range of Records
struct R7500sub1055
{
	u32 start_record;
	u32 end_record;
};

// Unsubscribe Records
struct R7500sub1056
{
	u32 record_count;
};

// External Trigger
struct R7500sub1114
{
};

// Trigger Out
struct R7500sub1115
{
	u32 flags;
	f64 length;
	f64 offset;
};

#define R7500_1115_FLAGS_ENABLE_BIT        0x00000001   // bit 0
#define R7500_1115_FLAGS_RX_DURATION_BIT   0x00000002   // bit 1

// PPS Edge Control
struct R7500sub1116
{
	u32 edges;
};

#define R7500_1118_FLAGS_AUTOMATIC_BIT     0x0000001  // bit 0
#define R7500_1118_FLAGS_MINIMUM_BIT       0x0000002  // bit 1
#define R7500_1118_FLAGS_MAXIMUM_BIT       0x0000004  // bit 2
#define R7500_1118_FLAGS_BOTH_MASK         0x0000006  // bit 1-2

#define SNIP_WIN_MIN 1
#define SNIP_WIN_MAX 300

// Snippet Control
struct R7500sub1118
{
	u32 flags;
	u32 min_window;
	u32 max_window;
};

// Ping Number of Times
struct R7500sub1121
{
	u32 number_of_times;
};

// Start Ping Sequence
struct R7500sub1122
{
	u32 sequence_identifier;
};

// Start Recording
struct R7500sub1200
{
	u32 reserved;
	c8 file_name[256];
};

// Set Recording Directory
struct R7500sub1207
{
	c8 path_name[256];
};

// Set Filtering
struct R7500sub1209
{
	u16 filter_type;
	u16 filter_method;
	u16 number_filters;
};

// Logging Settings
struct R7500sub1211
{
	u8 single_file;
	u8 history;
};

// Tracker Control
struct R7500sub1402
{
	u32 tracker_flags;
	f32 tracker_swath_width;
	f32 tracker_max_coverage_angle;
};

// Used for tracker_flags in R7500sub1402 and R7504
#define TRACKER_RANGE_ENABLED_BIT               0x00000001  // bit 0
#define TRACKER_POWER_GAIN_ENABLED_BIT          0x00000002  // bit 1
#define TRACKER_PULSE_LENGTH_ENABLED_BIT        0x00000004  // bit 2
#define TRACKER_COVERAGE_ANGLE_ENABLED_BIT      0x00000008  // bit 3
#define TRACKER_FIXED_SWATH_ENABLED_BIT         0x00000010  // bit 4
#define TRACKER_MAX_COVERAGE_ANGLE_ENABLED_BIT  0x00000020  // bit 5

// Full Rate Dual Head Control
struct R7500sub1502
{
	u32 full_rate_dual_head;
};

// 1600 series of commands used by MB2

// Custom Recording Control
struct R7500sub1600 
{
	c8 path_name[256];
	c8 prepend_name[256];
	c8 trailer_name[256];
	u8 prepend_header;
	u8 append_trailer;
	u32 record;
};

// Custom Playback Control
struct R7500sub1601
{
	c8 path_name[256];
	c8 file_name[256];
	i32 mode;
	u8 play;
	u8 keep_org_time_stamps;
};

// Custom Sensors
struct R7500sub1602
{
	u8 use_builtin_posmv;
	u8 use_attached_svp;
};

// Stacking
struct R7500sub1603
{
	u8 enable_stacking;
	u8 stacking_value;
};

// Serial Ports
struct R7500sub1604
{
	u8 port_zda_baud;
	u8 port_zda_parity;
	u8 port_zda_data;
	u8 port_zda_stop;
	u8 port_gga_baud;
	u8 port_gga_parity;
	u8 port_gga_data;
	u8 port_gga_stop;
	u8 port_svp_baud;
	u8 port_svp_parity;
	u8 port_svp_data;
	u8 port_svp_stop;
	u8 port_hpr_baud;
	u8 port_hpr_parity;
	u8 port_hpr_data;
	u8 port_hpr_stop;
	u8 port_hdt_baud;
	u8 port_hdt_parity;
	u8 port_hdt_data;
	u8 port_hdt_stop;
};

// RRIO Addresses
struct R7500sub1605
{
	c8 rrio_address1[256];
	c8 rrio_address2[256];
	c8 rrio_address3[256];
};

// Custom Recording Quick Info
struct R7500sub1606
{
	u16 disk_free_percent;
	u32 num_records;
	i64 size;
	u32 record;
	c8 file_name[256];
	u32 rdr_error;
	u32 reserved[30];
};

// Head Tilt Angle
struct R7500sub1607
{
	f32 head_tilt_y;
};

// Deck Mode
struct R7500sub1608
{
	u32 deck_mode;
};

// Power Mode
struct R7500sub1609
{
	u8 power_mode_flags;
	u8 power_mode_max;
};

// Power Built-In POSMV
struct R7500sub1610
{
};

// Compressed Water Column Data Setup
struct R7500sub7042
{
	u32 flags;
};

// Manual Sound Velocity
struct R7500sub7610
{
	u16 flags;
	f32 sound_velocity;
	u8 filter;
	u8 reserved[3];
};

#define R7500_7610_FLAGS_MANUAL_OVERRIDE_BIT        0x00000001  // bit 0
#define R7500_7610_FLAGS_IGNORE_SOUND_VELOCITY_BIT  0x00000002  // bit 1
#define R7500_7610_FLAGS_CHANGE_FILTER_BIT          0x00000004  // bit 2

enum SVFILTER
{
	SVFILTER_TRANSPARENT  = 1,
	SVFILTER_LIGHT        = 2,
	SVFILTER_NORMAL       = 3,
	SVFILTER_SVP70_WIZARD = 4,
};

// Manual Temperature Control
struct R7500sub7614
{
	u16 flags;
	f32 temperature_c;
	u16 reserved[2];
};

#define R7500_7614_FLAGS_MANUAL_OVERRIDE_BIT        0x00000001  // bit 0
#define R7500_7614_FLAGS_IGNORE_TEMPERATURE_BIT     0x00000002  // bit 1

// SB corrected transducer draft
struct R7500sub10001
{
	f32 corrected_transducer_draft;
};

// SB max ping rate
struct R7500sub10003
{
	f32 max_ping_rate;
};

// SB channel enable mode
struct R7500sub10004
{
	u32 channels;
	u32 ping_pong;
};

// SB transducer selection
struct R7500sub10005
{
	u32 transducer_index;
};

// SB operation modes
enum SBESSystemStates
{
	STANDBY = 10,
	HYDROGRAPHIC = 20,
};
enum SBESOperationModes
{
	STANDBY_CONFIGURATION = 10,
	TEST = 11,	
	BAR_CHECK = 12,
	HYDROGRAPHIC_AUTO = 20,
	HYDROGRAPHIC_SEMIAUTO = 21,
	HYDROGRAPHIC_MANUAL = 22,
};
struct R7500sub10007
{
	u32 system_state;
	u32 operation_mode;
};

// SB tracker tweak modes
struct R7500sub10008
{
	u32 tweak_mode_count;
};

struct R7500sub10008Data
{
	u32 tweak_id;  // see enum SB_TRACKER_ID
	u32 tweak_mode;  // see enum SB_TRACKER_MODE
};

// SB tracker tweak value
struct R7500sub10014
{
	u32 tweak_id;
	f32 tweak_value;
};

// Bottom Detection Bar-Check Gate
struct R7500sub10016
{
	f32 min_gate;
	f32 max_gate;
	u32 gate_mode;
};

// SB serial port configuration
struct R7500sub10020
{
	u32 port_index;
	u16 flags;
	u16 reserved1;
	u64 system_function;
	u32 phy_setting;
	u32 baud_rate;
	u32 data_bits;
	u32 stop_bits;
	u32 parity_index;
	u32 sentence_index_0;
	u32 reserved2[3];
	c8 label_on_box[32];
};

// SB serial/udp port list management
struct R7500sub10021
{
	u32 port_index;
	u32 port_command;
};

// SB TimeSync Source Enable
struct R7500sub10022
{
	u32 source_id;
	u32 source_command;
};

#define R7500SUB10022_SOURCE_ID_ZDA_PPS 1
#define R7500SUB10022_SOURCE_ID_NTP     2
#define R7500SUB10022_SOURCE_ID_UIPC    4

// SB Ethernet Time Source Configuration
struct R7500sub10023
{
	u32 source_id;
	c8 source_name[32];
	u32 source_ipv4;
};

#define R7500SUB10023_SOURCE_ID_NTP     2
#define R7500SUB10023_SOURCE_ID_UIPC    4

// SB multicast port configuration
struct R7500sub10024
{
	u32 multicast_index;
	u32 group_ip;
	u16 port;
	u16 flags;
	u16 sentence_index;
	u16 reserved0;
	u32 depthChan;
};


// SB annotation
struct R10025
{
	u32 client_number;
	u32 annotation_number;
	u32 ping_number;
	TIME_7K time_stamp;
	u16 reserved;
	f64 latitude;
	f64 longitude;
	f64 height;
	u32 flags;
	f32 depth;
	f32 heave;
	c8 text[80];
};

#define R10025_FLAGS_TEXT_VALID        0x0001
#define R10025_FLAGS_DEPTH_VALID       0x0002
#define R10025_FLAGS_LATTITUDE_VALID   0x0004
#define R10025_FLAGS_LONGITUDE_VALID   0x0008
#define R10025_FLAGS_HEIGHT_VALID      0x0010
#define R10025_FLAGS_HEAVE_VALID       0x0020
#define R10025_FLAGS_TIME_VALID        0x1000
#define R10025_FLAGS_PING_NUMBER_VALID 0x2000


// BlueView Pan/Tilt Configuration Container Format Version 1
struct R5835
{
	u16 version_number;
	u64 sonar_id;
	u16 head_id;
	u8 manufacturer[80];
	u8 model[80];
	f32 tilt_elbow_offset;
	u16 head_orientation;
	f32 pan_calibration_pos;
	f32 tilt_calibration_pos;
	f32 z_calibration_pos;
	u16 pan_raw_direction;
	u16 pan_axis_affected;
	u16 pan_axis_direction;
	u16 tilt_raw_direction;
	u16 tilt_axis_affected;
	u16 tilt_axis_direction;
	u8 scanning;
	f32 scan_pan_start_angle;
	f32 scan_pan_stop_angle;
	f32 scan_tilt_start_angle;
	f32 scan_tilt_stop_angle;
};

// BlueView Pan/Tilt Configuration Container Format Version 2
struct R5835v2
{
	u16 version_number;
	u64 sonar_id;
	u16 head_id;
	u8 manufacturer[80];
	u8 model[80];
	f32 tilt_elbow_offset;
	f32 pan_arm_offset;
	f32 tilt_axis_offset;
	f32 head_roll_orientation;
	f32 pan_calibration_pos;
	f32 tilt_calibration_pos;
	u8 scanning;
	f32 scan_pan_start_angle;
	f32 scan_pan_stop_angle;
	f32 scan_tilt_start_angle;
	f32 scan_tilt_stop_angle;
};

// BlueView Pan/Tilt Position Container Format
struct R5836
{
	u16 version_number;
	u64 sonar_id;
	u16 head_id;
	u32 ping_number;
	f32 pan_position;
	f32 tilt_position;
	f32 reserved;
};

// Sonar Settings
struct R7000
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	f32 frequency;
	f32 sample_rate;
	f32 receiver_bandwidth;
	f32 pulse_width;
	u32 pulse_type;  // see enum PULSE_TYPE
	u32 pulse_envelope_type;  // see enum TTransmitEnvelopeFunc
	f32 pulse_envelope_parameter;
	u16 pulse_mode;
	u16 pulse_reserved;
	f32 max_ping_rate;
	f32 ping_period;
	f32 range;
	f32 power;
	f32 gain;
	u32 control_flags;
	u32 projector_magic_number;
	f32 projector_beam_steer_x;
	f32 projector_beam_steer_z;
	f32 projector_beam_width_x;
	f32 projector_beam_width_z;
	f32 projector_beam_focal_point;
	u32 projector_beam_weighting_type;
	f32 projector_beam_weighting_parameter;
	u32 transmit_flags;
	u32 hydrophone_magic_number;
	u32 hydrophone_beam_weighting_type;
	f32 hydrophone_beam_weighting_parameter;
	u32 receive_flags;
	f32 receive_beam_width;
	f32 range_filter_min;
	f32 range_filter_max;
	f32 depth_filter_min;
	f32 depth_filter_max;
	f32 absorption;
	f32 sound_velocity;
	f32 spreading_loss;
	u16 reserved;
};

// Configuration
struct R7001
{
	u64 serial_number;
	u32 systems;
};

struct R7001MODULEINFO
{
	u32 unique_identifier;
	c8 string[60];
	u32 card_family_bits;
	u64 serial_number;
	u32 info_length;
};

// Match Filter
struct R7002
{
	u64 serial_number;
	u32 ping_number;
	u32 operation;
	f32 start_frequency;
	f32 stop_frequency;
	u32 replica_window_type;  // see enum TWindowFunc
	f32 replica_window_shading;
	f32 effective_pulsewidth;
	u32 reserved[13];
};

// Firmware and Hardware Configuration
struct R7003
{
	u32 devices;
	u32 info_length;
};

// Beam Geometry
struct R7004
{
	u64 serial_number;
	u32 beams;
};

// Bathymetric Data
struct R7006
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u32 beams;
	u8 layer_compensation_flag;
	u8 sound_velocity_flag;
	f32 sound_velocity;
};

#define QUALITY_PROCESS_BRIGHTNESS_BIT        0x01  // bit 0
#define QUALITY_PROCESS_COLINEARITY_BIT       0x02  // bit 1
#define QUALITY_PROCESS_MAGNITUDE_BIT         0x04  // bit 2
#define QUALITY_PROCESS_PHASE_BIT             0x08  // bit 3

// Side Scan Data
struct R7007
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	f32 beam_position;
	u32 control;
	u32 samples;
	u32 nadir_depth;
	u32 reserved[7];
	u16 beams_per_side;
	u16 beam;
	u8 bytes_per_sample;
	u8 data_type;
};

#define R7007_NADIR_DEPTH_USED 0x01

// Generic Water Column Data
struct R7008
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u16 beams;
	u16 reserved;
	u32 samples;
	u8 subset_flag;
	u8 rowcolumn_flag;
	u16 sample_header_identifier;
	u32 sample_type;
};

struct R7008Data
{
	u16 descriptor;
	u32 first_sample;
	u32 last_sample;
};

// TVG Values
struct R7010
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u32 samples;
	u32 reserved[8];
};

#define R7011_DB_VISUALIZATION    0x01
#define R7011_UN_STABILIZED_BEAMS 0x02

// Image Data
struct R7011
{
	u32 ping_number;
	u16 multiping_sequence;
	u32 width;
	u32 height;
	u16 color_depth;
	u16 rotation_flag;
	u16 compression_algorithm;
	u32 samples;
	u32 flags;
	f32 rx_delay;
	u32 reserved[6];
};

#define R7012_PITCH_STAB_APPLIED    0x1  // bit 0
#define R7012_ROLL_STAB_APPLIED     0x2  // bit 1
#define R7012_YAW_STAB_APPLIED      0x4  // bit 2
#define R7012_HEAVE_STAB_APPLIED    0x8  // bit 3

#define R7012_PHINS_STATUS_FLAGS    0x000F  // bits 0-3
#define R7012_PHINS_STATUS_SHIFT    0

// For R7026 & R7012
#define PHINS_REFERENCE_VALID       0
#define PHINS_REFERENCE_LOST        1

#define R7012_ROLL_STATUS_FLAGS     0x0070  // bits 4-7
#define R7012_ROLL_STATUS_SHIFT     4
#define R7012_NO_ROLL_ERROR         0x0
#define R7012_ROLL_ANGLE_WARNING    0x1
#define R7012_ROLL_ANGLE_ERROR      0x2
#define R7012_ROLL_RATE_ERROR       0x4
#define R7012_ROLL_MAX_ERROR        (R7012_ROLL_ANGLE_ERROR | R7012_ROLL_RATE_ERROR)
#define R7012_ROLL_MISSING          0x8

// Ping Motion Data
struct R7012
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u32 samples;
	u16 flags;
	u32 error_flags;
	f32 sampling_rate;
};

// Adaptive Gate
struct R7014
{
	u16 header_size;
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u32 number_of_gates;
	u16 gate_descriptor_size;
};

struct R7014GATEDATA
{
	f32 angle;
	f32 min_limit;
	f32 max_limit;
};

// Beamformed Data
struct R7018
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u16 beams;
	u32 samples;
	u32 reserved[8];
};

// Beamformed Sample Data
struct sampletype
{
	u16 mag;
	i16 phase;
};

// Vernier Processing Data (Raw)
struct R7019
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u8 reference_array;
	u8 pair1_array;
	u8 pair2_array;
	u8 decimation_factor;
	u16 beams;
	u32 samples;
	u32 decimated_samples;
	u32 first_sample;
	u32 reserved1[2];
	u16 smoothing_type;  // see enum TWindowFunc
	u16 smoothing_window;
	u32 reserved2[2];
	f32 mag_threshold;
	f32 min_qf;
	f32 max_qf;
	f32 min_angle;
	f32 max_angle;
	f32 elevation_coverage;
	u32 reserved3[4];
};

// BITE Sensor Data
struct SENSOR_BITE
{
	u16 sensor_field;
	c8 sensor_name[64];
	u8 sensor_type;
	f32 min;
	f32 max;
	f32 value;
};

// BITE Board Data
struct BOARD_BITE
{
	c8 source_name[64];
	u8 source_address;
	f32 was_frequency;
	u16 was_enumerator;
	TIME_7K downlink_time;
	TIME_7K uplink_time;
	TIME_7K bite_time;
	u8 board_status; 
	u16 bite_sensors;
	u64 bite_status[4];
};

#define BOARD_BITE_UPLINK_STATUS_BIT        0x01  // bit 0
#define BOARD_BITE_DOWNLINK_STATUS_BIT      0x02  // bit 1
#define BOARD_BITE_ERROR_STATUS_BIT         0x04  // bit 2

#define BOARD_BITE_SENSORS_STATUS_MASK      0x18  // bit 3-4
#define BOARD_BITE_SENSORS_STATUS_SHIFT     3

enum BiteStatus
{
	BOARD_BITE_SENSORS_STATUS_OK,
	BOARD_BITE_SENSORS_STATUS_WARNING,
	BOARD_BITE_SENSORS_STATUS_ERROR,
	BOARD_BITE_SENSORS_STATUS_FATAL,
};

// Built-In Test Environment Data
struct R7021
{
	u16 board_count;
};

// Sonar Source Version
struct R7022
{
	c8 version[32];
};

// 8k Wet End Version
struct R7023
{
	c8 version[32];
};

// Raw Detection Data
struct R7027
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u32 detections;
	u32 data_size;
	u8 algorithm;
	u32 flags;
	f32 sampling_rate;
	f32 tx_angle;
	f32 applied_roll;
	u32 reserved[15];
};

#define R7027_FLAGS_UNCERTAINTY_MASK          0x0F  // bit 0-3
#define R7027_FLAGS_MULTI_DETECTION_BIT       0x10  // bit 4
#define R7027_FLAGS_HAS_SNIPPETS_DETECT_BIT   0x40  // bit 6

// Uncertainty method in bits 0-3
enum UncertaintyMethod
{
	R7027_FLAGS_UNCERTAINTY_NONE    = 0,
	R7027_FLAGS_UNCERTAINTY_ROBHARE = 1,
	R7027_FLAGS_UNCERTAINTY_IFREMER = 2,
};

// Detection results section
struct R7027Data
{
	u16 beam_number;
	f32 detection;
	f32 rx_angle;
	u32 flags;
	u32 quality;
	f32 uncertainty;
	f32 signal_strength;
	f32 limit_min;
	f32 limit_max;
};

#define R7027DATA_FLAGS_MAGNITUDE_BIT         0x00000001  // bit 0
#define R7027DATA_FLAGS_PHASE_BIT             0x00000002  // bit 1
#define R7027DATA_FLAGS_QUALITY_TYPE_MASK     0x000001FC  // bit 2-8
#define R7027DATA_FLAGS_QUALITY_TYPE_SHIFT    2
#define R7027DATA_FLAGS_PRIORITY_MASK         0x00001E00  // bit 9-12
#define R7027DATA_FLAGS_PRIORITY_SHIFT        9
#define R7027DATA_FLAGS_SNIPPETS_DETECT_BIT   0x00004000  // bit 14

#define R7027DATA_QUALITY_BRIGHTNESS_BIT      0x00000001  // bit 0
#define R7027DATA_QUALITY_COLINEARITY_BIT     0x00000002  // bit 1

// Snippet Data
struct R7028
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u16 detections;
	u8 error_flags;
	u8 control_flags;
	u32 flags;
	u32 reserved[6];
};

// NOTE:  These are not the same bits as used in the RC1118 flags field
#define R7028_CONTROL_FLAGS_AUTO_WINDOW_BIT      0x01  // bit 0
#define R7028_CONTROL_FLAGS_QUALITY_FILTER_BIT   0x02  // bit 1
#define R7028_CONTROL_FLAGS_MIN_WINDOW_BIT       0x04  // bit 2
#define R7028_CONTROL_FLAGS_MAX_WINDOW_BIT       0x08  // bit 3

#define R7028_FLAGS_32BITS_SNIPPETS_BIT          0x01  // bit 0

// Vernier Processing Data (Filtered)
struct R7029
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u16 soundings;
	f32 min_angle;
	f32 max_angle;
	u16 repeat_size;
};

struct R7029Data
{
	f32 angle;
	u32 sample;
	f32 elevation;
	f32 reserved; 
};

enum DevIndex7031
{
	R7031_INDEX_OVERALL = 0,
	R7031_INDEX_RX,
	R7031_INDEX_TX,
	R7031_INDEX_SYSTEM,
};

// Built-In Test Environment Data (Summary)
struct R7031
{
	u16 total;
	u16 warning[4];
	u16 error[4];
	u16 fatal[4];
	u32 reserved[2];
};

// Compressed Beamformed Magnitude Data
struct R7041
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u16 beams;
	u16 flags;
	f32 samplerate;
	u32 reserved[4];
};

// Compressed Water Column Data
struct R7042
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u16 beams;
	u32 samples;
	u32 compressed_samples;
	u32 flags;
	u32 first_sample;
	f32 sample_rate;
	f32 compression_factor;
	u32 reserved[1];
};

// For R7042 and R7500sub7042
#define R7042_FLAGS_USE_BD_BIT                    0x0001  // bit 0
#define R7042_FLAGS_MAG_ONLY_BIT                  0x0002  // bit 1
#define R7042_FLAGS_COMPRESS_BIT                  0x0004  // bit 2
#define R7042_FLAGS_USE_ABSOLUTE_GATES_BIT        0x0008  // bit 3
#define R7042_FLAGS_DS_DIVISOR_MASK               0x00F0  // bits 4-7
#define R7042_FLAGS_DS_DIVISOR_SHIFT              4
#define R7042_FLAGS_DS_TYPE_MASK                  0x0F00  // bits 8-11
#define R7042_FLAGS_DS_TYPE_SHIFT                 8

#define R7500_7042_MASK                           0x0FFF  // bits 0-11

// Only for R7042
#define R7042_FLAGS_DATA_32BITS_BIT               0x1000  // bit 12
#define R7042_FLAGS_COMPRESS_FACTOR_AVAILABLE_BIT 0x2000  // bit 13
#define R7042_FLAGS_SEGMENT_AVAILABLE_BIT         0x4000  // bit 14
#define R7042_FLAGS_FIRST_SAMPLE_IS_RX_DELAY_BIT  0x8000  // bit 15

enum DownSamplingType
{
	DST_NONE,
	DST_MIDDLE_VALUE,
	DST_PEAK_VALUE,
	DST_AVERAGE,
};

// Segmented Raw Detection Data
struct R7047
{
	u16 header_size;
	u32 number_of_segments;
	u16 segment_field_size;
	u32 number_of_rx_detections;
	u16 rx_field_size;
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	f32 sound_velocity_at_transducer;
	f32 rx_delay;
};

struct R7047SEGMENTDATA
{
	u16 segment_number;
	f32 tx_angle_along;
	f32 tx_angle_across;
	f32 tx_delay;
	f32 frequency;
	u32 pulse_type;
	f32 chirp_heave;
	f32 tx_pulse_width;
	f32 tx_beam_width_across;
	f32 tx_beam_width_along;
	u32 tx_pulse_envelope_type;
	f32 tx_pulse_envelope_parameter;
	f32 tx_relative_source_level;
	f32 rx_beam_width;
	u8 detection_algorithm;
	u32 flags;
	f32 sampling_rate;
	u8 tvg;
	f32 rx_bandwidth;
};

struct R7047DETECTIONDATA
{
	u16 detection_number;
	u16 segment_number;
	f32 detection_point;
	f32 rx_angle_across;
	u32 flags;
	u32 quality;
	f32 uncertainty;
	f32 signal_strength;
	f32 signal_ratio;
};

#define R7047DETECTIONDATA_FLAGS_MAGNITUDE_BIT         0x00000001  // bit 0
#define R7047DETECTIONDATA_FLAGS_PHASE_BIT             0x00000002  // bit 1
#define R7047DETECTIONDATA_FLAGS_SNIPPETS_DETECT_BIT   0x00004000  // bit 14

#define R7047DETECTIONDATA_QUALITY_BRIGHTNESS_BIT  0x0001  // bit 0
#define R7047DETECTIONDATA_QUALITY_COLINEARITY_BIT 0x0002  // bit 1

// Calibrated Beam Data
struct R7048
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u16 first_beam;
	u16 beams;
	u32 samples;
	u8 fls_flag;
	u8 cal_flag;
	u32 reserved[8];
};

// System Events
struct R7050
{
	u64 serial_number;
	u32 events;
};

struct RD7050
{
	u16 event_type;
	u16 event_identifier;
	u32 device_identifier;
	u16 system_enumerator;
	u16 message_length;
	TIME_7K time_stamp;
};

// System Event Message
struct R7051
{
	u64 serial_number;
	u16 event_id;
	u16 size;
	u16 event_identifier;
};

// RDR Recording Status - Detailed
struct R7052
{
	u32 position;
	u8 percent_disk_free;
	u8 mode;  // see enum RDRMODE
	u32 num_records;
	u64 size;
	TIME_7K first_time_stamp;
	TIME_7K last_time_stamp;
	u32 total_time;
	c8 directory_name[256];
	c8 file_name[256];
	u32 rdr_error;
	u32 flags;
	u32 logger_ip_address;
	u8 single_file;
	u8 history;
	u16 reserved1;
	u32 reserved2[4];
};

#define R7052_FLAGS_EXTERNAL_LOGGER_SUPPORTED_BIT 0x01  // bit 0
#define R7052_FLAGS_EXTERNAL_LOGGER_ATTACHED_BIT  0x02  // bit 1
#define R7052_FLAGS_EXTERNAL_LOGGER_CONFIRMED_BIT 0x04  // bit 2
#define R7052_FLAGS_CUSTOM_LOGGER_SUPPORTED_BIT   0x08  // bit 3

enum RDRMODE
{
	RDRMODE_STOPPED   = 0,
	RDRMODE_RECORDING = 1,
	RDRMODE_PLAYING   = 2,
	RDRMODE_DELETING  = 3,
	RDRMODE_STOPPING  = 4,
};

// Calibrated Side-Scan Data
struct R7057
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	f32 beam_position;
	u32 control;
	u32 samples;
	f32 port_beam_width_y;
	f32 port_beam_width_z;
	f32 star_beam_width_y;
	f32 star_beam_width_z;
	f32 port_beam_steer_angle_y;
	f32 port_beam_steer_angle_z;
	f32 star_beam_steer_angle_y;
	f32 star_beam_steer_angle_z;
	u16 beams_per_side;
	u16 beam;
	u8 bytes_per_sample;
	u8 data_type;
	u8 error_flag;
};

// Used for 7058 and 7028
struct BEAM_RECORD
{
	u16 beam_number;
	u32 min_sample;
	u32 bd_sample;
	u32 max_sample;
};

// Snippet Backscattering Strength
struct R7058
{
	u64 serial_number;
	u32 ping_number;
	u16 multiping_sequence;
	u16 detections;
	u8 error_flags;
	u32 control_flags;
	f32 absorption;
	u32 reserved[6];
};

#define R7058_CONTROL_FLAGS_BRIGHTNESS_BIT        0x00000001  // bit 0
#define R7058_CONTROL_FLAGS_COLINEARITY_BIT       0x00000002  // bit 1
#define R7058_CONTROL_FLAGS_BOTTOM_DETECT_BIT     0x00000004  // bit 2
#define R7058_CONTROL_FLAGS_SNIPPET_DISPLAY_BIT   0x00000008  // bit 3
#define R7058_CONTROL_FLAGS_MIN_WINDOW_BIT        0x00000010  // bit 4
#define R7058_CONTROL_FLAGS_MAX_WINDOW_BIT        0x00000020  // bit 5
#define R7058_CONTROL_FLAGS_FOOTPRINT_BIT         0x00000040  // bit 6
#define R7058_CONTROL_FLAGS_NOT_PER_UNIT_BIT      0x00000080  // bit 7
#define R7058_CONTROL_FLAGS_SINGLE_ABSORPTION_BIT 0x00000100  // bit 8

// MB2 Specific Status
struct R7059
{
	c8 storage_directory_name[256];
	c8 storage_prepend_file_name[256];
	c8 storage_trailer_file_name[256];
	u8 storage_prepend_header;
	u8 storage_append_trailer;
	u8 storage_enabled;
	c8 playback_directory_name[256];
	c8 playback_file_name[256];
	i32 playback_mode;
	u8 playback_enabled;
	c8 rrio_address1[256];
	c8 rrio_address2[256];
	c8 rrio_address3[256];
	u8 use_builtin_posmv;
	u8 use_attached_svp;
	u8 enable_stacking;
	u8 stacking_value;
	u8 port_zda_baud;
	u8 port_zda_parity;
	u8 port_zda_data;
	u8 port_zda_stop;
	u8 port_gga_baud;
	u8 port_gga_parity;
	u8 port_gga_data;
	u8 port_gga_stop;
	u8 port_svp_baud;
	u8 port_svp_parity;
	u8 port_svp_data;
	u8 port_svp_stop;
	u8 port_hpr_baud;
	u8 port_hpr_parity;
	u8 port_hpr_data;
	u8 port_hpr_stop;
	u8 port_hdt_baud;
	u8 port_hdt_parity;
	u8 port_hdt_data;
	u8 port_hdt_stop;
	u16 port_sui_rrio;
	u8 keep_org_time_stamps;
	u8 reserved1;
	u32 reserved2[505];
};

// Subscriber information
// Remote control record 1053 Third Party Data Connection
#define MAX_BROADCAST_RECORDS    64

struct SUBSCRIBER_CONNECT
{
	u32 address;
	u16 port;
	u16 type;
	u32 num_records;
	u32 records[MAX_BROADCAST_RECORDS];
};

// Remote control record 1054 Delete Third Party Data Connection
struct SUBSCRIBER_DISCONNECT
{
	u32 address;
	u16 port;
	u16 type;
};

struct SUBSCRIBER_INFO
{
	SUBSCRIBER_CONNECT connection_info;
	u32 reserved[128];
};

// Subscriptions
struct R7053
{
	i32 num_subscribers;
};

// RDR Storage Recording - Short Update
struct R7054
{
	u16 disk_free_percent;
	u32 num_records;
	u64 size;
	u32 reserved[4];

// The fields below are implemented for the standalone 7kLogger
#ifdef EXTENDED_7054
	u8 mode;  // see enum RDRMODE
	c8 file_name[256];
	u32 rdr_error;
	u64 data_rate;
	u32 minutes_space_left;
#endif
};

// Calibration Status
struct R7055
{
	u64 serial_number;
	u16 calibration_status;
	u16 calibration_percent_complete;
	TIME_7K completion_time;
	c8 status_message[800];
	u32 sub_status;
	u8 cal_systems;
	u8 cal_systems_done;
	u8 current_cal_system_enum;
	u8 startup_cal;
	u16 status_by_enum[8];
	u32 reserved[2];
};

// File Header
struct R7200
{
	u64 file_identifier[2];
	u16 version_number;
	u16 reserved;
	u64 session_identifier[2];
	u32 rd_size;
	u32 subsystems;
	c8 recording_name[64];
	c8 recording_program_version[16];
	c8 user_name[64];
	c8 notes[128];
};

struct R7200DEVICE
{
	u32 device_identifier;
	u16 system_enumerator;
};

struct R7200_OD
{
	u32 size;
	u64 offset;
};

// File Catalog Record
struct R7300
{
	u32 size;
	u16 version;
	u32 num_records;
	u32 reserved;
};

struct R7300DATA
{
	u32 size;
	u64 offset;
	u16 record_type;
	u16 device_identifier;
	u16 system_enumerator;
	TIME_7K time_stamp;
	u32 record_count;
	u16 reserved[8];
};

// Time Message
struct R7400
{
	i8 leap_second;
	u8 pulse_flag;
	u16 port_identifier;
	u32 reserved1;
	u64 reserved2;
};

struct R7400_OptionalData
{
	f64 utc_time;
	f64 external_time;
	f64 t0_time;
	f64 t1_time;
	f64 pulse_length;
	f64 difference;
	u16 io_module_status;
};

// Remote Control
struct R7500
{
	u32 rc_id;
	u32 ticket;
	u64 tracking_number[2];
};

// Multi-ping Control Enable
struct R7500sub1111
{
	u16 num_pings;
	u32 frequency_begin;
	i32 frequency_spacing;
};

// Remote Control Acknowledge
struct R7501
{
	u32 ticket;
	u64 tracking_number[2];
};

// Remote Control Not Acknowledge
struct R7502
{
	u32 ticket;
	u64 tracking_number[2];
	u32 error_code;
};

// Remote Control Sonar Settings
struct R7503
{
	u64 serial_number;
	u32 ping_number;
	f32 frequency;
	f32 sample_rate;
	f32 receiver_bandwidth;
	f32 pulse_width;
	u32 pulse_type;  // see enum PULSE_TYPE
	u32 pulse_envelope_type;  // see enum TTransmitEnvelopeFunc
	f32 pulse_envelope_parameter;
	u16 pulse_mode;
	u16 pulse_reserved;
	f32 max_ping_rate;
	f32 ping_period;
	f32 range;
	f32 power;
	f32 gain;
	u32 control_flags;
	u32 projector_magic_number;
	f32 projector_beam_steer_x;
	f32 projector_beam_steer_z;
	f32 projector_beam_width_x;
	f32 projector_beam_width_z;
	f32 projector_beam_focal_point;
	u32 projector_beam_weighting_type;
	f32 projector_beam_weighting_parameter;
	u32 transmit_flags;
	u32 hydrophone_magic_number;
	u32 hydrophone_beam_weighting_type;
	f32 hydrophone_beam_weighting_parameter;
	u32 receive_flags;
	f32 range_filter_min;
	f32 range_filter_max;
	f32 depth_filter_min;
	f32 depth_filter_max;
	f32 absorption;
	f32 sound_velocity;
	f32 spreading_loss;
	u8 vernier_mode;  // see enum VERNIER_MODE
	u8 search_window;
	OffsetTriplet tx_array_offset;
	f32 head_tilt_x;
	f32 head_tilt_y;
	f32 head_tilt_z;
	u32 ping_on_off_state;  // see enum PING_STATE
	u16 beam_spacing_mode;  // see enum BEAMSPACINGTYPE
	u16 center_mode;  // see enum SYSMODE
	f32 ag_depth_filter_min;
	f32 ag_depth_filter_max;
	f64 trigger_out_length;
	f64 trigger_out_offset;
	u16 projector_81xx;
	u32 reserved1[2];
	f32 gain_alternate;
	u8 vernier_filter;
	u8 reserved2;
	u16 custom_beams;
	f32 coverage_angle;
	u8 was_coverage_mode;
	u8 was_quality_filter_flags;
	f32 rx_steering_angle;
	f32 flex_sector_coverage;
	f32 flex_sector_steering;
	f32 constant_spacing;
	u16 beam_mode_selection;
	f32 depth_gate_tilt;
	f32 applied_frequency;
	u32 element_selection;
};

// Common System Settings
struct R7504
{
	u64 serial_number;
	u32 ping_number;
	f32 sound_velocity;
	f32 absorption;
	f32 spreading_loss;
	u32 sequencer_control;
	u8 format;
	u8 baud;
	u8 parity;
	u8 data;
	u8 stop;
	u8 orientation;
	u8 record_version;
	f32 motion_latency;
	u8 svp_filter;  // see enum SVFILTER
	u8 sv_manual_override;
	u16 active_enumerator;
	u32 active_device_id;
	u32 system_mode;  // see enum SYSMODE
	u32 dual_head_mode;  // see enum DualHeadMode
	u32 tracker_flags;  // see R7500sub1402 bit flags
	f32 tracker_swath_width;
	R7500sub1045 multi_detect_params;
	u8 slave_ipv4_address[4];
	R7500sub1118 snippet_params;
	u32 full_rate_dual_head;
	f32 was_master_delay_multiplier;
	R7500sub1046 power_save_mode;
	R7500sub1047 auv_goodies;
	R7500sub7042 compressed_wc_params;
	u8 deck_mode;
	u8 reserved1;
	u8 power_mode_flags;
	u8 power_mode_max;
	f32 temperature_c;
	u8 sensor_manual_override;
	u8 sensor_data_flags;
	u8 sensor_active_flags;
	u8 reserved2;
	f32 tracker_max_coverage_angle;
	u16 duty_cycle_method;  // see enum DUTY_CYCLE_LIMIT_TYPE
	u16 reserved3;
	u32 reserved4[99];
};

// For power_mode_flags in R7504 and R7500sub1609
#define POWER_MODE_FLAGS_SUPPORTED_BIT   0x01  // bit 0
#define POWER_MODE_FLAGS_THROTTLED_BIT   0x02  // bit 1
#define POWER_MODE_FLAGS_AC_BIT          0x04  // bit 2

// For sensor flags in R7504
#define R7504_SENSOR_SOUND_VELOCITY_BIT  0x01  // bit 0
#define R7504_SENSOR_TEMPERATURE_BIT     0x02  // bit 1

// Filtered Sound Velocity
struct R7510
{
	f32 sensor_sv;
	f32 filtered_sv;
	u8 filter_type;
};

// System Lock Status
struct R7511
{
	u16 system_locked;
	u32 client_address;
	u32 reserved[8];
};

// Sound Velocity
struct R7610
{
	f32 sound_velocity;
	f32 temperature_k;
	f32 pressure;
};

// Absorption
struct R7611
{
	f32 absorption;
};

// Spreading Loss
struct R7612
{
	f32 spreading_loss;
};

// SB channel settings
struct R10000
{
	u32 ping_number;
	u32 multiping_sequence;
	u32 time_state;
	u32 transport_latency;
	f32 frequency_center;
	f32 sweep_width;
	f32 sample_rate;
	f32 receiver_bandwidth;
	f32 absorption;
	f32 spreading_loss;
	f32 initial_gain;
	f32 range;
	f32 reserved;
	f32 power;
	f32 pulse_length;
	u32 pulse_type;  // see enum PULSE_TYPE
	u32 pulse_envelope_type;  // see enum TTransmitEnvelopeFunc
	f32 pulse_envelope_parameter;
	u32 multiping_count;
	u32 reserved_for_interleaved_points;
	f32 max_ping_rate;
	f32 ping_period;
	f32 reserved1;
	u32 projector_id;
	f32 projector_beam_width_across;
	f32 projector_beam_width_along;
	u32 receiver_id;
	f32 receive_beam_width_across;
	f32 receive_beam_width_along;
	f32 corrected_transducer_draft;
	f32 absorption_tweak;
	f32 pulse_length_tweak;
	f32 spreading_loss_tweak;
	f32 initial_gain_tweak;
	f32 range_tweak;
	f32 power_tweak;
	f32 gate_min;
	f32 gate_max;
	u32 gate_mode;
};

// SB channel status
struct R10003
{
	u32 ping_number;
	f32 filtered_ping_rate;
};

// SB system settings
struct R10004
{
	u32 channels;
	u32 ping_pong;
	f32 mean_sound_velocity;
	u32 trigger_out_polarity;
	u32 trigger_out_mode;
	u32 trigger_in_enabled;
	f32 trigger_in_delay;
	u32 trigger_in_active_edge;
	f32 trigger_out_duration;
	f32 trigger_out_delay;
	u32 blanking_pin;
	u32 gating_pin;
	u32 tracker_mode;
	u32 operation_mode;
	u32 tracker_modes_1;
	u32 system_state;
	u32 time_source_current;
	u32 time_sources_enabled;
	u32 time_sources_active;
	u32 time_source_current_ntp_ipv4;
	u8  time_source_current_ntp_name[32];
	u32 time_source_current_uipc_ipv4;
	u8  time_source_current_uipc_name[32];
};

#define R10004_SOURCE_ZDA_PPS 1
#define R10004_SOURCE_NTP     2
#define R10004_SOURCE_UIPC    4

#define R10004_SYSTEM_STATE_CONFIGURATION 10
#define R10004_SYSTEM_STATE_OPERATION     20

// SB echogram water column
struct R10018
{
	u32 ping_number;
	u32 multiping_sequence;
	f32 mean_sound_velocity;
	f32 not_applied_transducer_draft;
	f32 sample_rate;
	f32 effective_pulse_length;
	f32 start_sample_delay;
	u32 bits_per_sample;
	u32 full_scale;
	u32 sample_count;
};

// SB raw detections
struct R10027
{
	u32 ping_number;
	u32 multiping_sequence;
	u32 detection_count;
	u32 data_field_size;
	f32 mean_sound_velocity;
	f32 sample_rate;
	f32 reserved[4];
	f32 not_applied_corrected_transducer_draft;
};

struct R10027Data
{
	u32 detection_method;
	f32 range;
	f32 not_applied_heave;
	f32 amplitude;
	f32 snr;
	f32 seabed_confidence;
	f32 colinearity;
	u32 classifier;
};

struct R10038
{
	u32 ping_number;
	u32 multiping_sequence;
	f32 mean_sound_velocity;
	f32 not_applied_transducer_draft;
	f32 sample_rate;
	f32 effective_pulse_length;
	f32 start_sample_delay;
	u32 bits_per_sample;
	u32 full_scale;
	u32 sample_count;
	u32 reserved[20];
};

struct R10038Data
{
	f32 real;
	f32 imag;
};

struct R10039
{
	u32 ping_number;
	u32 multiping_sequence;
	u32 flag_field_count;
	u32 reserved[20];
};

// SB depth
struct R10049
{
	f32 depth_meter;
	f32 depth_feet;
};

// SB serial port configuration (static part)
struct R10060
{
	u32 port_count;
	u32 data_size;
	u32 reserved[10];
};

// SB serial port configuration (dynamic part)
struct R10060Data
{
	u32 port_index;
	u16 flags;
	u16 reserved1;
	u64 system_function;
	u32 phy_setting;
	u32 baud_rate;
	u32 data_bits;
	u32 stop_bits;
	u32 parity_index;
	u32 sentence_index_0;
	u32 reserved2[3];
	c8 label_on_box[32];
};

// SB serial port status (static part)
struct R10061
{
	u32 port_count;
	u32 data_size;
	u32 reserved[10];
};

// SB serial port status (dynamic part)
struct R10061Data
{
	u32 port_index;
	u32 status;
};

// SB serial port QC
struct R10062
{
	u32 port_index;
	u32 byte_count;
	u32 message_count;
	u32 error_count;
	u32 status;
	u32 reserved1;
	u64 sentence_start_time_us;
	u64 sentence_end_time_us;
	u32 sentence_byte_count;
	u32 sentence_direction;
	u32 reserved2[8];
	u8 sentence_content[512];
};

// SB multicast port configuration
struct R10063
{
	u32 count;
	u32 reserved0;
	u32 reserved1;
};

struct R10063Data
{
	u32 multicast_index;
	u32 group_ip;
	u16 port;
	u16 flags;
	u16 sentence_index;
	u16 reserved0;
	u32 depthChan;
};

#pragma pack(pop)

#endif  // DEFINITIONS7K_H
