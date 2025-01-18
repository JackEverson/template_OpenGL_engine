#shadervertex
#version 460 core
    layout (location = 0) in vec3 aPos;

    uniform vec3 aColor;

    out vec3 color;

    void main()
    {
       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
       color = aColor;
    };

#shaderfragment
#version 460 core
    in vec3 color;
    out vec4 FragColor;
    void main()
    {
      FragColor = vec4(color, 1.0f);
    };

