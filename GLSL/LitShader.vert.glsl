    #version 330 core

    layout (location = 0) in vec3 loc_VertPos;
    layout (location = 1) in vec2 loc_VertUVs;

    out vec2 UVs;

    uniform mat4x4 TRANSFORMATION;
    uniform mat4x4 PROJECTION;
    uniform mat4x4 VIEW;

    void main()
    {
        gl_Position = PROJECTION * VIEW * TRANSFORMATION * vec4(loc_VertPos, 1.0);
        UVs = loc_VertUVs;
    }