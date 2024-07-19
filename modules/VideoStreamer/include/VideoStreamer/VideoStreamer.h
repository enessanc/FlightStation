#pragma once
#include "FGSCommon/FGSCommon.h"
#include "TSML.h"
#include "opencv2/opencv.hpp"

namespace FS
{
    enum class VideoStreamerExceptions : uint8_t
    {
        VideoNotOpened = 0
    };

    struct VideoContext
    {
        std::string h264_software_stream = " appsrc ! videoconvert !  video/x-raw,width=1280,height=720 ! "
        " x264enc tune=zerolatency speed-preset=ultrafast threads=4 ! tee name=t ! "
        " queue ! rtph264pay ! udpsink host=127.0.0.1 port=5000 t. ! "
        " queue ! matroskamux ! filesink location=flight_record_h264s.mkv " ;

        std::string h264_hardware_stream;
        std::string h265_software_stream;
        std::string h265_hardware_stream;
    };

    class VideoStreamer final : public TSML::ThreadNode<CommonMsg, VideoStreamerExceptions>
    {
    public:
        explicit VideoStreamer(TSML::TSMLContext<CommonMsg> *context , std::string node_id = "VideoStreamer");

    protected:
        void OnInitialize() override;
        void OnRun() override;
        void OnMessage(TSML::Message<CommonMsg> msg) override;
        void OnFinish() override;
        void OnException(const TSML::TSMLException<VideoStreamerExceptions>& e) override;

    private:
        cv::Mat OnFrameUpdate(const cv::Mat& frame);
        FS::VideoStreamerStatus status;

        VideoContext video_context;

        cv::VideoCapture video_capturer;
        cv::VideoWriter video_writer;
    };

}
