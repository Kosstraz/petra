#include "../Core.hpp"

#define TEXTURE_PATH "resources/images/"

int Core::InitEngine()
{
    DEBUG(CORE_LOG, "Initialisation du moteur...");
    INIT_RECORD RECORD

    if (!glfwInit())
    {
        STOP_RECORD

        return (GLFWINIT_FAILED);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    //glfwWindowHint(GLFW_REFRESH_RATE, 240);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Fenêtre", 0, 0);
    if (!window)
    {
        STOP_RECORD

        glfwTerminate();
        return (WINDOWNnullptr_FAILED);
    }
    glfwMakeContextCurrent(window);
    DEBUG(CORE_LOG, "Fenetre created !");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        STOP_RECORD

        glfwDestroyWindow(window);
        glfwTerminate();
        return (GLADLOADER_FAILED);
    }

    STOP_RECORD
    return (0);
}

int Core::JSONLoader(ArrayForJSON* jsonLoaderInfos)
{   return (json_open("JSdata/to_load.json", jsonLoaderInfos)); }

int Core::CompileAllShaders(const ArrayForJSON& jsonLoaderInfos)
{
    DEBUG(SHADER_LOG, "Compilation de tous les shaders...");
    INIT_RECORD RECORD
    Handle handle;

    int log = 0;
    for (ArrayForJSON::const_iterator i = jsonLoaderInfos.begin(); i != jsonLoaderInfos.end(); ++i)
    {
        if (strcmp(i->first, "vfs_to_load") == 0)
        {
            Shader shader = Shader();
            if ((log = shader.Make(i->second)) < 0)
                return (log);

            handle.shadersProgram[0] = shader.programID;
        }
    }

    glUseProgram(Handle::shadersProgram[0]);
    
    STOP_RECORD
    return (0);
}

void Core::CreateAllImportedTextures(const ArrayForJSON& jsonLoaderInfos)
{
    DEBUG(TEXTURE_LOG, "Creation de toutes les textures...");
    INIT_RECORD RECORD

    for (ArrayForJSON::const_iterator i = jsonLoaderInfos.begin(); i != jsonLoaderInfos.end(); ++i)
        if (strcmp(i->first, "textures_to_load") == 0)
        {
            char* path = strjoin(TEXTURE_PATH, i->second, 0, 0);
            Texture texture = Texture(path);
            global_rendering::textures.emplace(i->second, texture.TakeTexture());
            free(path);
        }

    STOP_RECORD
}

void Core::FreeJSON(ArrayForJSON* jsonLoaderInfos)
{   jsonLoaderInfos->clear();   }