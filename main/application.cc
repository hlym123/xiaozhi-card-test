#include "application.h"
#include "board.h"
#include "display.h"
#include "epd_display.h"
#include "system_info.h"
#include "audio_codec.h"
#include "mqtt_protocol.h"
#include "websocket_protocol.h"
#include "font_awesome_symbols.h"
#include "assets/lang_config.h"
#include "mcp_server.h"
<<<<<<< HEAD
=======
#include "audio_debugger.h"
#include "esp_lvgl_port.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
 

#if CONFIG_USE_AUDIO_PROCESSOR
#include "afe_audio_processor.h"
#else
#include "no_audio_processor.h"
#endif

#if CONFIG_USE_AFE_WAKE_WORD
#include "afe_wake_word.h"
#elif CONFIG_USE_ESP_WAKE_WORD
#include "esp_wake_word.h"
#else
#include "no_wake_word.h"
#endif
>>>>>>> fix-pdm-record

#include <cstring>
#include <esp_log.h>
#include <cJSON.h>
#include <driver/gpio.h>
#include <arpa/inet.h>

#define TAG "Application"


extern QueueHandle_t upgrade_queue;

static const char* const STATE_STRINGS[] = {
    "unknown",
    "starting",
    "configuring",
    "idle",
    "connecting",
    "listening",
    "speaking",
    "upgrading",
    "activating",
    "audio_testing",
    "fatal_error",
    "invalid_state"
};

Application::Application() {
    event_group_ = xEventGroupCreate();
<<<<<<< HEAD
=======
    background_task_ = new BackgroundTask(4096 * 8);
>>>>>>> fix-pdm-record

#if CONFIG_USE_DEVICE_AEC && CONFIG_USE_SERVER_AEC
#error "CONFIG_USE_DEVICE_AEC and CONFIG_USE_SERVER_AEC cannot be enabled at the same time"
#elif CONFIG_USE_DEVICE_AEC
    aec_mode_ = kAecOnDeviceSide;
#elif CONFIG_USE_SERVER_AEC
    aec_mode_ = kAecOnServerSide;
#else
    aec_mode_ = kAecOff;
#endif

<<<<<<< HEAD
    esp_timer_create_args_t clock_timer_args = {
        .callback = [](void* arg) {
            Application* app = (Application*)arg;
            app->OnClockTimer();
=======
#if CONFIG_USE_AUDIO_PROCESSOR
    audio_processor_ = std::make_unique<AfeAudioProcessor>();
#else
    audio_processor_ = std::make_unique<NoAudioProcessor>();
#endif

#if CONFIG_USE_AFE_WAKE_WORD
    wake_word_ = std::make_unique<AfeWakeWord>();
#elif CONFIG_USE_ESP_WAKE_WORD
    wake_word_ = std::make_unique<EspWakeWord>();
#else
    wake_word_ = std::make_unique<NoWakeWord>();
#endif

    // esp_timer_create_args_t clock_timer_args = {
    //     .callback = [](void* arg) {
    //         Application* app = (Application*)arg;
    //         app->OnClockTimer();
    //     },
    //     .arg = this,
    //     .dispatch_method = ESP_TIMER_TASK,
    //     .name = "clock_timer",
    //     .skip_unhandled_events = true
    // };
    // esp_timer_create(&clock_timer_args, &clock_timer_handle_);

    Application* app = this;  
    xTaskCreate(
        [](void* arg) {
            Application* app = static_cast<Application*>(arg);
            TickType_t last_wake_time = xTaskGetTickCount();
            const TickType_t interval = pdMS_TO_TICKS(1000);  
            while (true) {
                vTaskDelayUntil(&last_wake_time, interval);  
                app->OnClockTimer();
            }
>>>>>>> fix-pdm-record
        },
        "ClockTask",
        4096,
        this, 
        2,
        nullptr
    );
}

Application::~Application() {
    if (clock_timer_handle_ != nullptr) {
        esp_timer_stop(clock_timer_handle_);
        esp_timer_delete(clock_timer_handle_);
    }
    vEventGroupDelete(event_group_);
}

void Application::CheckNewVersion(Ota& ota) {
    const int MAX_RETRY = 10;
    int retry_count = 0;
    int retry_delay = 5; // 初始重试延迟为5秒

    auto& board = Board::GetInstance();
    while (true) {
        SetDeviceState(kDeviceStateActivating);
        auto display = board.GetDisplay();
        display->SetStatus(Lang::Strings::CHECKING_NEW_VERSION);
<<<<<<< HEAD

        if (!ota.CheckVersion()) {
=======
        if (!ota_.CheckVersion()) {
>>>>>>> fix-pdm-record
            retry_count++;
            if (retry_count < 3) {
                continue;
            }

            if (retry_count >= MAX_RETRY) {
                ESP_LOGE(TAG, "Too many retries, exit version check");
                return;
            }

            char buffer[128];
            snprintf(buffer, sizeof(buffer), Lang::Strings::CHECK_NEW_VERSION_FAILED, retry_delay, ota.GetCheckVersionUrl().c_str());
            Alert(Lang::Strings::ERROR, buffer, "sad", Lang::Sounds::P3_EXCLAMATION);

            ESP_LOGW(TAG, "Check new version failed, retry in %d seconds (%d/%d)", retry_delay, retry_count, MAX_RETRY);
            for (int i = 0; i < retry_delay; i++) {
                vTaskDelay(pdMS_TO_TICKS(1000));
                if (device_state_ == kDeviceStateIdle) {
                    break;
                }
            }
            retry_delay *= 2; // 每次重试后延迟时间翻倍
            continue;
        }
        retry_count = 0;
        retry_delay = 10; // 重置重试延迟时间

<<<<<<< HEAD
        if (ota.HasNewVersion()) {
            Alert(Lang::Strings::OTA_UPGRADE, Lang::Strings::UPGRADING, "happy", Lang::Sounds::P3_UPGRADE);

            vTaskDelay(pdMS_TO_TICKS(3000));

            SetDeviceState(kDeviceStateUpgrading);
            
            display->SetIcon(FONT_AWESOME_DOWNLOAD);
            std::string message = std::string(Lang::Strings::NEW_VERSION) + ota.GetFirmwareVersion();
            display->SetChatMessage("system", message.c_str());

            board.SetPowerSaveMode(false);
            audio_service_.Stop();
            vTaskDelay(pdMS_TO_TICKS(1000));

            bool upgrade_success = ota.StartUpgrade([display](int progress, size_t speed) {
                char buffer[64];
                snprintf(buffer, sizeof(buffer), "%d%% %uKB/s", progress, speed / 1024);
                display->SetChatMessage("system", buffer);
            });

            if (!upgrade_success) {
                // Upgrade failed, restart audio service and continue running
                ESP_LOGE(TAG, "Firmware upgrade failed, restarting audio service and continuing operation...");
                audio_service_.Start(); // Restart audio service
                board.SetPowerSaveMode(true); // Restore power save mode
                Alert(Lang::Strings::ERROR, Lang::Strings::UPGRADE_FAILED, "sad", Lang::Sounds::P3_EXCLAMATION);
                vTaskDelay(pdMS_TO_TICKS(3000));
                // Continue to normal operation (don't break, just fall through)
            } else {
                // Upgrade success, reboot immediately
                ESP_LOGI(TAG, "Firmware upgrade successful, rebooting...");
                display->SetChatMessage("system", "Upgrade successful, rebooting...");
                vTaskDelay(pdMS_TO_TICKS(1000)); // Brief pause to show message
                Reboot();
                return; // This line will never be reached after reboot
            }
=======
        /* 有新版本 --> 升级/跳过 */
        if (ota_.HasNewVersion()) {
            display->SetStatus("检查到新版本");
            upgrade_queue = xQueueCreate(5, sizeof(int));

            lvgl_port_lock(0);
            lv_obj_add_flag(display->content_, LV_OBJ_FLAG_HIDDEN);
            if (display->main_btn_confirm_upgrade_) {
                lv_obj_clear_flag(display->main_btn_confirm_upgrade_, LV_OBJ_FLAG_HIDDEN);
            }
            if (display->main_btn_skip_upgrade_) {
                lv_obj_clear_flag(display->main_btn_skip_upgrade_, LV_OBJ_FLAG_HIDDEN);
            }
            lvgl_port_unlock();

            // 阻塞等待用户选择
            int upgrade = 0;
            if (!xQueueReceive(upgrade_queue, &upgrade, pdMS_TO_TICKS(20000))) {
                ESP_LOGW(TAG, "User did not respond to upgrade prompt.");
                upgrade = 0;  
            } else {
                ESP_LOGI(TAG, "Ready to upgrade prompt.");
            }
            vQueueDelete(upgrade_queue);

            lvgl_port_lock(0);
            if (lv_obj_is_valid(display->main_btn_confirm_upgrade_)) {
                lv_obj_delete(display->main_btn_confirm_upgrade_);
                display->main_btn_confirm_upgrade_ = nullptr;
            }
            if (lv_obj_is_valid(display->main_btn_skip_upgrade_)) {
                lv_obj_delete(display->main_btn_skip_upgrade_);
                display->main_btn_skip_upgrade_ = nullptr;
            }
            lv_obj_clear_flag(display->content_, LV_OBJ_FLAG_HIDDEN);  
            lvgl_port_unlock();
            
            if (upgrade == 1) {  
                auto edp_display = static_cast<EpdDisplay*>(display);   
                edp_display->SetScrMainGestureEvent(false);

                auto& board = Board::GetInstance();
                lvgl_port_lock(0);
                board.ClearDisplay(0x00);
                display->LoadScreenByName("main");
                lv_refr_now(NULL);    
                // board.UpdateDisplay();
                lvgl_port_unlock();

                Alert(Lang::Strings::OTA_UPGRADE, Lang::Strings::UPGRADING, "happy", Lang::Sounds::P3_UPGRADE);
                vTaskDelay(pdMS_TO_TICKS(3000));

                SetDeviceState(kDeviceStateUpgrading);
                
                display->SetIcon(FONT_AWESOME_DOWNLOAD);
                std::string message = std::string(Lang::Strings::NEW_VERSION) + ota_.GetFirmwareVersion();
                display->SetChatMessage("system", message.c_str());

                board.SetPowerSaveMode(false);
                wake_word_->StopDetection();
                // 预先关闭音频输出，避免升级过程有音频操作
                auto codec = board.GetAudioCodec();
                codec->EnableInput(false);
                codec->EnableOutput(false);
                {
                    std::lock_guard<std::mutex> lock(mutex_);
                    audio_decode_queue_.clear();
                }
                background_task_->WaitForCompletion();
                delete background_task_;
                background_task_ = nullptr;
                vTaskDelay(pdMS_TO_TICKS(1000));

                /* 执行 OTA，带超时自动重启 */
                TimerHandle_t ota_timeout_timer = xTimerCreate(
                    "ota_timeout",
                    pdMS_TO_TICKS(10*1000), 
                    pdFALSE,
                    display, 
                    [](TimerHandle_t xTimer) {
                        auto display = static_cast<Display*>(pvTimerGetTimerID(xTimer));
                        char buffer[64];
                        snprintf(buffer, sizeof(buffer), "OTA失败，即将重启！");
                        display->SetChatMessage("system", buffer);
                        vTaskDelay(pdMS_TO_TICKS(2000));
                        esp_restart();
                    }
                );
                xTimerStart(ota_timeout_timer, 0);

                ota_.StartUpgrade([display, ota_timeout_timer](int progress, size_t speed) {
                    if (ota_timeout_timer != nullptr) {
                        xTimerReset(ota_timeout_timer, 0);
                    }
                    char buffer[64] = {0};
                    snprintf(buffer, sizeof(buffer), "%d%% %uKB/s", progress, speed / 1024 / 3); // TODO: 
                    display->SetChatMessage("system", buffer);
                });

                // ota_.StartUpgrade([display](int progress, size_t speed) {
                //     char buffer[64];
                //     snprintf(buffer, sizeof(buffer), "%d%% %uKB/s", progress, speed / 1024);
                //     display->SetChatMessage("system", buffer);
                // });

                // If upgrade success, the device will reboot and never reach here
                display->SetStatus(Lang::Strings::UPGRADE_FAILED);
                ESP_LOGI(TAG, "Firmware upgrade failed...");
                vTaskDelay(pdMS_TO_TICKS(3000));
                Reboot();
                return;
            } 
>>>>>>> fix-pdm-record
        }

        // No new version, mark the current version as valid
        ota.MarkCurrentVersionValid();
        if (!ota.HasActivationCode() && !ota.HasActivationChallenge()) {
            xEventGroupSetBits(event_group_, MAIN_EVENT_CHECK_NEW_VERSION_DONE);
            // Exit the loop if done checking new version
            break;
        }

        display->SetStatus(Lang::Strings::ACTIVATION);
        // Activation code is shown to the user and waiting for the user to input
        if (ota.HasActivationCode()) {
            ShowActivationCode(ota.GetActivationCode(), ota.GetActivationMessage());
        }

        // This will block the loop until the activation is done or timeout
        for (int i = 0; i < 10; ++i) {
            ESP_LOGI(TAG, "Activating... %d/%d", i + 1, 10);
            esp_err_t err = ota.Activate();
            if (err == ESP_OK) {
                xEventGroupSetBits(event_group_, MAIN_EVENT_CHECK_NEW_VERSION_DONE);
                break;
            } else if (err == ESP_ERR_TIMEOUT) {
                vTaskDelay(pdMS_TO_TICKS(3000));
            } else {
                vTaskDelay(pdMS_TO_TICKS(10000));
            }
            if (device_state_ == kDeviceStateIdle) {
                break;
            }
        }
    }
}

void Application::ShowActivationCode(const std::string& code, const std::string& message) {
    struct digit_sound {
        char digit;
        const std::string_view& sound;
    };
    static const std::array<digit_sound, 10> digit_sounds{{
        digit_sound{'0', Lang::Sounds::P3_0},
        digit_sound{'1', Lang::Sounds::P3_1}, 
        digit_sound{'2', Lang::Sounds::P3_2},
        digit_sound{'3', Lang::Sounds::P3_3},
        digit_sound{'4', Lang::Sounds::P3_4},
        digit_sound{'5', Lang::Sounds::P3_5},
        digit_sound{'6', Lang::Sounds::P3_6},
        digit_sound{'7', Lang::Sounds::P3_7},
        digit_sound{'8', Lang::Sounds::P3_8},
        digit_sound{'9', Lang::Sounds::P3_9}
    }};

    // This sentence uses 9KB of SRAM, so we need to wait for it to finish
    Alert(Lang::Strings::ACTIVATION, message.c_str(), "happy", Lang::Sounds::P3_ACTIVATION);

    for (const auto& digit : code) {
        auto it = std::find_if(digit_sounds.begin(), digit_sounds.end(),
            [digit](const digit_sound& ds) { return ds.digit == digit; });
        if (it != digit_sounds.end()) {
            audio_service_.PlaySound(it->sound);
        }
    }
}

void Application::Alert(const char* status, const char* message, const char* emotion, const std::string_view& sound) {
    ESP_LOGW(TAG, "Alert %s: %s [%s]", status, message, emotion);
    auto display = Board::GetInstance().GetDisplay();
    display->SetStatus(status);
    display->SetEmotion(emotion);
    display->SetChatMessage("system", message);
    if (!sound.empty()) {
        audio_service_.PlaySound(sound);
    }
}

void Application::DismissAlert() {
    if (device_state_ == kDeviceStateIdle) {
        auto display = Board::GetInstance().GetDisplay();
        display->SetStatus(Lang::Strings::STANDBY);
        display->SetEmotion("neutral");
        display->SetChatMessage("system", "");
    }
}

void Application::ToggleChatState() {
    // TODO:  
    aborted_ = false; 

    if (device_state_ == kDeviceStateActivating) {
        SetDeviceState(kDeviceStateIdle);
        return;
    } else if (device_state_ == kDeviceStateWifiConfiguring) {
        audio_service_.EnableAudioTesting(true);
        SetDeviceState(kDeviceStateAudioTesting);
        return;
    } else if (device_state_ == kDeviceStateAudioTesting) {
        audio_service_.EnableAudioTesting(false);
        SetDeviceState(kDeviceStateWifiConfiguring);
        return;
    }

    if (!protocol_) {
        ESP_LOGE(TAG, "Protocol not initialized");
        return;
    }

    if (device_state_ == kDeviceStateIdle) {
        Schedule([this]() {
            if (!protocol_->IsAudioChannelOpened()) {
                SetDeviceState(kDeviceStateConnecting);
                if (!protocol_->OpenAudioChannel()) {
                    return;
                }
            }

            SetListeningMode(aec_mode_ == kAecOff ? kListeningModeAutoStop : kListeningModeRealtime);
        });
    } else if (device_state_ == kDeviceStateSpeaking) {
        Schedule([this]() {
            AbortSpeaking(kAbortReasonNone);
            FullRefresh();
        });
    } else if (device_state_ == kDeviceStateListening) {
        Schedule([this]() {
            protocol_->CloseAudioChannel();
        });
    }
}

void Application::StartListening() {
    if (device_state_ == kDeviceStateActivating) {
        SetDeviceState(kDeviceStateIdle);
        return;
    } else if (device_state_ == kDeviceStateWifiConfiguring) {
        audio_service_.EnableAudioTesting(true);
        SetDeviceState(kDeviceStateAudioTesting);
        return;
    }

    if (!protocol_) {
        ESP_LOGE(TAG, "Protocol not initialized");
        return;
    }
    
    if (device_state_ == kDeviceStateIdle) {
        Schedule([this]() {
            if (!protocol_->IsAudioChannelOpened()) {
                SetDeviceState(kDeviceStateConnecting);
                if (!protocol_->OpenAudioChannel()) {
                    return;
                }
            }
            SetListeningMode(kListeningModeManualStop);
        });
    } else if (device_state_ == kDeviceStateSpeaking) {
        Schedule([this]() {
            AbortSpeaking(kAbortReasonNone);
            SetListeningMode(kListeningModeManualStop);
        });
    }
}

void Application::StopListening() {
    if (device_state_ == kDeviceStateAudioTesting) {
        audio_service_.EnableAudioTesting(false);
        SetDeviceState(kDeviceStateWifiConfiguring);
        return;
    }

    const std::array<int, 3> valid_states = {
        kDeviceStateListening,
        kDeviceStateSpeaking,
        kDeviceStateIdle,
    };
    // If not valid, do nothing
    if (std::find(valid_states.begin(), valid_states.end(), device_state_) == valid_states.end()) {
        return;
    }

    Schedule([this]() {
        if (device_state_ == kDeviceStateListening) {
            protocol_->SendStopListening();
            SetDeviceState(kDeviceStateIdle);
        }
    });
}

void Application::Start() {
    auto& board = Board::GetInstance();
    SetDeviceState(kDeviceStateStarting);

    /* Setup the display */
    auto display = board.GetDisplay();

    /* Setup the audio service */
    auto codec = board.GetAudioCodec();
    audio_service_.Initialize(codec);
    audio_service_.Start();

<<<<<<< HEAD
    AudioServiceCallbacks callbacks;
    callbacks.on_send_queue_available = [this]() {
        xEventGroupSetBits(event_group_, MAIN_EVENT_SEND_AUDIO);
    };
    callbacks.on_wake_word_detected = [this](const std::string& wake_word) {
        xEventGroupSetBits(event_group_, MAIN_EVENT_WAKE_WORD_DETECTED);
    };
    callbacks.on_vad_change = [this](bool speaking) {
        xEventGroupSetBits(event_group_, MAIN_EVENT_VAD_CHANGE);
    };
    audio_service_.SetCallbacks(callbacks);
=======
    if (codec->input_sample_rate() != 16000) {
        input_resampler_.Configure(codec->input_sample_rate(), 16000);
        reference_resampler_.Configure(codec->input_sample_rate(), 16000);
    }
    codec->Start();

    // 设置默认音量，播放启动音 
    int volume = board.LoadVolumeFormNvs();
    codec->SetOutputVolume(volume);
    ResetDecoder();
    PlaySound(Lang::Sounds::P3_STARTUP);

#if CONFIG_USE_AUDIO_PROCESSOR
    xTaskCreatePinnedToCore([](void* arg) {
        Application* app = (Application*)arg;
        app->AudioLoop();
        vTaskDelete(NULL);
    }, "audio_loop", 4096 * 2, this, 8, &audio_loop_task_handle_, 1);
#else
    xTaskCreate([](void* arg) {
        Application* app = (Application*)arg;
        app->AudioLoop();
        vTaskDelete(NULL);
    }, "audio_loop", 4096 * 2, this, 8, &audio_loop_task_handle_);
#endif
>>>>>>> fix-pdm-record

    /* Start the clock timer to update the status bar */
    esp_timer_start_periodic(clock_timer_handle_, 1000000); // 1秒

    while (lv_scr_act() != display->scr_main_) {
        vTaskDelay(pdMS_TO_TICKS(50)); 
    }

    /* Wait for the network to be ready */
    board.StartNetwork();

    // Check for new firmware version or get the MQTT broker address
    Ota ota;
    CheckNewVersion(ota);

    // Update the status bar immediately to show the network state
    display->UpdateStatusBar(true);

    // Initialize the protocol
    display->SetStatus(Lang::Strings::LOADING_PROTOCOL);

    // Add MCP common tools before initializing the protocol
    McpServer::GetInstance().AddCommonTools();

    if (ota.HasMqttConfig()) {
        protocol_ = std::make_unique<MqttProtocol>();
    } else if (ota.HasWebsocketConfig()) {
        protocol_ = std::make_unique<WebsocketProtocol>();
    } else {
        ESP_LOGW(TAG, "No protocol specified in the OTA config, using MQTT");
        protocol_ = std::make_unique<MqttProtocol>();
    }

    protocol_->OnNetworkError([this](const std::string& message) {
        last_error_message_ = message;
        xEventGroupSetBits(event_group_, MAIN_EVENT_ERROR);
    });
    protocol_->OnIncomingAudio([this](std::unique_ptr<AudioStreamPacket> packet) {
        if (device_state_ == kDeviceStateSpeaking) {
            audio_service_.PushPacketToDecodeQueue(std::move(packet));
        }
    });
    protocol_->OnAudioChannelOpened([this, codec, &board]() {
        board.SetPowerSaveMode(false);
        if (protocol_->server_sample_rate() != codec->output_sample_rate()) {
            ESP_LOGW(TAG, "Server sample rate %d does not match device output sample rate %d, resampling may cause distortion",
                protocol_->server_sample_rate(), codec->output_sample_rate());
        }
    });
    protocol_->OnAudioChannelClosed([this, &board]() {
        board.SetPowerSaveMode(true);
        Schedule([this]() {
            auto display = Board::GetInstance().GetDisplay();
            display->SetChatMessage("system", "");
            SetDeviceState(kDeviceStateIdle);
        });
    });
    protocol_->OnIncomingJson([this, display](const cJSON* root) {
        // Parse JSON data
        auto type = cJSON_GetObjectItem(root, "type");
        if (strcmp(type->valuestring, "tts") == 0) {
            auto state = cJSON_GetObjectItem(root, "state");
            if (strcmp(state->valuestring, "start") == 0) {
                Schedule([this]() {
                    aborted_ = false;
                    if (device_state_ == kDeviceStateIdle || device_state_ == kDeviceStateListening) {
                        SetDeviceState(kDeviceStateSpeaking);
                    }
                });
            } else if (strcmp(state->valuestring, "stop") == 0) {
                Schedule([this]() {
                    if (device_state_ == kDeviceStateSpeaking) {
                        if (listening_mode_ == kListeningModeManualStop) {
                            SetDeviceState(kDeviceStateIdle);
                        } else {
                            SetDeviceState(kDeviceStateListening);
                        }
                    }
                });
            } else if (strcmp(state->valuestring, "sentence_start") == 0) {
                auto text = cJSON_GetObjectItem(root, "text");
                if (cJSON_IsString(text)) {
                    ESP_LOGI(TAG, "<< %s", text->valuestring);
                    Schedule([this, display, message = std::string(text->valuestring)]() {
                        display->SetChatMessage("assistant", message.c_str());
                    });
                }
            }
        } else if (strcmp(type->valuestring, "stt") == 0) {
            auto text = cJSON_GetObjectItem(root, "text");
            if (cJSON_IsString(text)) {
                ESP_LOGI(TAG, ">> %s", text->valuestring);
                Schedule([this, display, message = std::string(text->valuestring)]() {
                    display->SetChatMessage("user", message.c_str());
                });
            }
        } else if (strcmp(type->valuestring, "llm") == 0) {
            auto emotion = cJSON_GetObjectItem(root, "emotion");
            if (cJSON_IsString(emotion)) {
                Schedule([this, display, emotion_str = std::string(emotion->valuestring)]() {
                    display->SetEmotion(emotion_str.c_str());
                });
            }
        } else if (strcmp(type->valuestring, "mcp") == 0) {
            auto payload = cJSON_GetObjectItem(root, "payload");
            if (cJSON_IsObject(payload)) {
                McpServer::GetInstance().ParseMessage(payload);
            }
        } else if (strcmp(type->valuestring, "system") == 0) {
            auto command = cJSON_GetObjectItem(root, "command");
            if (cJSON_IsString(command)) {
                ESP_LOGI(TAG, "System command: %s", command->valuestring);
                if (strcmp(command->valuestring, "reboot") == 0) {
                    // Do a reboot if user requests a OTA update
                    Schedule([this]() {
                        Reboot();
                    });
                } else {
                    ESP_LOGW(TAG, "Unknown system command: %s", command->valuestring);
                }
            }
        } else if (strcmp(type->valuestring, "alert") == 0) {
            auto status = cJSON_GetObjectItem(root, "status");
            auto message = cJSON_GetObjectItem(root, "message");
            auto emotion = cJSON_GetObjectItem(root, "emotion");
            if (cJSON_IsString(status) && cJSON_IsString(message) && cJSON_IsString(emotion)) {
                Alert(status->valuestring, message->valuestring, emotion->valuestring, Lang::Sounds::P3_VIBRATION);
            } else {
                ESP_LOGW(TAG, "Alert command requires status, message and emotion");
            }
#if CONFIG_RECEIVE_CUSTOM_MESSAGE
        } else if (strcmp(type->valuestring, "custom") == 0) {
            auto payload = cJSON_GetObjectItem(root, "payload");
            ESP_LOGI(TAG, "Received custom message: %s", cJSON_PrintUnformatted(root));
            if (cJSON_IsObject(payload)) {
                Schedule([this, display, payload_str = std::string(cJSON_PrintUnformatted(payload))]() {
                    display->SetChatMessage("system", payload_str.c_str());
                });
            } else {
                ESP_LOGW(TAG, "Invalid custom message format: missing payload");
            }
#endif
        } else {
            ESP_LOGW(TAG, "Unknown message type: %s", type->valuestring);
        }
    });
    bool protocol_started = protocol_->Start();

    SetDeviceState(kDeviceStateIdle);

    has_server_time_ = ota.HasServerTime();
    if (protocol_started) {
        std::string message = std::string(Lang::Strings::VERSION) + ota.GetCurrentVersion();
        display->ShowNotification(message.c_str());
        display->SetChatMessage("system", "");
        // Play the success sound to indicate the device is ready
<<<<<<< HEAD
        audio_service_.PlaySound(Lang::Sounds::P3_SUCCESS);
=======
        // ResetDecoder();
        // PlaySound(Lang::Sounds::P3_WELCOME);
        Schedule([] {
            auto& app = Application::GetInstance();
            app.ResetDecoder();
            app.PlaySound(Lang::Sounds::P3_WELCOME);
        });
>>>>>>> fix-pdm-record
    }

    //auto& board = Board::GetInstance();

    // lvgl_port_lock(0);
    // board.ClearDisplay(0x00);
    // //lv_obj_clear_flag(display->main_btn_chat_, LV_OBJ_FLAG_HIDDEN);
    // lv_refr_now(NULL);    
    // board.UpdateDisplay();
    // lvgl_port_unlock();

    FullRefresh();

    // Print heap stats
    SystemInfo::PrintHeapStats();

    // Enter the main event loop
    MainEventLoop();
}

void Application::OnClockTimer() {
    clock_ticks_++;

    auto display = Board::GetInstance().GetDisplay();
    display->UpdateStatusBar();

    // Print the debug info every 10 seconds
    if (clock_ticks_ % 10 == 0) {
        // SystemInfo::PrintTaskCpuUsage(pdMS_TO_TICKS(1000));
        // SystemInfo::PrintTaskList();
        SystemInfo::PrintHeapStats();
    }
}

// Add a async task to MainLoop
void Application::Schedule(std::function<void()> callback) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        main_tasks_.push_back(std::move(callback));
    }
    xEventGroupSetBits(event_group_, MAIN_EVENT_SCHEDULE);
}

// The Main Event Loop controls the chat state and websocket connection
// If other tasks need to access the websocket or chat state,
// they should use Schedule to call this function
void Application::MainEventLoop() {
    // Raise the priority of the main event loop to avoid being interrupted by background tasks (which has priority 2)
    vTaskPrioritySet(NULL, 3);

    while (true) {
        auto bits = xEventGroupWaitBits(event_group_, MAIN_EVENT_SCHEDULE |
            MAIN_EVENT_SEND_AUDIO |
            MAIN_EVENT_WAKE_WORD_DETECTED |
            MAIN_EVENT_VAD_CHANGE |
            MAIN_EVENT_ERROR, pdTRUE, pdFALSE, portMAX_DELAY);
        if (bits & MAIN_EVENT_ERROR) {
            SetDeviceState(kDeviceStateIdle);
            Alert(Lang::Strings::ERROR, last_error_message_.c_str(), "sad", Lang::Sounds::P3_EXCLAMATION);
        }

        if (bits & MAIN_EVENT_SEND_AUDIO) {
            while (auto packet = audio_service_.PopPacketFromSendQueue()) {
                if (!protocol_->SendAudio(std::move(packet))) {
                    break;
                }
            }
        }

        if (bits & MAIN_EVENT_WAKE_WORD_DETECTED) {
            OnWakeWordDetected();
        }

        if (bits & MAIN_EVENT_VAD_CHANGE) {
            if (device_state_ == kDeviceStateListening) {
                auto led = Board::GetInstance().GetLed();
                led->OnStateChanged();
            }
        }

        if (bits & MAIN_EVENT_SCHEDULE) {
            std::unique_lock<std::mutex> lock(mutex_);
            auto tasks = std::move(main_tasks_);
            lock.unlock();
            for (auto& task : tasks) {
                task();
            }
        }
    }
}

void Application::OnWakeWordDetected() {
    if (!protocol_) {
        return;
    }

    if (device_state_ == kDeviceStateIdle) {
        audio_service_.EncodeWakeWord();

        if (!protocol_->IsAudioChannelOpened()) {
            SetDeviceState(kDeviceStateConnecting);
            if (!protocol_->OpenAudioChannel()) {
                audio_service_.EnableWakeWordDetection(true);
                return;
            }
        }

        auto wake_word = audio_service_.GetLastWakeWord();
        ESP_LOGI(TAG, "Wake word detected: %s", wake_word.c_str());
#if CONFIG_USE_AFE_WAKE_WORD || CONFIG_USE_CUSTOM_WAKE_WORD
        // Encode and send the wake word data to the server
        while (auto packet = audio_service_.PopWakeWordPacket()) {
            protocol_->SendAudio(std::move(packet));
        }
        // Set the chat state to wake word detected
        protocol_->SendWakeWordDetected(wake_word);
        SetListeningMode(aec_mode_ == kAecOff ? kListeningModeAutoStop : kListeningModeRealtime);
#else
        SetListeningMode(aec_mode_ == kAecOff ? kListeningModeAutoStop : kListeningModeRealtime);
        // Play the pop up sound to indicate the wake word is detected
        audio_service_.PlaySound(Lang::Sounds::P3_POPUP);
#endif
    } else if (device_state_ == kDeviceStateSpeaking) {
        AbortSpeaking(kAbortReasonWakeWordDetected);
    } else if (device_state_ == kDeviceStateActivating) {
        SetDeviceState(kDeviceStateIdle);
    }
}

void Application::AbortSpeaking(AbortReason reason) {
    ESP_LOGI(TAG, "Abort speaking");
   // aborted_ = true; //
    protocol_->SendAbortSpeaking(reason);
}

void Application::SetListeningMode(ListeningMode mode) {
    listening_mode_ = mode;
    SetDeviceState(kDeviceStateListening);
}

void Application::SetDeviceState(DeviceState state) {
    static int cnt;
    static int64_t listen_start_time = 0; // 单次监听开始时间
    static int64_t total_listen_time = 0; // 累计 Listening 时长（单位：us）

    printf("\ndevice state: %d\n", device_state_);

    device_last_state_ = device_state_;
    if (device_state_ == state) {
        return;
    }
    
    clock_ticks_ = 0;
    auto previous_state = device_state_;
    device_state_ = state;
    ESP_LOGI(TAG, "STATE: %s", STATE_STRINGS[device_state_]);

    // Send the state change event
    DeviceStateEventManager::GetInstance().PostStateChangeEvent(previous_state, state);

    auto& board = Board::GetInstance();
    auto display = board.GetDisplay();
    auto led = board.GetLed();
    led->OnStateChanged();
    switch (state) {
        case kDeviceStateUnknown:
        case kDeviceStateIdle:
            audio_processor_->Stop();
            display->SetStatus(Lang::Strings::STANDBY);
            display->SetEmotion("neutral");
<<<<<<< HEAD
            audio_service_.EnableVoiceProcessing(false);
            audio_service_.EnableWakeWordDetection(true);
=======
 
            lvgl_port_lock(50);
            lv_obj_align(display->main_btn_chat_, LV_ALIGN_TOP_MID, 0, 215);
            lv_label_set_text(display->main_btn_chat_label_, "对话");
            lv_obj_clear_flag(display->main_btn_chat_, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(display->main_btn_pause_chat_, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(display->content_, LV_OBJ_FLAG_HIDDEN);
            lvgl_port_unlock();

            // 如果上一个状态是 Listening，更新累计时长
            if (previous_state == kDeviceStateListening && listen_start_time != 0) {
                int64_t duration = esp_timer_get_time() - listen_start_time;
                total_listen_time += duration;
                listen_start_time = 0;
            }
            // 超过 20 秒就全刷
            if (cnt++ != 0 && total_listen_time > 20 * 1000000) {
                FullRefresh();
                total_listen_time = 0;  // 重置累计时间
            }
            wake_word_->StartDetection();
>>>>>>> fix-pdm-record
            break;
        case kDeviceStateConnecting:
            display->SetStatus(Lang::Strings::CONNECTING);
            display->SetEmotion("neutral");
            display->SetChatMessage("system", "");
<<<<<<< HEAD
=======
            display->SetBtnLabel("");
            timestamp_queue_.clear();
>>>>>>> fix-pdm-record
            break;
        case kDeviceStateListening:
            display->SetStatus(Lang::Strings::LISTENING);
            display->SetEmotion("neutral");

<<<<<<< HEAD
=======
            lvgl_port_lock(0);
            lv_obj_align(display->main_btn_chat_, LV_ALIGN_TOP_MID, 0, 215);
            lv_label_set_text(display->main_btn_chat_label_, "退出");
            lv_obj_clear_flag(display->main_btn_chat_, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(display->main_btn_pause_chat_, LV_OBJ_FLAG_HIDDEN);
            lvgl_port_unlock();

            // 仅首次进入 Listening 时记录开始时间
            if (previous_state != kDeviceStateListening && listen_start_time == 0) {
                listen_start_time = esp_timer_get_time();
            }
            board.SetIndicator(0, 50, 0);
            // Update the IoT states before sending the start listening command
#if CONFIG_IOT_PROTOCOL_XIAOZHI
            UpdateIotStates();
#endif
>>>>>>> fix-pdm-record
            // Make sure the audio processor is running
            if (!audio_service_.IsAudioProcessorRunning()) {
                // Send the start listening command
                protocol_->SendStartListening(listening_mode_);
                audio_service_.EnableVoiceProcessing(true);
                audio_service_.EnableWakeWordDetection(false);
            }
            break;
        case kDeviceStateSpeaking:
            display->SetStatus(Lang::Strings::SPEAKING);
     
            lvgl_port_lock(50);
            lv_label_set_text(display->main_btn_pause_chat_label_, "暂停");
            lv_obj_clear_flag(display->main_btn_pause_chat_, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(display->main_btn_chat_, LV_OBJ_FLAG_HIDDEN);
            lvgl_port_unlock();

            if (listening_mode_ != kListeningModeRealtime) {
                audio_service_.EnableVoiceProcessing(false);
                // Only AFE wake word can be detected in speaking mode
#if CONFIG_USE_AFE_WAKE_WORD
                audio_service_.EnableWakeWordDetection(true);
#else
                audio_service_.EnableWakeWordDetection(false);
#endif
            }
            audio_service_.ResetDecoder();
            break;
        case kDeviceStateSetting: // 进入设置 
            audio_processor_->Stop();
            wake_word_->StopDetection();
            break;
        case kDeviceStateSleep: // 进入休眠 
            printf("\n");
            ResetDecoder();
            audio_processor_->Stop();
            wake_word_->StopDetection();
        break;
        default:
            // Do nothing
            break;
    }
}

void Application::Reboot() {
    ESP_LOGI(TAG, "Rebooting...");
    esp_restart();
}

void Application::WakeWordInvoke(const std::string& wake_word) {
    if (device_state_ == kDeviceStateIdle) {
        ToggleChatState();
        Schedule([this, wake_word]() {
            if (protocol_) {
                protocol_->SendWakeWordDetected(wake_word); 
            }
        }); 
    } else if (device_state_ == kDeviceStateSpeaking) {
        Schedule([this]() {
            AbortSpeaking(kAbortReasonNone);
        });
    } else if (device_state_ == kDeviceStateListening) {   
        Schedule([this]() {
            if (protocol_) {
                protocol_->CloseAudioChannel();
            }
        });
    }
}

bool Application::CanEnterSleepMode() {
    // if (device_state_ != kDeviceStateIdle) {
    //     return false;
    // }


    if (device_state_ == kDeviceStateListening || device_state_ == kDeviceStateSpeaking) {
        return false;
    }

    if (protocol_ && protocol_->IsAudioChannelOpened()) {
        return false;
    }

<<<<<<< HEAD
    if (!audio_service_.IsIdle()) {
        return false;
    }
=======
    // TODO: 触摸操作时不进入休眠 
    // // 判断是否刚刚触摸过（比如 5 秒以内）
    // const int64_t now = esp_timer_get_time();  // 单位: 微秒
    // const int64_t TOUCH_TIMEOUT_US = 5 * 1000000;  // 5 秒
    // if ((now - last_touch_time_us) < TOUCH_TIMEOUT_US) {
    //     return false;
    // }
>>>>>>> fix-pdm-record

    // Now it is safe to enter sleep mode
    return true;
}

void Application::SendMcpMessage(const std::string& payload) {
    Schedule([this, payload]() {
        if (protocol_) {
            protocol_->SendMcpMessage(payload);
        }
    });
}

void Application::SetAecMode(AecMode mode) {
    aec_mode_ = mode;
    Schedule([this]() {
        auto& board = Board::GetInstance();
        auto display = board.GetDisplay();
        switch (aec_mode_) {
        case kAecOff:
            audio_service_.EnableDeviceAec(false);
            display->ShowNotification(Lang::Strings::RTC_MODE_OFF);
            break;
        case kAecOnServerSide:
            audio_service_.EnableDeviceAec(false);
            display->ShowNotification(Lang::Strings::RTC_MODE_ON);
            break;
        case kAecOnDeviceSide:
            audio_service_.EnableDeviceAec(true);
            display->ShowNotification(Lang::Strings::RTC_MODE_ON);
            break;
        }

        // If the AEC mode is changed, close the audio channel
        if (protocol_ && protocol_->IsAudioChannelOpened()) {
            protocol_->CloseAudioChannel();
        }
    });
}

<<<<<<< HEAD
void Application::PlaySound(const std::string_view& sound) {
    audio_service_.PlaySound(sound);
}
=======

// Add for XiaoZhi Card

static void sleep_task(void *param) {
    //auto *args = static_cast<SoundPlayParams *>(param);

    auto& board = Board::GetInstance();
    auto display = board.GetDisplay();
    auto codec = board.GetAudioCodec();
    codec->EnableInput(false);
    codec->EnableOutput(false);
    // {
    //     std::lock_guard<std::mutex> lock(mutex_);
    //     audio_decode_queue_.clear();
    // }
    lvgl_port_lock(0); 
    display->lv_scr_last_ = lv_screen_active();
    display->LoadScreenByName("sleep");
    // board.UpdateDisplay();
    lv_refr_now(NULL);  
    lvgl_port_unlock();
    vTaskDelay(pdMS_TO_TICKS(300));
    board.Sleep();
   
    //delete args;
    vTaskDelete(nullptr);
}

void Application::EnterSleepMode(uint8_t mode) {
    ESP_LOGI(TAG, "app: EnterSleepMode");

    if (device_state_  != kDeviceStateIdle) {
        printf("device_state_  != kDeviceStateIdle\n");

        wake_word_->StopDetection();

        xTaskCreate(sleep_task, "sleep_task", 4096, nullptr, 3, nullptr);
        // auto& board = Board::GetInstance();
        // auto display = board.GetDisplay();
        // auto codec = board.GetAudioCodec();
        // codec->EnableInput(false);
        // codec->EnableOutput(false);
        // {
        //     std::lock_guard<std::mutex> lock(mutex_);
        //     audio_decode_queue_.clear();
        // }
        // lvgl_port_lock(0); 
        // display->lv_scr_last_ = lv_screen_active();
        // display->LoadScreenByName("sleep");
        // board.ClearDisplay(0x00); 
        // board.SetRefreshCode(0xF7);
        // lv_refr_now(NULL);  
        // lvgl_port_unlock();
        // vTaskDelay(pdMS_TO_TICKS(300));
        // board.EnterSleepMode(0);
    } else {
        Schedule([this]() {
            auto& board = Board::GetInstance();
            auto display = board.GetDisplay();
            wake_word_->StopDetection();
            auto codec = board.GetAudioCodec();
            codec->EnableInput(false);
            codec->EnableOutput(false);
            {
                std::lock_guard<std::mutex> lock(mutex_);
                audio_decode_queue_.clear();
            }
            display->LoadScreenByName("sleep");
            vTaskDelay(pdMS_TO_TICKS(300));
            board.Sleep();
        });
    }
}

void Application::ExitSleepMode() {
    ESP_LOGI(TAG, "app: ExitSleepMode");

    // if (device_state_ == kDeviceStateIdle) {
    //     auto& board = Board::GetInstance();
    //     auto display = board.GetDisplay();
    //     board.ExitSleepMode();

    //     lvgl_port_lock(0);
    //     display->LoadScreenByName("main");
    //     board.UpdateDisplay();
    //     // board.ClearDisplay(0x00); 
    //     // board.SetRefreshCode(0xF7);
    //     lv_refr_now(NULL);  
    //     lvgl_port_unlock();

    //     auto codec = board.GetAudioCodec();
    //     codec->EnableInput(true);
    //     ResetDecoder();
    //     PlaySound(Lang::Sounds::P3_SUCCESS);
    //     wake_word_->StartDetection();
    //     SetDeviceState(kDeviceStateIdle);
    // } else {
    //     auto& board = Board::GetInstance();
    //     auto display = board.GetDisplay();
    //     board.ExitSleepMode();

    //     lvgl_port_lock(0);
    //     if (display->lv_scr_last_) {
    //         lv_scr_load(display->lv_scr_last_);
    //     }
    //     //display->LoadScreenByName("main");
    //     // board.ClearDisplay(0x00); 
    //     // board.SetRefreshCode(0xF7);
    //     board.UpdateDisplay();
    //     lv_refr_now(NULL);  
    //     lvgl_port_unlock();
    // }
}

void Application::Shutdown() {
    ESP_LOGI(TAG, "app: Shutdown");
 
    ResetDecoder();
    PlaySound(Lang::Sounds::P3_C2);

    auto& board = Board::GetInstance();
    board.Shutdown();  
}

void Application::FullRefresh()
{
    auto& board = Board::GetInstance();
    auto display = board.GetDisplay();
    
    lvgl_port_lock(0);
    // board.UpdateDisplay();
    lv_obj_invalidate(lv_screen_active());   
    for (int i = 0; i < 5; i++) {
        lv_refr_now(NULL);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
    lvgl_port_unlock();
}

void Application::PlayClickSound() {
    Schedule([] {
        auto& app = Application::GetInstance();
        app.ResetDecoder();
        app.PlaySound(Lang::Sounds::P3_C2);
    });
}

// void Application::InitialAutoShutdown(uint32_t auto_shutdown_time_s) 
// {
//     shutdown_timer_ = xTimerCreate("shutdown_timer",
//                                    pdMS_TO_TICKS(auto_shutdown_time_s * 1000),  
//                                    pdFALSE,
//                                    this,  
//                                    &Application::ShutdownTimerCallback); 
// }

// void Application::ShutdownTimerCallback(TimerHandle_t xTimer)
// {
//     Application* self = static_cast<Application*>(pvTimerGetTimerID(xTimer));
//     if (self) {
//         if (self->shutdown_timer_ != nullptr) {
//             xTimerStop(self->shutdown_timer_, 0);
//             xTimerDelete(self->shutdown_timer_, 0);
//             self->shutdown_timer_ = nullptr;
//         }

//         self->Schedule([self]() {
//             self->Shutdown();
//         });
//     }
// }

// void Application::ResetShutdownTimer()
// {   
//     if (shutdown_timer_ != NULL) {
//         xTimerStop(shutdown_timer_, 0);
//         xTimerStart(shutdown_timer_, 0);
//     }   
// } 
>>>>>>> fix-pdm-record
