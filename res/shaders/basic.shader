#shadervertex
#version 330 core
    layout (location = 0) in vec3 aPos;
    void main()
    {
       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    };

#shaderfragment
#version 330 core
    out vec4 FragColor;
    void main()
    {
      FragColor = vec4(0.5f, 0.1f, 0.5f, 1.0f);
    };

