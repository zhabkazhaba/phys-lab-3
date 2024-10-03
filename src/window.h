#ifndef PHYS_LAB_1_WINDOW_H
#define PHYS_LAB_1_WINDOW_H
#include "imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "GLFW/glfw3.h"
#include <vector>
#include <map>
#include <string>
#include "utilityFuncs.hpp"
#include "textManager.h"
#include "experimentList.hpp"


class Window {
private:
    enum INF_TYPE {
        INF     = 0,
        SUCCESS = 1,
        ERR     = 2
    };

    const static inline ImVec4 t_colors[] = {
            ImVec4(1.0f, 1.0f, 1.0f, 1.0f), // WHITE
            ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // GREEN
            ImVec4(1.0f, 0.0f, 0.0f, 1.0f)  // RED
    };

    Window();
    static Window* instancePtr;
    textManager managerObj = textManager("../resources/messages.json", language::ENGLISH);

    // Utility
    static bool check_mode;
    struct {
        float tmp1;
        float tmp2;
        float tmp3;
        float tmp4;
        int tmp_int;
        float tmp_conv1;
        float tmp_conv2;
        float tmp_conv3;
        float tmp_conv4;
        float tmp_conv5;
        float tmp_conv6;
        int tmp_del;
        int tmp_del_count;
        int dec_places;
        bool auto_upd;
        std::pair<int, float> tmp_pair1;
        std::pair<int, float> tmp_pair2;
        std::pair<int, double> tmp_pair3;
        experimentList::measureTuple tmp_tuple1;
        experimentList::measureTuple tmp_tuple2;
    } t;
    struct {
        std::string message;
        ImVec4 color;
    } msg;
public:
    Window(Window& o) = delete;
    ~Window();
    static Window* initializeWindow();
    int runWindow();
    void sendMessage(const std::string& message, INF_TYPE color);
};


#endif //PHYS_LAB_1_WINDOW_H
