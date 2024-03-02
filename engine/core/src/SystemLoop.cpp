#include <core/Core.hpp>

#include <core/SceneManager.hpp>
#include <base/Camera.hpp>
#include <base/Cube.hpp>

#include <rendering/Texture.hpp>

#include <core/FPSCounter.hpp>

#include <iostream>

#define VIT_SPEED (2.0f * Time::deltaTime)

void window_iconify_callback(GLFWwindow* window, int iconified)
{
    while (iconified == 0x01)
    {   iconified = 0x00;   }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    IF_RARELY(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 0x01);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    Handle::window_size = {width, height};
    Camera* get = SceneManager::GetCurrentScene()->FindACTOR<Camera>("mainCamera");
    get->Perspective();
}

int Core::Loop()
{
        // Debugage
    DEBUG(CORE_LOG, "Lancement de l'execution principale du programme.")
    INIT_RECORD RECORD

        // Fenêtre et paramètres OpenGL
    GLFWwindow* context = glfwGetCurrentContext();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

        // Callback
    glfwSetWindowIconifyCallback    (context, window_iconify_callback);
    glfwSetKeyCallback              (context, key_callback);
    glfwSetFramebufferSizeCallback  (context, framebuffer_size_callback);
    
        // Scène principale
    Scene* mainLevel     = new Scene();
    SceneManager::SetCurrentScene(mainLevel);

        // Personnalisation   <---
    Camera       cam      = Camera("mainCamera");
    Cube         player   = Cube("player");
    /*const char* textures[6] = { "test/KARIS_carre.BMP", "test/KARIS_carre.BMP",
                                "test/KARIS_carre.BMP", "test/KARIS_carre.BMP",
                                "no_texture", "test/KARIS_carre.BMP"   };*/
    //player.PutMultiplesTextures(textures);

    /*Cube** map;
    map = PetraO::Creates<Cube>("map_", 100);
    for (uint i = 0; i < 50; i++)
        map[i]->SetPosition(Vector3f(0.f, 0.f, i * 2.0f));
    for (uint i = 50; i < 100; i++)
        map[i]->SetPosition(Vector3f(i * 2.0f, 0.f, 0.f));*/

        // Charge la scène et tous ces éléments
    SceneManager::GetCurrentScene()->LoadThisScene();

    STOP_RECORD
    DEBUG_GL()
    FPSCounter fps_counter;
    while (!glfwWindowShouldClose(context))
    {
        fps_counter.StartCount();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

        if (glfwGetKey(context, 'W') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x - VIT_SPEED, player.transform.position.y, player.transform.position.z));
        if (glfwGetKey(context, 'S') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x + VIT_SPEED, player.transform.position.y, player.transform.position.z));

        if (glfwGetKey(context, 'D') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x, player.transform.position.y, player.transform.position.z + VIT_SPEED));
        if (glfwGetKey(context, 'A') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x, player.transform.position.y, player.transform.position.z - VIT_SPEED));

        if (glfwGetKey(context, 'E') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x, player.transform.position.y + VIT_SPEED, player.transform.position.z));
        if (glfwGetKey(context, 'Q') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x, player.transform.position.y - VIT_SPEED, player.transform.position.z));

            // Dessin tous les éléments de la scène
        SceneManager::GetCurrentScene()->DrawThisScene();   //! Changer la façon dont la fonction 'DrawThisScene()' fonctionne, individuellement et spécifiquement si nécessaire
                                                            //! --> optimisation FPS | performence

        glfwSwapBuffers(context);
        glfwPollEvents();

        fps_counter.MarkCount();
    }

    RECORD

    DEBUG(CORE_LOG, "Terminate memory")
    glfwTerminate();
    DEBUG(CORE_LOG, "GLFW resources terminated")
    glfwDestroyWindow(context);
    DEBUG(CORE_LOG, "Window destroyed")
    delete (mainLevel);
    DEBUG(CORE_LOG, "Scene deleted")

    STOP_RECORD

    return (0);
}