#include "../Core.hpp"

#include <core/Handle.hpp>
#include <base/Camera.hpp>
#include <base/GeometryTest.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Core::Loop()
{
    DEBUG(CORE_LOG, "Lancement de l'exécution principale du programme.")
    GLFWwindow* context = glfwGetCurrentContext();
    Handle handle;
    glad_glEnable(GL_MULTISAMPLE);

        // Callback
    glfwSetKeyCallback(context, key_callback);

        // Sous-programme
    Scene* mainLevel     = new Scene();
    handle.currentScene = mainLevel  ;
    
    Camera*       cam = new Camera("mainCamera");
    GeometryTest* geo = new GeometryTest("geo" );
    geo->WhatBuild(DRAW_TRIANGLE);
    
        // Charge la scène et tous ces éléments
    handle.currentScene->LoadThisScene();

    float a = 0.0f;
    DEBUG_GL()
    while (!glfwWindowShouldClose(context))
    {
        glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        cam->SetPosition(Vector3f(1.f, a, 1.f));
        a += 0.0005f;

            // Dessin tous les éléments de la scène
        handle.currentScene->DrawThisScene();

        glfwSwapBuffers(context);
        glfwPollEvents();
    }

    DEBUG(CORE_LOG, "Suppression de la mémoire, fin de programme.")
    delete mainLevel;
}