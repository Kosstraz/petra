    /*////////////*/
    /// FRAGMENT ///
    /*////////////*/

[FRAGMENT_SOURCE]
{
    #version 330 core

    out vec4 fragColor;

    uniform vec4      COLOR;

    void main()
    {
        fragColor = COLOR;
    }
}

    /*//////////*/
    /// VERTEX ///
    /*//////////*/

[VERTEX_SOURCE]
{
    #version 330 core

    layout (location = 0) in vec3 loc_VertPos;

    uniform mat4x4 TRANSFORMATION;
    uniform mat4x4 PROJECTION;
    uniform mat4x4 VIEW;

    void main()
    {
        gl_Position = PROJECTION * VIEW * TRANSFORMATION * vec4(loc_VertPos.x, loc_VertPos.y, loc_VertPos.z * 1.85, 1.0);    //? ajustement auto pour l'axe Z
                                                                                                                            //! à regarder avec une règle (1er degrés)
    }
}