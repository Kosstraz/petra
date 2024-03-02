    #version 330 core

    layout (location = 0) in vec3 loc_VertPos;
    layout (location = 1) in vec2 loc_VertUVs;

    out vec2 UVs;

    uniform mat4x4 TRANSFORMATION;
    uniform mat4x4 PROJECTION;
    uniform mat4x4 VIEW;

    void main()
    {
        gl_Position = PROJECTION * VIEW * TRANSFORMATION * vec4(loc_VertPos.x, loc_VertPos.y, loc_VertPos.z * 1.85, 1.0);    //? ajustement auto pour l'axe Z
                                                                                                                            //! à regarder avec une règle (1er degrés)
        UVs = loc_VertUVs;
    }