#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <esp_timer.h>

#include <string>
#include <mutex>
#include <deque>
#include <vector>
#include <memory>

#include "protocol.h"
#include "ota.h"
#include "audio_service.h"
#include "device_state_event.h"

#define MAIN_EVENT_SCHEDULE (1 << 0)
#define MAIN_EVENT_SEND_AUDIO (1 << 1)
#define MAIN_EVENT_WAKE_WORD_DETECTED (1 << 2)
#define MAIN_EVENT_VAD_CHANGE (1 << 3)
#define MAIN_EVENT_ERROR (1 << 4)
#define MAIN_EVENT_CHECK_NEW_VERSION_DONE (1 << 5)

enum AecMode {
    kAecOff,
    kAecOnDeviceSide,
    kAecOnServerSide,
};

<<<<<<< HEAD
=======
enum DeviceState {
    kDeviceStateUnknown,
    kDeviceStateStarting,
    kDeviceStateWifiConfiguring,
    kDeviceStateIdle,
    kDeviceStateConnecting,
    kDeviceStateListening,
    kDeviceStateSpeaking,
    kDeviceStateUpgrading,
    kDeviceStateActivating,
    kDeviceStateAudioTesting,
    kDeviceStateFatalError,
    kDeviceStateSetting,
    kDeviceStateSleep,
};

#define OPUS_FRAME_DURATION_MS 60
#define MAX_AUDIO_PACKETS_IN_QUEUE (2400 / OPUS_FRAME_DURATION_MS)
#define AUDIO_TESTING_MAX_DURATION_MS 10000

>>>>>>> fix-pdm-record
class Application {
public:
    static Application& GetInstance() {
        static Application instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void Start();
    DeviceState GetDeviceState() const { return device_state_; }
<<<<<<< HEAD
    bool IsVoiceDetected() const { return audio_service_.IsVoiceDetected(); }
=======
    DeviceState GetDeviceLastState() const { return device_last_state_; }
    bool IsVoiceDetected() const { return voice_detected_; }
>>>>>>> fix-pdm-record
    void Schedule(std::function<void()> callback);
    void SetDeviceState(DeviceState state);
    void Alert(const char* status, const char* message, const char* emotion = "", const std::string_view& sound = "");
    void DismissAlert();
    void AbortSpeaking(AbortReason reason);
    void ToggleChatState();
    void StartListening();
    void StopListening();
    void Reboot();
    void WakeWordInvoke(const std::string& wake_word);
    bool CanEnterSleepMode();
    void SendMcpMessage(const std::string& payload);
    void SetAecMode(AecMode mode);
    AecMode GetAecMode() const { return aec_mode_; }
<<<<<<< HEAD
    void PlaySound(const std::string_view& sound);
    AudioService& GetAudioService() { return audio_service_; }
=======
    BackgroundTask* GetBackgroundTask() const { return background_task_; }
    // Add for XiaoZhi Card
    void EnterSleepMode(uint8_t mode);
    void ExitSleepMode();
    void Shutdown();
    void FullRefresh();
    void PlayClickSound(); 
>>>>>>> fix-pdm-record

    TimerHandle_t shutdown_timer_;
    void InitialAutoShutdown(uint32_t auto_shutdown_time_s); 
    static void ShutdownTimerCallback(TimerHandle_t xTimer);
    void ResetShutdownTimer();

    void ResetDecoder();
private:
    Application();
    ~Application();

    std::mutex mutex_;
    std::deque<std::function<void()>> main_tasks_;
    std::unique_ptr<Protocol> protocol_;
    EventGroupHandle_t event_group_ = nullptr;
    esp_timer_handle_t clock_timer_handle_ = nullptr;
    volatile DeviceState device_last_state_ = kDeviceStateUnknown;
    volatile DeviceState device_state_ = kDeviceStateUnknown;
    ListeningMode listening_mode_ = kListeningModeAutoStop;
    AecMode aec_mode_ = kAecOff;
    std::string last_error_message_;
    AudioService audio_service_;

    bool has_server_time_ = false;
    bool aborted_ = false;
    int clock_ticks_ = 0;
    TaskHandle_t check_new_version_task_handle_ = nullptr;

    void MainEventLoop();
<<<<<<< HEAD
    void OnWakeWordDetected();
    void CheckNewVersion(Ota& ota);
    void ShowActivationCode(const std::string& code, const std::string& message);
=======
    void OnAudioInput();
    void OnAudioOutput();
    bool ReadAudio(std::vector<int16_t>& data, int sample_rate, int samples);
    void SetDecodeSampleRate(int sample_rate, int frame_duration);
    void CheckNewVersion();
    void ShowActivationCode();
>>>>>>> fix-pdm-record
    void OnClockTimer();
    void SetListeningMode(ListeningMode mode);
};

#endif // _APPLICATION_H_
