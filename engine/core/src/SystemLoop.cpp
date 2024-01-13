#include <core/Core.hpp>

#include <core/SceneManager.hpp>
#include <base/Camera.hpp>
#include <base/GeometryTest.hpp>

#include <rendering/Texture.hpp>

#include <core/Chrono.hpp>

#include <sstream>

//  Todo:
//

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    IF_RARELY(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    Handle::window_size = {width, height};
    Camera* get = &SceneManager::GetCurrentScene()->FindACTOR<Camera>("mainCamera");
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
    glfwSetFramebufferSizeCallback(context, framebuffer_size_callback);

        // Scène principale
    Scene* mainLevel     = new Scene();
    SceneManager::SetCurrentScene(mainLevel);

        // Personnalisation   <---
    Camera        cam    = Camera("mainCamera");
    GeometryTest* player = new GeometryTest("player");
    player->WhatBuild(DRAW_CUBE);
    player->PutTexture(0);

    /*GeometryTest** tests = new GeometryTest*[50000];
    for (long i = 0; i < 50000; i++)
    {
        std::ostringstream os;
        os << i;
        std::string s = os.str();
        tests[i] = new GeometryTest(s.c_str());
        tests[i]->WhatBuild(DRAW_CUBE);
    }*/

    player->SetPosition(Vector3f(0.f, 1.f, 0.f));
    player->SetColor(Vector3f(1.f, 0.f, 1.f));


        // Charge la scène et tous ces éléments
    SceneManager::GetCurrentScene()->LoadThisScene();

    c.Stop();
    EXEC_TIME(c.GetTime())
    DEBUG_GL()
    int a = 0;
    while (!glfwWindowShouldClose(context))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

        player->SetColor(Vector3f(1.f, 0.5f, .0f));

        if (glfwGetKey(context, 'W') == GLFW_PRESS)
            player->SetPosition(Vector3f(player->transform.position.x - .001f, player->transform.position.y, player->transform.position.z));
        else if (glfwGetKey(context, 'S') == GLFW_PRESS)
            player->SetPosition(Vector3f(player->transform.position.x + .001f, player->transform.position.y, player->transform.position.z));

        if (glfwGetKey(context, 'D') == GLFW_PRESS)
            player->SetPosition(Vector3f(player->transform.position.x, player->transform.position.y, player->transform.position.z - .001f));
        else if (glfwGetKey(context, 'A') == GLFW_PRESS)
            player->SetPosition(Vector3f(player->transform.position.x, player->transform.position.y, player->transform.position.z + .001f));

        if (glfwGetKey(context, 'E') == GLFW_PRESS)
            player->SetPosition(Vector3f(player->transform.position.x, player->transform.position.y + .001f, player->transform.position.z));
        else if (glfwGetKey(context, 'Q') == GLFW_PRESS)
            player->SetPosition(Vector3f(player->transform.position.x, player->transform.position.y - .001f, player->transform.position.z));

        //if (glfwGetKey(context, 'P') == GLFW_PRESS)
            //player->Destroy();
            
        /*if (glfwGetKey(context, 'P') == GLFW_PRESS && a == 0)
        {
            a = 1;
            printf("p");
            for (long i = 0; i < 50000; i++)
            {
                SceneManager::GetCurrentScene()->DeleteObject(tests[i]->GetName());
                delete (tests[i]);
            }
        }*/

            // Dessin tous les éléments de la scène
        SceneManager::GetCurrentScene()->DrawThisScene();

        glfwSwapBuffers(context);
        glfwPollEvents();
    }

    DEBUG(CORE_LOG, "Terminate memory")
    delete mainLevel;
    glfwDestroyWindow(context);
    glfwTerminate();
    
    exit(0);
}