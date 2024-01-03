              
[FRAGMENT_SOURCE]
{
    #version 330 core

    out vec3 fragColor;

    void main()
    {
        fragColor = vec3(1, 1, 0);
    }
}

[VERTEX_SOURCE]
{
    #version 330 core

    layout(location = 0) in vec3 loc_VertPos;

    uniform mat4x4 TRANSFORMATION;
    uniform mat4x4 PROJECTION;
    uniform mat4x4 VIEW;

    void main()
    {
        gl_Position = PROJECTION * VIEW * TRANSFORMATION * vec4(loc_VertPos, 1.0);
    }
}                       