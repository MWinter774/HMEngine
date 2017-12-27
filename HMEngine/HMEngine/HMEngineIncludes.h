#pragma once

#include <SDL2.0.7\SDL.h>
#undef main

#include <boost\ptr_container\ptr_vector.hpp>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\matrix_transform_2d.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <SOIL\SOIL.h>

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <exception>
#include <map>
#include <unordered_map>
#include <fstream>
#include <exception>
#include <list>
#include <memory>

#include "Window.h"
#include "GameEngine.h"
#include "HardwareInputs.h"
#include "Transform.h"
#include "Constants.h"
#include "Camera.h"
#include "Shader.h"
#include "BasicShader.h"
#include "RenderingEngine.h"
#include "GameSettings.h"
#include "GameObject.h"
#include "Component.h"
#include "Texture.h"
#include "MeshRenderer.h"