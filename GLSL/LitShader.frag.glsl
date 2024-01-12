    #version 330 core

    //in vec2 UVs;

    out vec4 fragColor;

    uniform vec4      COLOR;
    //uniform sampler2D TEXTURE;

    void main()
    {
        fragColor = COLOR;//vec4(texture(TEXTURE, UVs).rgb, 1.0);
    }