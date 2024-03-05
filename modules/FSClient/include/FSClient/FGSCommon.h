#include <cstdint>

namespace FGS
{
    constexpr uint8_t TEAM_NO = 0; //This will be updated during competition

    // The messages from GS to FS 
    enum class MessageType : uint8_t
    {
        GS_FS_SetState = 0,
        FS_GS_SetStateACK
    };


    enum class FlightState : uint8_t
    {
        NotFlying = 0,
        TakeOff,
        Land,
        SecureRootFollow,
        RouteFollow,
        FollowTaskTend,
        FollowTaskPounce,
        EscapeTaskPounce,
        EscapeTaskCollision,
        QRTask,
        FailSafe,
        ManualMode
    };

    enum class EscapeBehaviour : uint8_t {
        Return_Secure_Route,
        Try_Safe,
        Ask_Rapid_Movement,
        Switch_Manual_Control
    };

    enum class LogLevel : uint8_t {
        Trace,
        Info,
        Debug,
        Error
    };

    enum class RiskPolicy : uint8_t {
        None,
        Low,
        Medium,
        High
    };

    //Common Structs
    struct CommonClock
    {
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
        uint16_t millisecond;
    };

    struct CommonCoordinate
    {
        double latitude;
        double longtitude;
    };

    struct CommonTelemetry
    {
        uint8_t team_no;

        //Position Data
        CommonCoordinate coordinate;
        float UAV_altitude; //in meter

        //Angle Data in Degree
        float UAV_pitch;
        float UAV_yaw;
        float UAV_roll;
    };

    struct OpponentTelemetry
    {
        CommonTelemetry common;
        double time_difference; //in milliseconds
    };


    struct Telemetry {
        CommonTelemetry common;

        float UAV_Battery; //battery state in percent

        bool is_auto; //is UAV in auto-mode during flight
        bool is_pounce; //is UAV in pounce mode, (NOT FOLLOW TARGET TENDENCY MODE!!!)

        uint16_t target_center_x; // if (is_pounce) the x component of target in frame else 0
        uint16_t target_center_y; // if (is_pounce) the y component of target in frame else 0

        uint16_t target_width; // if (is_pounce) the width of drawn rectangle of target in frame else 0
        uint16_t target_height;// if (is_pounce) the height of drawn rectangle of target in frame else 0

        CommonClock GPS_Clock; //the clock of gps module

        FlightState state;
    };

    struct PounceInformation
    {
        CommonClock start_time;
        CommonClock finish_time;

        bool is_auto;
        bool is_successful; //extra, if this is true; then the GS should send it to server, otherwise the server should log it
    };


    struct QRCodeInformation
    {
        CommonClock start_time;
        CommonClock finish_time;

        char qr_code_text[40];
        //in competition, we will use version 1 QR Code, so it can hold to 152 bits, so 40*4bit should be enough

        bool is_successful;
    };
}