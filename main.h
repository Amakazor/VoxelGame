#pragma once
#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <bx/timer.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <iostream>
#include <ostream>
#include <set>

#include "camera.h"
#include "messages/message_bus.h"
#include "meshes/colored_mesh.h"
#include "shader_program.h"
#include "block/chunk.h"
#include "GLFW/glfw3native.h"
#include "handlers/input_handler.h"
#include "messages/key_message.h"
#include "messages/mouse_message.h"
#include "objects/object.h"
#include "vertices/vertex.h"
