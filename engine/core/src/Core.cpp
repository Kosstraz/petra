#include "../Core.hpp"

int Core::InitEngine()
{
    DEBUG(CORE_LOG, "Initialisation du moteur...");

    if (!glfwInit())
        return (GLFWINIT_FAILED);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", 0, 0);
    if (!window)
    {
        glfwTerminate();
        return (WINDOWNnullptr_FAILED);
    }
    glfwMakeContextCurrent(window);
    DEBUG(CORE_LOG, "Fenetre created !");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return (GLADLOADER_FAILED);

    return (0);
}

void Core::CompileAllShaders()
{
        // Init handle struct
    Handle handle;
    
        // Init all shaders availlables
    Shader* shader1 = new Shader("GLSL/LitShader.vfs.glsl");
    shader1->Set_frag_set_vert("GLSL/LitShader.frag.glsl", "GLSL/LitShader.vert.glsl");
    shader1->CompileShader();
    
        // Finish the shaders' programs attribution
    handle.shadersProgram[0] = shader1->programID;
    delete shader1;

        // Use the current shader (for the cam)
    glad_glUseProgram(handle.shadersProgram[0]);
}

void Core::Terminate()
{
    DEBUG(CORE_LOG, "Terminate memory");
    glfwDestroyWindow(glfwGetCurrentContext());
    glfwTerminate();
}