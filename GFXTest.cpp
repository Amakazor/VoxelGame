#include "main.h"

namespace
{
    void glfw_error_callback(const int error, const char *description)
    {
        std::cout << "GLFW error " << error << ": " << description << std::endl;
    }

    bool s_show_stats = false;
    bool s_show_wireframe = false;

    bool cursor_enabled = false;

    void glfw_key_callback(GLFWwindow *window, const int key, const int scancode, const int action, int mods)
    {
        message_bus::get_instance()->message(key_action, key_message(key, scancode, action));
        
        if (key == GLFW_KEY_F1 && action == GLFW_RELEASE) s_show_stats = !s_show_stats;
        if (key == GLFW_KEY_F2 && action == GLFW_RELEASE) s_show_wireframe = !s_show_wireframe;
        if (key == GLFW_KEY_F3 && action == GLFW_RELEASE)
        {
            cursor_enabled = !cursor_enabled;
            glfwSetInputMode(window, GLFW_CURSOR, cursor_enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
        }
        if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    double previous_x = 0.0;
    double previous_y = 0.0;
    bool first_mouse = true;

    void glfw_cursor_position_callback(GLFWwindow *window, const double current_x, const double current_y)
    {
        if (first_mouse)
        {
            previous_x = current_x;
            previous_y = current_y;

            first_mouse = false;
            return;
        }
        
        message_bus::get_instance()->message(mouse_movement, mouse_message(current_x, current_y, current_x - previous_x, current_y - previous_y, !cursor_enabled));

        previous_x = current_x;
        previous_y = current_y;
    }
}

int main()
{
    uint16_t width = 1600;
    uint16_t height = 900;
    
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return 1;
    GLFWwindow* window = glfwCreateWindow(1600, 900, "Hello, bgfx!", nullptr, nullptr);
    if (!window) return 1;
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported()) glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwSetKeyCallback(window, glfw_key_callback);
    glfwSetCursorPosCallback(window, glfw_cursor_position_callback);
    
    bgfx::PlatformData pd;
    pd.nwh = glfwGetWin32Window(window);

    bgfx::Init bgfx_init;
    bgfx_init.type = bgfx::RendererType::Vulkan;
    bgfx_init.resolution.width = width;
    bgfx_init.resolution.height = height;
    bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
    bgfx_init.platformData = pd;
    if (!bgfx::init(bgfx_init)) return 1;
    
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x317F43FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, width, height);

    const std::shared_ptr<input_handler> input = input_handler::get_instance();
    
    camera cam(width, height);
    cam.object_transform.move_local({0.0f, 0.0f, -5.0f});
    cam.mark_transform_matrix_dirty();

    chunk c({0, 0, 0});
    c.add_block({0, 0, 0}, false);
    c.add_block({0, 1, 0});
    c.add_block({0, 2, 0}, false);
    c.add_block({1, 0, 0}, false);
    c.add_block({2, 0, 0}, false);
    c.add_block({2, 1, 0}, false);
    c.add_block({2, 2, 0}, false);
    c.add_block({1, 2, 0});
    
    int32_t counter = 0;
    int64_t last_frame_time = bx::getHPCounter();
    float total_time = 0.0f;
    
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        const int64_t current_frame_time = bx::getHPCounter();
        const int64_t frame_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;
        const int64_t timer_frequency = bx::getHPFrequency();
        const float delta_time = static_cast<float>(frame_time) / static_cast<float>(timer_frequency);
        total_time += delta_time;

        int current_width, current_height;
        glfwGetFramebufferSize(window, &current_width, &current_height);

        if (width != current_width || height != current_height)
        {
            bgfx::reset(current_width, current_height, BGFX_RESET_VSYNC);
            bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
            width = static_cast<uint16_t>(current_width);
            height = static_cast<uint16_t>(current_height);

            cam.recalculate_projection(width, height);
        }

        input->tick();
        cam.tick(delta_time);
        
        cam.set_view();
        
        bgfx::touch(0);

        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf(2, 1, 0x0f, "Current frame: %d", counter);
        bgfx::dbgTextPrintf(2, 2, 0x0f, "Delta time: %f", delta_time);
        bgfx::dbgTextPrintf(2, 3, 0x0f, "Total time: %f", total_time);
        bgfx::dbgTextPrintf(2, 4, 0x0f, "FPS (current): %f", 1.0f / delta_time);
        bgfx::dbgTextPrintf(2, 5, 0x0f, "FPS (avg) %f", static_cast<float>(counter) / total_time);
        bgfx::dbgTextPrintf(2, 6, 0x0f, "Camera position: %f, %f, %f", cam.object_transform.position.x, cam.object_transform.position.y, cam.object_transform.position.z);
        bgfx::dbgTextPrintf(2, 7, 0x0f, "Camera rotation: %f, %f, %f", cam.object_transform.rotation.x, cam.object_transform.rotation.y, cam.object_transform.rotation.z);
        bgfx::setDebug((s_show_stats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT) | (s_show_wireframe ? BGFX_DEBUG_WIREFRAME : BGFX_DEBUG_NONE));
        
        c.draw();
        
        bgfx::frame();
        counter++;
    }
    
    bgfx::shutdown();
    glfwTerminate();
    return 0;
}