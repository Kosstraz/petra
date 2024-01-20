#include <core/Core.hpp>

#include <core/SceneManager.hpp>
#include <base/Camera.hpp>
#include <base/Cube.hpp>

#include <rendering/Texture.hpp>

#include <core/Chrono.hpp>

#include <iostream>

//  Todo:
//
//  1 - Trouver de bonnes coordonnées (U, V) pour les textures sur un simple cube
//  2 - Faire une fonction permettant de décompresser certains types dans un .BMP
//  3 - Faire une fonction pouvant décompresser certains types dans un .PNG
//  4 - Faire des fonctions pour parser un fichier .JPG & .JPEG
//  5 - Faire une fonction pouvant décompresser certains types dans un .JPEG & .JPG
//  6 - Régler le pb de parçage du fichier to_load.json
//  B - Potentiellement mettre en commun dans une liste les uvsBufferID pour les objets identiques utilisant les mêmes (types de) textures

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
    get->Perspective(width, height);
}

int Core::Loop()
{
        // Debugage
    DEBUG(CORE_LOG, "Lancement de l'execution principale du programme.")
    INIT_RECORD
    RECORD

        // Fenêtre et paramètres OpenGL
    GLFWwindow* context = glfwGetCurrentContext();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

        // Callback
    glfwSetWindowIconifyCallback(context, window_iconify_callback);
    glfwSetKeyCallback(context, key_callback);
    glfwSetFramebufferSizeCallback(context, framebuffer_size_callback);

        // Scène principale
    Scene* mainLevel     = new Scene();
    SceneManager::SetCurrentScene(mainLevel);

        // Personnalisation   <---
    Camera       cam      = Camera("mainCamera");
    Cube         player   = Cube("player");
    const char* textures[6] = { "blocks/dirt.png", nullptr, //test/butezMoiCetteMerde.bmp
                                nullptr, nullptr,
                                nullptr, nullptr };
    player.PutMultiplesTextures(textures);

        // Charge la scène et tous ces éléments
    SceneManager::GetCurrentScene()->LoadThisScene();

    STOP_RECORD
    DEBUG_GL()
    while (!glfwWindowShouldClose(context))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

        if (glfwGetKey(context, 'W') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x - 0.001f, player.transform.position.y, player.transform.position.z));
        if (glfwGetKey(context, 'S') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x + 0.001f, player.transform.position.y, player.transform.position.z));

        if (glfwGetKey(context, 'D') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x, player.transform.position.y, player.transform.position.z + 0.001f));
        if (glfwGetKey(context, 'A') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x, player.transform.position.y, player.transform.position.z - 0.001f));

        if (glfwGetKey(context, 'E') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x, player.transform.position.y + 0.001f, player.transform.position.z));
        if (glfwGetKey(context, 'Q') == GLFW_PRESS)
            player.SetPosition(Vector3f(player.transform.position.x, player.transform.position.y - 0.001f, player.transform.position.z));

            // Dessin tous les éléments de la scène
        SceneManager::GetCurrentScene()->DrawThisScene();

        glfwSwapBuffers(context);
        glfwPollEvents();
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