#include "pch.h"
#include "Windows.Kinect.KinectSensor.h"
#include "Windows.Kinect.KinectSensor.g.cpp"


namespace winrt::Windows::Kinect::implementation
{
    winrt::Windows::Kinect::KinectSensor KinectSensor::GetDefault()
    {
        return winrt::make<KinectSensor>();
    }
    winrt::Windows::Foundation::Collections::IObservableMap<hstring, winrt::Windows::Kinect::KinectSensor> KinectSensor::Sensors()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::event_token KinectSensor::IsPausedChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::KinectSensor, winrt::Windows::Kinect::IsPausedChangedEventArgs> const& value)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void KinectSensor::IsPausedChanged(winrt::event_token const& token) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void KinectSensor::Open()
    {
        LOG_WARNING("[KinectSensor] Open\n");
    }
    void KinectSensor::Close()
    {
        LOG_WARNING("[KinectSensor] Close\n");
    }
    bool KinectSensor::IsOpen()
    {
        LOG_WARNING("[KinectSensor] IsOpen\n");
        return false;
    }
    bool KinectSensor::IsPaused()
    {
        LOG_WARNING("[KinectSensor] IsPaused\n");
        return false;
    }
    winrt::Windows::Kinect::ColorFrameSource KinectSensor::ColorFrameSource()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::DepthFrameSource KinectSensor::DepthFrameSource()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyFrameSource KinectSensor::BodyFrameSource()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyIndexFrameSource KinectSensor::BodyIndexFrameSource()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::InfraredFrameSource KinectSensor::InfraredFrameSource()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::AudioSource KinectSensor::AudioSource()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::MultiSourceFrameReader KinectSensor::OpenMultiSourceFrameReader(winrt::Windows::Kinect::FrameSourceTypes const& enabledFrameSourceTypes)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::CoordinateMapper KinectSensor::CoordinateMapper()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    hstring KinectSensor::UniqueKinectId()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
}
