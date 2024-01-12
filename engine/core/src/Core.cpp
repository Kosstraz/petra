#include "../Core.hpp"

int Core::InitEngine()
{
    DEBUG(CORE_LOG, "Initialisation du moteur...");
    Chrono c;
    c.Start();

    if (!glfwInit())
    {
        c.Stop();
        EXEC_TIME(c.GetTime());

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
        c.Stop();
        EXEC_TIME(c.GetTime())

        glfwTerminate();
        return (WINDOWNnullptr_FAILED);
    }
    glfwMakeContextCurrent(window);
    DEBUG(CORE_LOG, "Fenetre created !");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {   
        c.Stop();
        EXEC_TIME(c.GetTime());

        return (GLADLOADER_FAILED);
    }

    c.Stop();
    EXEC_TIME(c.GetTime());
    return (0);
}

int Core::JSONLoader(ArrayForJSON* jsonLoaderInfos)
{
    return (json_open("JSdata/to_load.json", jsonLoaderInfos));
}

void Core::CompileAllShaders(const ArrayForJSON& jsonLoaderInfos)
{
    DEBUG(SHADER_LOG, "Compilation de tous les shaders...");
    Chrono c; c.Start();
    Handle handle;

    for (ArrayForJSON::const_iterator i = jsonLoaderInfos.begin(); i != jsonLoaderInfos.end(); i++)
    {
        if (strcmp(i->first, "vfs_to_load") == 0)
        {
            Shader shader = Shader(i->second);
            shader.Guess_frag(i->second);
            shader.Guess_vert(i->second);
            shader.CompileShader();

            handle.shadersProgram[0] = shader.programID;
        }
    }

    c.Stop();
    EXEC_TIME(c.GetTime());
}

void Core::CreateAllImportedTextures(const ArrayForJSON& jsonLoaderInfos)
{
    DEBUG(TEXTURE_LOG, "Création de toutes les textures...");
    Chrono c; c.Start();

    for (ArrayForJSON::const_iterator i = jsonLoaderInfos.begin(); i != jsonLoaderInfos.end(); i++)
        if (strcmp(i->first, "textures_to_load") == 0)
        {
            Texture texture = Texture(i->second);
            
        }

    c.Stop();
    EXEC_TIME(c.GetTime());
}

void Core::FreeJSON(ArrayForJSON* jsonLoaderInfos)
{
    for (ArrayForJSON::iterator i = jsonLoaderInfos->begin(); i != jsonLoaderInfos->end(); i++)
    {
        free(i->second);
        free(i->first);
    }
    jsonLoaderInfos->clear();
    delete (jsonLoaderInfos);
}