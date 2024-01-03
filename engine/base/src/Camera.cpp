#include "../Camera.hpp"

    /// CONSTRUCTEURS

Camera::Camera(const char* name) : PetraO(name)
{

    this->projection = nullptr;
    this->view = nullptr;
    
    this->projection         = new Matrix4x4f(1.f);
    this->view               = new Matrix4x4f(1.f);
    this->transform.position = Vector3f(0.f);

    this->projection->Perspective(80.f, 800.f, 600.f, 0.01f, 1000.f);
    this->view->LookAt           (  this->transform.position,
                                    Vector3f(0.f, 0.f, 0.f),
                                    Vector3f::up);

    int unifLoc = glad_glGetUniformLocation(Handle::shadersProgram[0], "PROJECTION");
    glad_glUniformMatrix4fv(unifLoc, 1, false, this->projection->Ref());
    
    unifLoc = glad_glGetUniformLocation(Handle::shadersProgram[0], "VIEW");
    glad_glUniformMatrix4fv(unifLoc, 1, false, this->view->Ref());

    glad_glUseProgram(Handle::shadersProgram[0]);
}

Camera::~Camera()
{
    delete this->projection;
    delete this->view;
}

    /// METHODES

void Camera::SetPosition(Vector3f position) noexcept
{
    this->transform.position = position;
    this->view->LookAt           (this->transform.position, 
                                    Vector3f(0.f, 0.f, 0.f), 
                                    Vector3f(0.f, 1.f, 0.f));

    int loc = glad_glGetUniformLocation(Handle::shadersProgram[0], "VIEW");
    glad_glUniformMatrix4fv(loc, 1, false, this->view->Ref());

    glad_glUseProgram(Handle::shadersProgram[0]);
}

void Camera::SetScale(Vector3f scale) noexcept
{
    this->transform.scale = scale;
    this->view->LookAt           (this->transform.position, 
                                    Vector3f(0.f, 0.f, 0.f), 
                                    Vector3f(0.f, 1.f, 0.f));

    int loc = glad_glGetUniformLocation(Handle::shadersProgram[0], "VIEW");
    glad_glUniformMatrix4fv(loc, 1, false, this->view->Ref());

    glad_glUseProgram(Handle::shadersProgram[0]);
}

void Camera::SetRotation(Vector3f rotation) noexcept
{
    this->transform.rotation = rotation;
    this->view->LookAt           (this->transform.position, 
                                    Vector3f(0.f, 0.f, 0.f), 
                                    Vector3f(0.f, 1.f, 0.f));
                                    
    int loc = glad_glGetUniformLocation(Handle::shadersProgram[0], "VIEW");
    glad_glUniformMatrix4fv(loc, 1, false, this->view->Ref());

    glad_glUseProgram(Handle::shadersProgram[0]);
}