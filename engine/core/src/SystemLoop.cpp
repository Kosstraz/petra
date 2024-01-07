#include "../Core.hpp"

#include <base/Camera.hpp>
#include <base/GeometryTest.hpp>

#include <core/Chrono.hpp>

#include <core/SceneManager.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    Handle::window_size = {width, height};

    Camera* get = SceneManager::GetCurrentScene()->FindACTOR<Camera>("mainCamera");
    get->Perspective(width, height);
}

void Core::Loop()
{
        // Debugage
    DEBUG(CORE_LOG, "Lancement de l'execution principale du programme.")
    Chrono c;
    c.Start();

        // Fenêtre et paramètres OpenGL
    GLFWwindow* context = glfwGetCurrentContext();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

        // Callback
    //glfwSetKeyCallback(context, key_callback);
    glfwSetWindowSizeCallback(context, window_size_callback);

        // Scène principale
    Scene* mainLevel     = new Scene();
    SceneManager::SetCurrentScene(mainLevel);

        // Personnalisation   <---
    Camera*       cam = new Camera("mainCamera");
    GeometryTest* geo = new GeometryTest("geo" );
    geo->WhatBuild(DRAW_CUBE);

        // Charge la scène et tous ces éléments
    SceneManager::GetCurrentScene()->LoadThisScene();





        // Modifications de la Personnalisation
    geo->SetPosition(Vector3f(0.f, 0.f, 0.f));
    geo->SetColor(Vector3f(1.f, 0.2f, 0.8f));

    cam->LookAt(geo->transform.position);

    float speed = 0.01f;
    float f = 0.f;
    float r = 0.f;

    c.Stop();
    EXEC_TIME(c.GetTime())
    DEBUG_GL()
    while (!glfwWindowShouldClose(context))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

    


        
        if (glfwGetKey(context, 'A') == GLFW_PRESS)
            r -= speed;
        if (glfwGetKey(context, 'D') == GLFW_PRESS)
            r += speed;

        if (glfwGetKey(context, 'W') == GLFW_PRESS)
            f -= speed;
        if (glfwGetKey(context, 'S') == GLFW_PRESS)
            f += speed;


        geo->SetPosition(Vector3f(r, 0.f, f));
        //geo->transform.position.Debug();



            // Dessin tous les éléments de la scène
        SceneManager::GetCurrentScene()->DrawThisScene();

        glfwSwapBuffers(context);
        glfwPollEvents();
    }

    DEBUG(CORE_LOG, "Suppression de la memoire, fin de programme.")
    delete mainLevel;
}